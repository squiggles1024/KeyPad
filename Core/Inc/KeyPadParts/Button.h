/*
 * button.h
 *
 *  Created on: May 18, 2022
 *      Author: evanl
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "KeyFunctions.h"
#include "Button_Hardware.h"
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	ButtonChanged = 0,
	ButtonUnchanged,
	ButtonErr
}ButtonStatus_t;

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef struct{
	uint8_t ButtonIDNumber;
	KeyFunction_t KeyFunction;
}Button_Init_Struct_t;

typedef struct{
	uint8_t ButtonIDNumber;
	KeyFunction_t KeyFunction;
    ButtonState_t State;
    Button_IO_Drv_t IO_Driver;
}Button_Handle_t;

/**************************************//**************************************//**************************************
 * Public Function Declarations
 **************************************//**************************************//**************************************/
void ButtonInit(Button_Init_Struct_t Settings, Button_Handle_t *Button, Button_IO_Drv_t IO);
ButtonStatus_t ButtonRead(Button_Handle_t *Button);
void ButtonSetFunction(Button_Handle_t* Button, KeyFunction_t NewFunction);

#endif /* INC_BUTTON_H_ */
