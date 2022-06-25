/*
 * TouchButton.c
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */
#include "TouchButton.h"

void TouchButtonInit(TouchButton_Init_Struct_t Settings, TouchButton_Handle_t *Dev, TouchButton_IO_Drv_t IO_Driver){
    Dev->IO_Driver = IO_Driver;
    Dev->KeyFunction = Settings.KeyFunction;
    Dev->TopLeftBound = Settings.TopLeftBound;
    Dev->BottomRightBound = Settings.BottomRightBound;
    Dev->State = TouchButtonUnpressed;
    Dev->IO_Driver.init();
}



void TouchButtonSetFunction(TouchButton_Handle_t* Dev, KeyFunction_t NewFunction){
    Dev->KeyFunction = NewFunction;
}

TouchButton_Status_t TouchButtonRead(TouchButton_Handle_t *Dev){
	TouchButtonState_t Previous_State = Dev->State;
    Dev->State = Dev->IO_Driver.read(Dev->TopLeftBound, Dev->BottomRightBound);
    if(Previous_State != Dev->State){
    	return TouchButtonChanged;
    } else {
    	return TouchButtonUnchanged;
    }
}
