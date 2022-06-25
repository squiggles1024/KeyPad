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

#define TOUCH_BUTTON_HALFWIDTH (31) //62 x 62 Pixels
#define TOUCH_BUTTONS_PER_ROW (4)
#define TOUCH_BUTTON_ROW_PITCH (80)
#define TOUCH_BUTTON_COLUMN_PITCH (60)
#define TOUCH_BUTTON1_X_CENTER (40)
#define TOUCH_BUTTON1_Y_CENTER (60)

typedef enum{
    TouchButtonChanged,
	TouchButtonUnchanged
}TouchButton_Status_t;

typedef struct{
	TouchButtonCoordinate_t TopLeftBound;
	TouchButtonCoordinate_t BottomRightBound;
	KeyFunction_t KeyFunction;
}TouchButton_Init_Struct_t;

typedef struct{
	TouchButtonCoordinate_t TopLeftBound;
	TouchButtonCoordinate_t BottomRightBound;
	KeyFunction_t KeyFunction;
    TouchButtonState_t State;
    TouchButton_IO_Drv_t IO_Driver;
}TouchButton_Handle_t;

void TouchButtonInit(TouchButton_Init_Struct_t Settings, TouchButton_Handle_t *Dev, TouchButton_IO_Drv_t IO_Driver);
TouchButton_Status_t TouchButtonRead(TouchButton_Handle_t *Dev);
void TouchButtonSetFunction(TouchButton_Handle_t* Dev, KeyFunction_t NewFunction);



#endif /* INC_KEYPADPARTS_TOUCHBUTTON_H_ */
