/*
 * FT6206.c
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "FT6206.h"

/**************************************//**************************************//**************************************
 * Exported Constants
 **************************************//**************************************//**************************************/
const FT6206_Reg_t DEV_MODE = 0x00;
const FT6206_Reg_t GEST_ID = 0x01;
const FT6206_Reg_t TD_STATUS = 0x02;
const FT6206_Reg_t P1_XH = 0x03;
const FT6206_Reg_t P1_XL = 0x04;
const FT6206_Reg_t P1_YH = 0x05;
const FT6206_Reg_t P1_YL = 0x06;
const FT6206_Reg_t P1_WEIGHT = 0x07;
const FT6206_Reg_t P1_MISC = 0x08;
const FT6206_Reg_t P2_XH = 0x09;
const FT6206_Reg_t P2_XL = 0x0A;
const FT6206_Reg_t P2_YH = 0x0B;
const FT6206_Reg_t P2_YL = 0x0C;
const FT6206_Reg_t P2_WEIGHT = 0x0D;
const FT6206_Reg_t P2_MISC = 0x0E;
const FT6206_Reg_t TH_GROUP = 0x80;
const FT6206_Reg_t TH_DIFF = 0x85;
const FT6206_Reg_t CTRL = 0x86;
const FT6206_Reg_t TIMEENTERMONITOR = 0x87;
const FT6206_Reg_t PERIODACTIVE = 0x88;
const FT6206_Reg_t PERIODMONITOR = 0x89;
const FT6206_Reg_t RADIAN_VALUE = 0x91;
const FT6206_Reg_t OFFSET_LEFT_RIGHT = 0x92;
const FT6206_Reg_t OFFSET_UP_DOWN = 0x93;
const FT6206_Reg_t DISTANCE_LEFT_RIGHT = 0x94;
const FT6206_Reg_t DISTANCE_UP_DOWN = 0x95;
const FT6206_Reg_t DISTANCE_ZOOM = 0x96;
const FT6206_Reg_t LIB_VER_H = 0xA1;
const FT6206_Reg_t LIB_VER_L = 0xA2;
const FT6206_Reg_t CIPHER = 0xA3;
const FT6206_Reg_t G_MODE = 0xA4;
const FT6206_Reg_t PWR_MODE = 0xA5;
const FT6206_Reg_t FIRMID = 0xA6;
const FT6206_Reg_t FOCALTECH_ID = 0xA8;
const FT6206_Reg_t RELEASE_CODE_ID = 0xAF;
const FT6206_Reg_t STATE = 0xBC;

/**************************************//**************************************//**************************************
 * Private Variables
 **************************************//**************************************//**************************************/
static uint8_t touch_screen_buffer[4];

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes a FT6206 Device Handle
 *@Params: Device Handle pointer, IO Driver struct
 *@Return: None
 *@Precondition: None
 *@Postcondition: Device handle will have low level hardware initialized (I2C, GPIO, DMA)
 **************************************//**************************************/
void FT6206_Init(FT6206_Handle_t *Dev, FT6206_IO_Drv_t IO_Drv){
	Dev->P1_XPos = 0;
	Dev->P1_YPos = 0;
	Dev->P1_EventFlag = 0;
	Dev->IO_Driver = IO_Drv;
	Dev->IO_Driver.init();
	Dev->IO_Driver.read(P1_XH, touch_screen_buffer, 4);
	//FT6206_ReadScreen(Dev);
}

/**************************************//**************************************
 *@Brief: Deinitializes FT6206 device handle
 *@Params: FT6206 device handle to deinitialize
 *@Return: None
 *@Precondition: None
 *@Postcondition: DMA will be disabled, and IO driver initialized to null
 **************************************//**************************************/
void FT6206_DeInit(FT6206_Handle_t *Dev){
	Dev->IO_Driver.deinit();
	Dev->IO_Driver.init = '\0';
	Dev->IO_Driver.deinit = '\0';
	Dev->IO_Driver.read = '\0';
	Dev->IO_Driver.write = '\0';
	Dev->IO_Driver.ioctl = '\0';
}

/**************************************//**************************************
 *@Brief: Reads the touch screen
 *@Params: Device handle to read
 *@Return: None
 *@Precondition: Device handle should be initialized
 *@Postcondition: Dev.State and Coordinates will be updated (Pressed/Unpressed and position)
 **************************************//**************************************/
void FT6206_ReadScreen(FT6206_Handle_t *Dev){
	//uint8_t buffer[4];
	Dev->P1_YPos = 240 - ((touch_screen_buffer[0] << 8 | touch_screen_buffer[1]) & 0x0FFF);
	Dev->P1_EventFlag = touch_screen_buffer[0] >> 6;
	Dev->P1_XPos = (touch_screen_buffer[2] << 8 | touch_screen_buffer[3]) & 0x0FFF;
	Dev->IO_Driver.read(P1_XH, touch_screen_buffer, 4);
}

/**************************************//**************************************
 *@Brief: Stops FT6206 DMA Engine
 *@Params: Device handle to stop
 *@Return: None
 *@Precondition: Device handle should be initialized.
 *@Postcondition: Device DMA engine will be stopped.
 **************************************//**************************************/
void FT6206_Halt(FT6206_Handle_t *Dev){
	Dev->IO_Driver.deinit();
}

/**************************************//**************************************
 *@Brief: Reads a FT6206 Device Register
 *@Params: Device handle, register to read, data buffer, number of bytes
 *@Return: None
 *@Precondition: Device handle should be initialized.
 *@Postcondition: pdata will contain FT6206 register data
 **************************************//**************************************/
void FT6206_ReadReg(FT6206_Handle_t *Dev, FT6206_Reg_t reg, uint8_t* pdata, uint8_t length){
    Dev->IO_Driver.read(reg, pdata, length);
}

/**************************************//**************************************
 *@Brief: Writes to a FT6206 Device Register
 *@Params: Device handle, reg to read, data buffer to write, number of bytes to write
 *@Return: None
 *@Precondition: Device handle should be initialized. pdata should be able to store length bytes
 *@Postcondition: pdata will be written to FT6206 device register
 **************************************//**************************************/
void FT6206_WriteReg(FT6206_Handle_t *Dev, FT6206_Reg_t reg, uint8_t* pdata, uint8_t length){
	Dev->IO_Driver.write(reg, pdata, length);
}

