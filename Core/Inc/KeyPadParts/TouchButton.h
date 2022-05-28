/*
 * TouchButton.h
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPADPARTS_TOUCHBUTTON_H_
#define INC_KEYPADPARTS_TOUCHBUTTON_H_
#include "KeyFunctions.h"
#include "TouchButton_Hardware.h"
#include <stdint.h>

typedef enum{
    TouchButtonChanged,
	TouchButtonUnchanged
}TouchButton_Status_t;

typedef struct{
	TouchButtonCoordinate_t TopLeftBound;
	TouchButtonCoordinate_t BottomRightBound;
	KeyScanCode KeyFunction;
	ModifierKey ModKeyFunction;
    MouseClick  MouseFunction;
    MouseWheel  WheelFunction;
}TouchButton_Init_Struct_t;

typedef struct{
	TouchButtonCoordinate_t TopLeftBound;
	TouchButtonCoordinate_t BottomRightBound;
	KeyScanCode KeyFunction;
	ModifierKey ModKeyFunction;
    MouseClick  MouseFunction;
    MouseWheel  WheelFunction;
    TouchButtonState_t State;
    TouchButton_IO_Drv_t IO_Driver;
}TouchButton_Handle_t;

void TouchButtonInit(TouchButton_Init_Struct_t Settings, TouchButton_Handle_t *Dev, TouchButton_IO_Drv_t IO_Driver);
TouchButton_Status_t TouchButtonRead(TouchButton_Handle_t *Dev);
void TouchButtonSetFunction(TouchButton_Handle_t* Dev, KeyScanCode KeyFunc, ModifierKey ModKey, MouseClick MouseFunction, MouseWheel WheelFunction);



#endif /* INC_KEYPADPARTS_TOUCHBUTTON_H_ */
