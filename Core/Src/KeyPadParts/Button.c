/*
 * Button.c
 *
 *  Created on: May 18, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "Button.h"

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes a Button Device Handle
 *@Params: Init struct with settings, Handle to initialized, low level IO driver
 *@Return: None
 *@Precondition: None
 *@Postcondition: Button handle will be initialized and ready to use
 **************************************//**************************************/
void ButtonInit(Button_Init_Struct_t Settings, Button_Handle_t *Button, Button_IO_Drv_t IO){
	Button->IO_Driver.init   = IO.init;
	Button->IO_Driver.deinit = IO.deinit;
	Button->IO_Driver.read   = IO.read;
	Button->IO_Driver.write  = IO.write;
	Button->IO_Driver.ioctl  = IO.ioctl;
	Button->IO_Driver.init();

	Button->ButtonIDNumber = Settings.ButtonIDNumber;
	Button->KeyFunction = Settings.KeyFunction;
	Button->ModKeyFunction = Settings.ModKeyFunction;
	Button->MouseFunction = Settings.MouseFunction;
	Button->State = ButtonUnpressed;
}

/**************************************//**************************************
 *@Brief: Updates the state of a button
 *@Params: Button handle to read
 *@Return: ButtonChanged if the button changed states, otherwise ButtonUnchanged
 *@Precondition: ButtonHandle should be initialized/
 *@Postcondition: ButtonState in the ButtonHandle will be updated.
 **************************************//**************************************/
ButtonStatus_t ButtonRead(Button_Handle_t *Button){
    ButtonState_t Previous_State = Button->State;
    Button->State = Button->IO_Driver.read(Button->ButtonIDNumber);
    if(Previous_State != Button->State){
    	return ButtonChanged;
    } else {
    	return ButtonUnchanged;
    }
}

/**************************************//**************************************
 *@Brief: Assigns functionality to a ButtonHandle
 *@Params: ButtonHandle to modify
 *@Return: None
 *@Precondition: None
 *@Postcondition: ButtonHandle have its functions assigned according to passed parameters.
 **************************************//**************************************/
void ButtonSetFunction(Button_Handle_t* Button, KeyScanCode KeyFunc, ModifierKey ModKey, MouseClick MouseFunction, MouseWheel WheelFunction){
	Button->KeyFunction = KeyFunc;
	Button->ModKeyFunction = ModKey;
	Button->MouseFunction = MouseFunction;
	Button->WheelFunction = WheelFunction;
}
