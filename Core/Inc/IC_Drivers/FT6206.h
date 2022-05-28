/*
 * FT6206.h
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */

#ifndef INC_IC_DRIVERS_FT6206_H_
#define INC_IC_DRIVERS_FT6206_H_
#include <stdint.h>
#include "FT6206_Hardware.h"
typedef uint8_t FT6206_Reg_t;

extern const FT6206_Reg_t DEV_MODE;
extern const FT6206_Reg_t GEST_ID;
extern const FT6206_Reg_t TD_STATUS;
extern const FT6206_Reg_t P1_XH;
extern const FT6206_Reg_t P1_XL;
extern const FT6206_Reg_t P1_YH;
extern const FT6206_Reg_t P1_YL;
extern const FT6206_Reg_t P1_WEIGHT;
extern const FT6206_Reg_t P1_MISC;
extern const FT6206_Reg_t P2_XH;
extern const FT6206_Reg_t P2_XL;
extern const FT6206_Reg_t P2_YH;
extern const FT6206_Reg_t P2_YL;
extern const FT6206_Reg_t P2_WEIGHT;
extern const FT6206_Reg_t P2_MISC;
extern const FT6206_Reg_t TH_GROUP;
extern const FT6206_Reg_t TH_DIFF;
extern const FT6206_Reg_t CTRL;
extern const FT6206_Reg_t TIMEENTERMONITOR;
extern const FT6206_Reg_t PERIODACTIVE;
extern const FT6206_Reg_t PERIODMONITOR;
extern const FT6206_Reg_t RADIAN_VALUE;
extern const FT6206_Reg_t OFFSET_LEFT_RIGHT;
extern const FT6206_Reg_t OFFSET_UP_DOWN;
extern const FT6206_Reg_t DISTANCE_LEFT_RIGHT;
extern const FT6206_Reg_t DISTANCE_UP_DOWN;
extern const FT6206_Reg_t DISTANCE_ZOOM;
extern const FT6206_Reg_t LIB_VER_H;
extern const FT6206_Reg_t LIB_VER_L;
extern const FT6206_Reg_t CIPHER;
extern const FT6206_Reg_t G_MODE;
extern const FT6206_Reg_t PWR_MODE;
extern const FT6206_Reg_t FIRMID;
extern const FT6206_Reg_t FOCALTECH_ID;
extern const FT6206_Reg_t RELEASE_CODE_ID;
extern const FT6206_Reg_t STATE;

typedef enum{
    PressDown = 0,
	LiftUp,
	Contact,
	NoEvent
}FT6202_EventFlag_t;

typedef struct{
	volatile uint16_t P1_XPos;
	volatile uint16_t P1_YPos;
	volatile FT6202_EventFlag_t P1_EventFlag;
	FT6206_IO_Drv_t IO_Driver;
}FT6206_Handle_t;

void FT6206_Init(FT6206_Handle_t *Dev, FT6206_IO_Drv_t IO_Drv);
void FT6206_DeInit(FT6206_Handle_t *Dev);
void FT6206_ReadScreen(FT6206_Handle_t *Dev);
void FT6206_Halt(FT6206_Handle_t *Dev);
void FT6206_ReadReg(FT6206_Handle_t *Dev, FT6206_Reg_t reg, uint8_t* pdata, uint8_t length);
void FT6206_WriteReg(FT6206_Handle_t *Dev, FT6206_Reg_t reg, uint8_t* pdata, uint8_t length);


#endif /* INC_KEYPADPARTS_FT6206_H_ */
