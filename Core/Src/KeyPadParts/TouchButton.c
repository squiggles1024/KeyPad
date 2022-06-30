/*
 * TouchButton.c
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "TouchButton.h"

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief:Initializes Touch button and underlying hardware
 *@Params: Init struct w/ desired user settings, Device handle pointer, low level IO Driver
 *@Return: None
 *@Precondition: None
 *@Postcondition: Touchbutton hardware (GPIO, I2C, FT6206) will be initialized
 **************************************//**************************************/
void TouchButtonInit(TouchButton_Init_Struct_t Settings, TouchButton_Handle_t *Dev, TouchButton_IO_Drv_t IO_Driver){
    Dev->IO_Driver = IO_Driver;
    Dev->KeyFunction = Settings.KeyFunction;
    Dev->TopLeftBound = Settings.TopLeftBound;
    Dev->BottomRightBound = Settings.BottomRightBound;
    Dev->State = TouchButtonUnpressed;
    Dev->IO_Driver.init();
}

/**************************************//**************************************
 *@Brief: Change function of a Touch Button
 *@Params: Touch button handle pointer, desired button function
 *@Return: None
 *@Precondition: Touch button should be initialized
 *@Postcondition: Touch button will have its Function member changed.
 **************************************//**************************************/
void TouchButtonSetFunction(TouchButton_Handle_t* Dev, KeyFunction_t NewFunction){
    Dev->KeyFunction = NewFunction;
}

/**************************************//**************************************
 *@Brief: Reads a touch button
 *@Params: Touch button to read
 *@Return: TouchButtonChanged if it goes from Pressed->Unpressed or Unpressed->Pressed
 *@Precondition: Touch button should be initialized
 *@Postcondition: Touchbutton.State will be updated
 **************************************//**************************************/
TouchButton_Status_t TouchButtonRead(TouchButton_Handle_t *Dev){
	TouchButtonState_t Previous_State = Dev->State;
    Dev->State = Dev->IO_Driver.read(Dev->TopLeftBound, Dev->BottomRightBound);
    if(Previous_State != Dev->State){
    	return TouchButtonChanged;
    } else {
    	return TouchButtonUnchanged;
    }
}
