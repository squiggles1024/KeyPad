/**
  ******************************************************************************
  * @file    usbd_customhid.h
  * @author  MCD Application Team
  * @brief   header file for the usbd_customhid.c file.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CUSTOMHID_H
#define __USB_CUSTOMHID_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_CUSTOM_HID
  * @brief This file is the Header file for USBD_customhid.c
  * @{
  */


/** @defgroup USBD_CUSTOM_HID_Exported_Defines
  * @{
  */


#ifndef MOUSE_HID_EPIN_ADDR
#define MOUSE_HID_EPIN_ADDR                          0x81
#endif

#ifndef KEYBOARD_HID_EPIN_ADDR
#define KEYBOARD_HID_EPIN_ADDR                       0x82
#endif


#ifndef GENERIC_HID_OUT_ADDR
#define GENERIC_HID_OUT_ADDR                         0x03
#endif


#define MOUSE_EP_MAX_PACKET_SIZE                     0x0040
#define KBD_EP_MAX_PACKET_SIZE                       0x0040
#define GHID_EP_MAX_PACKET_SIZE                      0x0040

//USB Descriptor Lengths
#define USB_CONFIG_DESC_LEN                          0x09
#define USB_MOUSE_IFDESC_LEN                         0x09
#define USB_KBD_IFDESC_LEN                           0x09
#define USB_GENERIC_HID_IFDESC_LEN                   0x09
#define USB_HID_DESC_LEN                             0x09
#define USB_MOUSEHID_REPORT_DESC_LEN                 0x0040
#define USB_KBDHID_REPORT_DESC_LEN                   0x002D
#define USB_GHID_REPORT_DESC_LEN                     0x0015
#define USB_EP_DESC_LEN                              0x07

#define USB_COMPOSITE_DESC_LEN                       (USB_CONFIG_DESC_LEN + USB_MOUSE_IFDESC_LEN + USB_HID_DESC_LEN + USB_EP_DESC_LEN + USB_KBD_IFDESC_LEN + USB_HID_DESC_LEN + USB_EP_DESC_LEN + USB_GENERIC_HID_IFDESC_LEN + USB_HID_DESC_LEN + USB_EP_DESC_LEN)

//USB IF Protocols
#define USB_NO_IF_PROTOCOL                           0x00
#define USB_KBD_IF_PROTOCOL                          0x01
#define USB_MOUSE_IF_PROTOCOL                        0x02

//USB IF Numbers
#define USB_MOUSE_IFNUM                              0x00
#define USB_KBD_IFNUM                                0x01
#define USB_GENERIC_HID_IFNUM                        0x02

//USB Endpoints per interface
#define USB_MOUSE_EP_QTY                             0x01
#define USB_KBD_EP_QTY                               0x01
#define USB_GENERIC_HID_EP_QTY                       0x01

//Number of HID Report Descriptors per HID
#define USB_MOUSE_REPORT_DESC_QTY                    0x01
#define USB_KBD_REPORT_DESC_QTY                      0x01
#define USB_GHID_REPORT_DESC_QTY                     0x01

//USB HID Class Specifics
#define USB_HID_DEV_CLASS                            0x03
#define USB_HID_CLASS_SPEC                           0x0111

//USB Descriptor Types
#define USB_DESC_TYPE_HID                            0x21
#define USB_DESC_TYPE_HID_REPORT                     0x22

//USB bIntervals
#define USB_MOUSE_POLLRATE                           0x01
#define USB_KBD_POLLRATE                             0x01
#define USB_GHID_POLLRATE                            0x01

//USB EP Type
#define USB_EP_TYPE_INTERRUPT                        0x03

#define CUSTOM_HID_DESCRIPTOR_TYPE                   0x21U
#define CUSTOM_HID_REPORT_DESC                       0x22U

#define CUSTOM_HID_REQ_SET_PROTOCOL                  0x0BU
#define CUSTOM_HID_REQ_GET_PROTOCOL                  0x03U

#define CUSTOM_HID_REQ_SET_IDLE                      0x0AU
#define CUSTOM_HID_REQ_GET_IDLE                      0x02U

#define CUSTOM_HID_REQ_SET_REPORT                    0x09U
#define CUSTOM_HID_REQ_GET_REPORT                    0x01U

/**
  * @}
  */


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */
typedef enum
{
  CUSTOM_HID_IDLE = 0U,
  CUSTOM_HID_BUSY,
} CUSTOM_HID_StateTypeDef;

typedef struct _USBD_CUSTOM_HID_Itf
{
  uint8_t *pReport;
  int8_t (* Init)(void);
  int8_t (* DeInit)(void);
  int8_t (* OutEvent)(uint8_t event_idx, uint8_t state);

} USBD_CUSTOM_HID_ItfTypeDef;

typedef struct
{
  uint8_t  Report_buf[GHID_EP_MAX_PACKET_SIZE];
  uint32_t Protocol;
  uint32_t IdleState;
  uint32_t AltSetting;
  uint32_t IsReportAvailable;
  CUSTOM_HID_StateTypeDef state;
} USBD_CUSTOM_HID_HandleTypeDef;

/*
 * HID Class specification version 1.1
 * 6.2.1 HID Descriptor
 */

typedef struct
{
  uint8_t           bLength;
  uint8_t           bDescriptorTypeCHID;
  uint16_t          bcdCUSTOM_HID;
  uint8_t           bCountryCode;
  uint8_t           bNumDescriptors;
  uint8_t           bDescriptorType;
  uint16_t          wItemLength;
} __PACKED USBD_DescTypeDef;

/**
  * @}
  */



/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */

extern USBD_ClassTypeDef USBD_CUSTOM_HID;
#define USBD_CUSTOM_HID_CLASS &USBD_CUSTOM_HID
/**
  * @}
  */

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */
uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef *pdev,
                                   uint8_t *report, uint16_t len, uint8_t epnum);

uint8_t USBD_CUSTOM_HID_ReceivePacket(USBD_HandleTypeDef *pdev);

uint8_t USBD_CUSTOM_HID_RegisterInterface(USBD_HandleTypeDef *pdev,
                                          USBD_CUSTOM_HID_ItfTypeDef *fops);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_CUSTOMHID_H */
/**
  * @}
  */

/**
  * @}
  */

