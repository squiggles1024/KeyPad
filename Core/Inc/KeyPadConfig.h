/*
 * KeyPadConfig.h
 *
 *  Created on: Jun 24, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPADCONFIG_H_
#define INC_KEYPADCONFIG_H_

/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "KeyFunctions.h"
#include "KeyPad.h"

/**************************************//**************************************//**************************************
 * Exported Variables
 **************************************//**************************************//**************************************/
extern KeyFunction_t ButtonFunctionsDefault[NUMBER_OF_BUTTONS];
extern KeyFunction_t TouchButtonFunctionsDefault[NUMBER_OF_TOUCH_BUTTONS];
extern KeyFunction_t JoystickFunctionsDefault[JOYSTICK_DIRECTIONS];

#endif /* INC_KEYPADCONFIG_H_ */
