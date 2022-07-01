/**
  ******************************************************************************
  * @file    usbd_customhid.c
  * @author  MCD Application Team
  * @brief   This file provides the CUSTOM_HID core functions.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  * @verbatim
  *
  *          ===================================================================
  *                                CUSTOM_HID Class  Description
  *          ===================================================================
  *           This module manages the CUSTOM_HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (CUSTOM_HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - Usage Page : Generic Desktop
  *             - Usage : Vendor
  *             - Collection : Application
  *
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *
  *
  *  @endverbatim
  *
  ******************************************************************************
  */

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbd_customhid.h"
#include "usbd_ctlreq.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_CUSTOM_HID
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_CUSTOM_HID_Private_Defines
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_CUSTOM_HID_Private_Macros
  * @{
  */
/**
  * @}
  */
/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @{
  */

static uint8_t USBD_CUSTOM_HID_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_CUSTOM_HID_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_CUSTOM_HID_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);

static uint8_t USBD_CUSTOM_HID_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t USBD_CUSTOM_HID_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t USBD_CUSTOM_HID_EP0_RxReady(USBD_HandleTypeDef  *pdev);
#ifndef USE_USBD_COMPOSITE
static uint8_t *USBD_CUSTOM_HID_GetFSCfgDesc(uint16_t *length);
static uint8_t *USBD_CUSTOM_HID_GetHSCfgDesc(uint16_t *length);
static uint8_t *USBD_CUSTOM_HID_GetOtherSpeedCfgDesc(uint16_t *length);
static uint8_t *USBD_CUSTOM_HID_GetDeviceQualifierDesc(uint16_t *length);
#endif /* USE_USBD_COMPOSITE  */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables
  * @{
  */

USBD_ClassTypeDef  USBD_CUSTOM_HID =
{
  USBD_CUSTOM_HID_Init,
  USBD_CUSTOM_HID_DeInit,
  USBD_CUSTOM_HID_Setup,
  NULL, /*EP0_TxSent*/
  USBD_CUSTOM_HID_EP0_RxReady, /*EP0_RxReady*/ /* STATUS STAGE IN */
  USBD_CUSTOM_HID_DataIn, /*DataIn*/
  USBD_CUSTOM_HID_DataOut,
  NULL, /*SOF */
  NULL,
  NULL,
#ifdef USE_USBD_COMPOSITE
  NULL,
  NULL,
  NULL,
  NULL,
#else
  USBD_CUSTOM_HID_GetHSCfgDesc,
  USBD_CUSTOM_HID_GetFSCfgDesc,
  USBD_CUSTOM_HID_GetOtherSpeedCfgDesc,
  USBD_CUSTOM_HID_GetDeviceQualifierDesc,
#endif /* USE_USBD_COMPOSITE  */
};

__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[USB_MOUSEHID_REPORT_DESC_LEN] __ALIGN_END =
{
	    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	    0x09, 0x02,                    // USAGE (Mouse)
	    0xa1, 0x01,                    // COLLECTION (Application)
	    0x09, 0x01,                    //   USAGE (Pointer)
	    0xa1, 0x00,                    //   COLLECTION (Physical)
	    0x05, 0x09,                    //     USAGE_PAGE (Button)
	    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
	    0x29, 0x05,                    //     USAGE_MAXIMUM (Button 5)
	    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	    0x95, 0x05,                    //     REPORT_COUNT (5)
	    0x75, 0x01,                    //     REPORT_SIZE (1)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0x75, 0x03,                    //     REPORT_SIZE (3)
	    0x95, 0x01,                    //     REPORT_COUNT (1)
	    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
	    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	    0x09, 0x30,                    //     USAGE (X)
	    0x09, 0x31,                    //     USAGE (Y)
	    0x15, 0x7f,                    //     LOGICAL_MINIMUM (-127)
	    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	    0x75, 0x08,                    //     REPORT_SIZE (8)
	    0x95, 0x02,                    //     REPORT_COUNT (2)
	    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
	    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	    0x09, 0x38,                    //     USAGE (Wheel)
	    0x15, 0x7f,                    //     LOGICAL_MINIMUM (-127)
	    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	    0x75, 0x08,                    //     REPORT_SIZE (8)
	    0x95, 0x01,                    //     REPORT_COUNT (1)
	    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
	    0xc0,                          //   END_COLLECTION
	    0xc0,                          // END_COLLECTION
};

__ALIGN_BEGIN static uint8_t HID_KEY_ReportDesc[USB_KBDHID_REPORT_DESC_LEN] __ALIGN_END = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x95, SIMULTANEOUS_BUTTONS,    //   REPORT_COUNT (Number of buttons that can be pressed simultaneously)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
};



__ALIGN_BEGIN static uint8_t HID_GHID_ReportDesc[USB_GHID_REPORT_DESC_LEN] __ALIGN_END = {
    0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    //   COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x06,                    //   REPORT_COUNT (6): 1 Byte = Button Type, 1 Byte = Button Address, 4 Bytes = Button Function
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0xc0                           // END_COLLECTION
};


__ALIGN_BEGIN static uint8_t KeyPad_ConfigDesc[USB_COMPOSITE_DESC_LEN] __ALIGN_END= {
	//Config Desc
	USB_CONFIG_DESC_LEN, //bLength
	USB_DESC_TYPE_CONFIGURATION, //bDescriptorType (Config desc)
	LOBYTE(USB_COMPOSITE_DESC_LEN), //wTotalLength
	HIBYTE(USB_COMPOSITE_DESC_LEN),
	0x03, //bNumInterfaces, 3 interfaces
	0x01, //bConfigurationValue, config 1
	0x00, //iConfiguration, index of string descriptor
    0x80, //bmAttributes (D7 = reserved bit = must be 1)
	USBD_MAX_POWER, //bMaxPower 100mA

	//Interface 0: Mouse Interface
    USB_MOUSE_IFDESC_LEN,    //bLength
	USB_DESC_TYPE_INTERFACE, //bDescType
    USB_MOUSE_IFNUM,         //bInterface Number
	0x00,                    //bAlternateSettings
	USB_MOUSE_EP_QTY,        //bNumEndpoints
	USB_HID_DEV_CLASS,       //bInterfaceClass
	0,                       //bInterfaceSubclass (1 = Boot, 0 = No Boot)
	USB_MOUSE_IF_PROTOCOL,   //bInterfaceProtocol (0 = none, 1 = keyboard, 2 = mouse)
	0,                       //iInterface (index of str desc)

	//HID 0: Mouse HID Desc
	USB_HID_DESC_LEN,           //bLength
	USB_DESC_TYPE_HID,          //bDescriptorType
	LOBYTE(USB_HID_CLASS_SPEC), //bcdHID
	HIBYTE(USB_HID_CLASS_SPEC),
	0,                          //bCountryCode
	USB_MOUSE_REPORT_DESC_QTY,  //bNumDescriptors = Number of HID Report Descriptors
	USB_DESC_TYPE_HID_REPORT,   //bDescriptorType = Descriptor Type to Follow
    LOBYTE(USB_MOUSEHID_REPORT_DESC_LEN),
	HIBYTE(USB_MOUSEHID_REPORT_DESC_LEN),

	//EPIN 1: Mouse IN Endpoint Desc
	USB_EP_DESC_LEN, //bLength
	USB_DESC_TYPE_ENDPOINT, //bDescriptorType
	MOUSE_HID_EPIN_ADDR,    //bEndpoint Address
	USB_EP_TYPE_INTERRUPT,  //bmAttributes
    LOBYTE(MOUSE_EP_MAX_PACKET_SIZE),
	HIBYTE(MOUSE_EP_MAX_PACKET_SIZE),
	USB_MOUSE_POLLRATE,

	//Interface 1: Keyboard Interface
    USB_KBD_IFDESC_LEN,      //bLength
	USB_DESC_TYPE_INTERFACE, //bDescType
    USB_KBD_IFNUM,           //bInterface Number
	0x00,                    //bAlternateSettings
	USB_KBD_EP_QTY,          //bNumEndpoints
	USB_HID_DEV_CLASS,       //bInterfaceClass
	0,                       //bInterfaceSubclass (1 = Boot, 0 = No Boot)
	USB_KBD_IF_PROTOCOL,     //bInterfaceProtocol (0 = none, 1 = keyboard, 2 = mouse)
	0,                       //iInterface (index of str desc)

	//HID 1: Keyboard HID Desc
	USB_HID_DESC_LEN,           //bLength
	USB_DESC_TYPE_HID,          //bDescriptorType
	LOBYTE(USB_HID_CLASS_SPEC), //bcdHID
	HIBYTE(USB_HID_CLASS_SPEC),
	0,                          //bCountryCode
	USB_KBD_REPORT_DESC_QTY,    //bNumDescriptors = Number of HID Report Descriptors
	USB_DESC_TYPE_HID_REPORT,   //bDescriptorType = Descriptor Type to Follow
    LOBYTE(USB_KBDHID_REPORT_DESC_LEN),
	HIBYTE(USB_KBDHID_REPORT_DESC_LEN),

	//EPIN 2: Keyboard IN Endpoint Desc
	USB_EP_DESC_LEN, //bLength
	USB_DESC_TYPE_ENDPOINT, //bDescriptorType
	KEYBOARD_HID_EPIN_ADDR,    //bEndpoint Address
	USB_EP_TYPE_INTERRUPT,  //bmAttributes
    LOBYTE(KBD_EP_MAX_PACKET_SIZE),
	HIBYTE(KBD_EP_MAX_PACKET_SIZE),
	USB_KBD_POLLRATE,

	//Interface 2: Generic HID
    USB_KBD_IFDESC_LEN,      //bLength
	USB_DESC_TYPE_INTERFACE, //bDescType
    USB_GENERIC_HID_IFNUM,   //bInterface Number
	0x00,                    //bAlternateSettings
	USB_GENERIC_HID_EP_QTY,  //bNumEndpoints
	USB_HID_DEV_CLASS,       //bInterfaceClass
	0,                       //bInterfaceSubclass (1 = Boot, 0 = No Boot)
	USB_NO_IF_PROTOCOL,      //bInterfaceProtocol (0 = none, 1 = keyboard, 2 = mouse)
	0,                       //iInterface (index of str desc)

	//HID 2: Generic HID Desc
	USB_HID_DESC_LEN,           //bLength
	USB_DESC_TYPE_HID,          //bDescriptorType
	LOBYTE(USB_HID_CLASS_SPEC), //bcdHID
	HIBYTE(USB_HID_CLASS_SPEC),
	0,                          //bCountryCode
	USB_GHID_REPORT_DESC_QTY,    //bNumDescriptors = Number of HID Report Descriptors
	USB_DESC_TYPE_HID_REPORT,   //bDescriptorType = Descriptor Type to Follow
    LOBYTE(USB_GHID_REPORT_DESC_LEN),
	HIBYTE(USB_GHID_REPORT_DESC_LEN),

	//EPIN 3: Generic HID OUT Endpoint Desc
	USB_EP_DESC_LEN, //bLength
	USB_DESC_TYPE_ENDPOINT, //bDescriptorType
	GENERIC_HID_OUT_ADDR,    //bEndpoint Address
	USB_EP_TYPE_INTERRUPT,  //bmAttributes
    LOBYTE(GHID_EP_MAX_PACKET_SIZE),
	HIBYTE(GHID_EP_MAX_PACKET_SIZE),
	USB_GHID_POLLRATE,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_CUSTOM_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};
 /* USE_USBD_COMPOSITE  */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Functions
  * @{
  */

/**
  * @brief  USBD_CUSTOM_HID_Init
  *         Initialize the CUSTOM_HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_CUSTOM_HID_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);
  USBD_CUSTOM_HID_HandleTypeDef *hhid;

  hhid = (USBD_CUSTOM_HID_HandleTypeDef *)USBD_malloc(sizeof(USBD_CUSTOM_HID_HandleTypeDef));

  if (hhid == NULL)
  {
    pdev->pClassDataCmsit[pdev->classId] = NULL;
    return (uint8_t)USBD_EMEM;
  }

   pdev->pClassDataCmsit[pdev->classId] = (void *)hhid;
   pdev->pClassData = pdev->pClassDataCmsit[pdev->classId];


   pdev->ep_in[KEYBOARD_HID_EPIN_ADDR & 0xFU].bInterval = CUSTOM_HID_FS_BINTERVAL;
   pdev->ep_in[MOUSE_HID_EPIN_ADDR & 0xFU].bInterval = USB_MOUSE_POLLRATE;
   pdev->ep_out[GENERIC_HID_OUT_ADDR & 0xFU].bInterval = USB_GHID_POLLRATE;


  /* Open EP IN */
  (void)USBD_LL_OpenEP(pdev, MOUSE_HID_EPIN_ADDR, USBD_EP_TYPE_INTR, MOUSE_EP_MAX_PACKET_SIZE);
  (void)USBD_LL_OpenEP(pdev, KEYBOARD_HID_EPIN_ADDR, USBD_EP_TYPE_INTR, KBD_EP_MAX_PACKET_SIZE);

  pdev->ep_in[MOUSE_HID_EPIN_ADDR & 0xFU].is_used = 1U;
  pdev->ep_in[KEYBOARD_HID_EPIN_ADDR & 0xFU].is_used = 1U;

  /* Open EP OUT */
  (void)USBD_LL_OpenEP(pdev, GENERIC_HID_OUT_ADDR, USBD_EP_TYPE_INTR, GHID_EP_MAX_PACKET_SIZE);

  pdev->ep_out[GENERIC_HID_OUT_ADDR & 0xFU].is_used = 1U;

  hhid->state = CUSTOM_HID_IDLE;

  ((USBD_CUSTOM_HID_ItfTypeDef *)pdev->pUserData[pdev->classId])->Init();

  /* Prepare Out endpoint to receive 1st packet */
  (void)USBD_LL_PrepareReceive(pdev, GENERIC_HID_OUT_ADDR, hhid->Report_buf, GHID_EP_MAX_PACKET_SIZE);

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_CUSTOM_HID_Init
  *         DeInitialize the CUSTOM_HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_CUSTOM_HID_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);

  /* Close CUSTOM_HID EP IN */
  (void)USBD_LL_CloseEP(pdev, MOUSE_HID_EPIN_ADDR);
  pdev->ep_in[MOUSE_HID_EPIN_ADDR & 0xFU].is_used = 0U;
  pdev->ep_in[MOUSE_HID_EPIN_ADDR & 0xFU].bInterval = 0U;
  (void)USBD_LL_CloseEP(pdev, KEYBOARD_HID_EPIN_ADDR);
  pdev->ep_in[KEYBOARD_HID_EPIN_ADDR & 0xFU].is_used = 0U;
  pdev->ep_in[KEYBOARD_HID_EPIN_ADDR & 0xFU].bInterval = 0U;

  /* Close CUSTOM_HID EP OUT */
  (void)USBD_LL_CloseEP(pdev, GENERIC_HID_OUT_ADDR);
  pdev->ep_out[GENERIC_HID_OUT_ADDR & 0xFU].is_used = 0U;
  pdev->ep_out[GENERIC_HID_OUT_ADDR & 0xFU].bInterval = 0U;

  /* Free allocated memory */
  if (pdev->pClassDataCmsit[pdev->classId] != NULL)
  {
    ((USBD_CUSTOM_HID_ItfTypeDef *)pdev->pUserData[pdev->classId])->DeInit();
    USBD_free(pdev->pClassDataCmsit[pdev->classId]);
    pdev->pClassDataCmsit[pdev->classId] = NULL;
    pdev->pClassData = NULL;
  }

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_CUSTOM_HID_Setup
  *         Handle the CUSTOM_HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t USBD_CUSTOM_HID_Setup(USBD_HandleTypeDef *pdev,
                                     USBD_SetupReqTypedef *req)
{
  USBD_CUSTOM_HID_HandleTypeDef *hhid = (USBD_CUSTOM_HID_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];
  uint16_t len = 0U;
  uint8_t  *pbuf = NULL;
  uint16_t status_info = 0U;
  USBD_StatusTypeDef ret = USBD_OK;

  if (hhid == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
    case USB_REQ_TYPE_CLASS:
      switch (req->bRequest)
      {
        case CUSTOM_HID_REQ_SET_PROTOCOL:
          hhid->Protocol = (uint8_t)(req->wValue);
          break;

        case CUSTOM_HID_REQ_GET_PROTOCOL:
          (void)USBD_CtlSendData(pdev, (uint8_t *)&hhid->Protocol, 1U);
          break;

        case CUSTOM_HID_REQ_SET_IDLE:
          hhid->IdleState = (uint8_t)(req->wValue >> 8);
          break;

        case CUSTOM_HID_REQ_GET_IDLE:
          (void)USBD_CtlSendData(pdev, (uint8_t *)&hhid->IdleState, 1U);
          break;

        case CUSTOM_HID_REQ_SET_REPORT:
          hhid->IsReportAvailable = 1U;
          (void)USBD_CtlPrepareRx(pdev, hhid->Report_buf,
                                  MIN(req->wLength, USBD_CUSTOMHID_OUTREPORT_BUF_SIZE));
          break;

        default:
          USBD_CtlError(pdev, req);
          ret = USBD_FAIL;
          break;
      }
      break;

    case USB_REQ_TYPE_STANDARD:
      switch (req->bRequest)
      {
        case USB_REQ_GET_STATUS:
          if (pdev->dev_state == USBD_STATE_CONFIGURED)
          {
            (void)USBD_CtlSendData(pdev, (uint8_t *)&status_info, 2U);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_GET_DESCRIPTOR:
          if ((req->wValue >> 8) == CUSTOM_HID_REPORT_DESC)
          {
              if(req->wIndex == USB_MOUSE_IFNUM){
                  pbuf = HID_MOUSE_ReportDesc;
                  len = MIN(USB_MOUSEHID_REPORT_DESC_LEN, req->wLength);
              } else if(req->wIndex == USB_KBD_IFNUM){
                  pbuf = HID_KEY_ReportDesc;
                  len = MIN(USB_KBDHID_REPORT_DESC_LEN, req->wLength);
              } else if(req->wIndex == USB_GENERIC_HID_IFNUM){
                  pbuf = HID_GHID_ReportDesc;
                  len = MIN(USB_GHID_REPORT_DESC_LEN, req->wLength);
              }
          }


          (void)USBD_CtlSendData(pdev, pbuf, len);
          break;

        case USB_REQ_GET_INTERFACE:
          if (pdev->dev_state == USBD_STATE_CONFIGURED)
          {
            (void)USBD_CtlSendData(pdev, (uint8_t *)&hhid->AltSetting, 1U);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_SET_INTERFACE:
          if (pdev->dev_state == USBD_STATE_CONFIGURED)
          {
            hhid->AltSetting = (uint8_t)(req->wValue);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_CLEAR_FEATURE:
          break;

        default:
          USBD_CtlError(pdev, req);
          ret = USBD_FAIL;
          break;
      }
      break;

    default:
      USBD_CtlError(pdev, req);
      ret = USBD_FAIL;
      break;
  }
  return (uint8_t)ret;
}

/**
  * @brief  USBD_CUSTOM_HID_SendReport
  *         Send CUSTOM_HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef *pdev, uint8_t *report, uint16_t len, uint8_t epnum)
{
  USBD_CUSTOM_HID_HandleTypeDef *hhid;

  if (pdev->pClassDataCmsit[pdev->classId] == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  hhid = (USBD_CUSTOM_HID_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (pdev->dev_state == USBD_STATE_CONFIGURED)
  {
    if (hhid->state == CUSTOM_HID_IDLE)
    {
      hhid->state = CUSTOM_HID_BUSY;
      (void)USBD_LL_Transmit(pdev, epnum, report, len);
    }
    else
    {
      return (uint8_t)USBD_BUSY;
    }
  }
  return (uint8_t)USBD_OK;
}
#ifndef USE_USBD_COMPOSITE
/**
  * @brief  USBD_CUSTOM_HID_GetFSCfgDesc
  *         return FS configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_CUSTOM_HID_GetFSCfgDesc(uint16_t *length)
{

  *length = (uint16_t)sizeof(KeyPad_ConfigDesc);
  return KeyPad_ConfigDesc;
}

/**
  * @brief  USBD_CUSTOM_HID_GetHSCfgDesc
  *         return HS configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_CUSTOM_HID_GetHSCfgDesc(uint16_t *length)
{
  *length = (uint16_t)sizeof(KeyPad_ConfigDesc);
  return KeyPad_ConfigDesc;
}

/**
  * @brief  USBD_CUSTOM_HID_GetOtherSpeedCfgDesc
  *         return other speed configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_CUSTOM_HID_GetOtherSpeedCfgDesc(uint16_t *length)
{
  *length = (uint16_t)sizeof(KeyPad_ConfigDesc);
  return KeyPad_ConfigDesc;
}
#endif /* USE_USBD_COMPOSITE  */

/**
  * @brief  USBD_CUSTOM_HID_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_CUSTOM_HID_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  UNUSED(epnum);

  /* Ensure that the FIFO is empty before a new transfer, this condition could
  be caused by  a new transfer before the end of the previous transfer */
  ((USBD_CUSTOM_HID_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId])->state = CUSTOM_HID_IDLE;

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_CUSTOM_HID_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_CUSTOM_HID_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  UNUSED(epnum);
  USBD_CUSTOM_HID_HandleTypeDef *hhid;

  if (pdev->pClassDataCmsit[pdev->classId] == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  hhid = (USBD_CUSTOM_HID_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  /* USB data will be immediately processed, this allow next USB traffic being
  NAKed till the end of the application processing */
  ((USBD_CUSTOM_HID_ItfTypeDef *)pdev->pUserData[pdev->classId])->OutEvent(hhid->Report_buf[0],
                                                                           hhid->Report_buf[1]);

  return (uint8_t)USBD_OK;
}


/**
  * @brief  USBD_CUSTOM_HID_ReceivePacket
  *         prepare OUT Endpoint for reception
  * @param  pdev: device instance
  * @retval status
  */
uint8_t USBD_CUSTOM_HID_ReceivePacket(USBD_HandleTypeDef *pdev)
{
  USBD_CUSTOM_HID_HandleTypeDef *hhid;

  if (pdev->pClassDataCmsit[pdev->classId] == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

#ifdef USE_USBD_COMPOSITE
  /* Get OUT Endpoint address allocated for this class instance */
  CUSTOMHIDOutEpAdd = USBD_CoreGetEPAdd(pdev, USBD_EP_OUT, USBD_EP_TYPE_INTR);
#endif /* USE_USBD_COMPOSITE */

  hhid = (USBD_CUSTOM_HID_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  /* Resume USB Out process */
  (void)USBD_LL_PrepareReceive(pdev, GENERIC_HID_OUT_ADDR, hhid->Report_buf, CONFIG_CHANGE_BYTES);

  return (uint8_t)USBD_OK;
}


/**
  * @brief  USBD_CUSTOM_HID_EP0_RxReady
  *         Handles control request data.
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t USBD_CUSTOM_HID_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
  USBD_CUSTOM_HID_HandleTypeDef *hhid = (USBD_CUSTOM_HID_HandleTypeDef *)pdev->pClassDataCmsit[pdev->classId];

  if (hhid == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  if (hhid->IsReportAvailable == 1U)
  {
    ((USBD_CUSTOM_HID_ItfTypeDef *)pdev->pUserData[pdev->classId])->OutEvent(hhid->Report_buf[0],
                                                                             hhid->Report_buf[1]);
    hhid->IsReportAvailable = 0U;
  }

  return (uint8_t)USBD_OK;
}

#ifndef USE_USBD_COMPOSITE
/**
  * @brief  DeviceQualifierDescriptor
  *         return Device Qualifier descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_CUSTOM_HID_GetDeviceQualifierDesc(uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_CUSTOM_HID_DeviceQualifierDesc);

  return USBD_CUSTOM_HID_DeviceQualifierDesc;
}
#endif /* USE_USBD_COMPOSITE  */
/**
  * @brief  USBD_CUSTOM_HID_RegisterInterface
  * @param  pdev: device instance
  * @param  fops: CUSTOMHID Interface callback
  * @retval status
  */
uint8_t USBD_CUSTOM_HID_RegisterInterface(USBD_HandleTypeDef *pdev,
                                          USBD_CUSTOM_HID_ItfTypeDef *fops)
{
  if (fops == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  pdev->pUserData[pdev->classId] = fops;

  return (uint8_t)USBD_OK;
}
/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

