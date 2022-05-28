/*
 * TouchButton_Hardware.c
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */
#include "TouchButton_Hardware.h"
#include "FT6206.h"

typedef enum{
	TouchButton_Uninitialized,
	TouchButton_Initialized
}TouchButton_Init_Status_t;

static TouchButton_Init_Status_t TouchButton_Init = TouchButton_Uninitialized;

static void TouchButton_IO_Init(void){;
	if(TouchButton_Init == TouchButton_Uninitialized){
		FT6206_Init(&TouchScreen, FT6202_Drv);
		TouchButton_Init = TouchButton_Initialized;
	}
}

static void TouchButton_IO_DeInit(void){
	if(TouchButton_Init == TouchButton_Initialized){
		FT6206_DeInit(&TouchScreen);
		TouchButton_Init = TouchButton_Uninitialized;
	}
}

static TouchButtonState_t TouchButton_IO_Read(TouchButtonCoordinate_t TopLeftBound, TouchButtonCoordinate_t BottomRightBound){
	if(TouchScreen.P1_XPos >= TopLeftBound.X_Position && TouchScreen.P1_XPos <= BottomRightBound.X_Position && TouchScreen.P1_YPos >= TopLeftBound.Y_Position && TouchScreen.P1_YPos <= BottomRightBound.Y_Position){
		if(TouchScreen.P1_EventFlag == Contact){
	        return TouchButtonPressed;
		} else {
			return TouchButtonUnpressed;
		}
	} else {
		return TouchButtonUnpressed;
	}
}


FT6206_Handle_t TouchScreen;
const TouchButton_IO_Drv_t TouchButton_IO_Driver = {
		.init = TouchButton_IO_Init,
		.deinit = TouchButton_IO_DeInit,
		.read = TouchButton_IO_Read,
		.write = '\0',
		.ioctl = '\0'
};

void TouchScreenIRQCallback(){
	FT6206_ReadScreen(&TouchScreen);
}
