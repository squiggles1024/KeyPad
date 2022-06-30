/*
 * TouchButton_Hardware.c
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "TouchButton_Hardware.h"
#include "FT6206.h"

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	TouchButton_Uninitialized,
	TouchButton_Initialized
}TouchButton_Init_Status_t;

/**************************************//**************************************//**************************************
 * Private Variable Definitions
 **************************************//**************************************//**************************************/
static TouchButton_Init_Status_t TouchButton_Init = TouchButton_Uninitialized;

/**************************************//**************************************//**************************************
 * Private Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes hardware required to use touch buttons
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: FT6206 Hardware will be initialized
 **************************************//**************************************/
static void TouchButton_IO_Init(void){;
	if(TouchButton_Init == TouchButton_Uninitialized){
		FT6206_Init(&TouchScreen, FT6202_Drv);
		TouchButton_Init = TouchButton_Initialized;
	}
}

/**************************************//**************************************
 *@Brief: deinitializes TouchButton LL hardware
 *@Params: None
 *@Return: None
 *@Precondition: TouchButton should be initialized
 *@Postcondition: DMA engine will be stopped and FT6206 Device IO handle will be deinitialized
 **************************************//**************************************/
static void TouchButton_IO_DeInit(void){
	if(TouchButton_Init == TouchButton_Initialized){
		FT6206_DeInit(&TouchScreen);
		TouchButton_Init = TouchButton_Uninitialized;
	}
}

/**************************************//**************************************
 *@Brief: Determines if a touch button is pressed
 *@Params: Upper Left and Lower Right boundary for button
 *@Return: Pressed if a touch is detected, otherwise Unpressed
 *@Precondition: TouchButton Hardware must be initialized.
 *@Postcondition: None
 **************************************//**************************************/
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


/**************************************//**************************************//**************************************
 * Exported Variables
 **************************************//**************************************//**************************************/
FT6206_Handle_t TouchScreen;
const TouchButton_IO_Drv_t TouchButton_IO_Driver = {
		.init = TouchButton_IO_Init,
		.deinit = TouchButton_IO_DeInit,
		.read = TouchButton_IO_Read,
		.write = '\0',
		.ioctl = '\0'
};

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
void TouchScreenIRQCallback(){
	FT6206_ReadScreen(&TouchScreen);
}
