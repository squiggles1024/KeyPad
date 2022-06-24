/*
 * KeyPad.h
 *
 *  Created on: Jun 23, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_
#include <stdint.h>
#include "Button.h"
#include "Joystick.h"
#include "TouchButton.h"
#include "SerialLED.h"

#define NUMBER_OF_BUTTONS (NUMBER_OF_IO_EXPANDERS*PINS_PER_EXPANDER) //64

typedef enum{
	MouseChange,
	KeyboardData,
	NoKeypadChange
}KeypadFlagStatus_t;

typedef enum{
    ButtonFunction,
    TouchButtonFunction,
	JoystickFunction
}KeypadFunctionType_t;

typedef struct{
    uint8_t modifiers;
    const uint8_t reserved;
    uint8_t keycodes[NUMBER_OF_BUTTONS];
}__attribute__((packed)) KeyPad_KeyboardUSBBuffer_t;

typedef struct{
    uint8_t button_reg;
    int8_t x_movement;
    int8_t y_movement;
    int8_t wheel_movement;
}__attribute__((packed)) KeyPad_MouseUSBBuffer_t;

typedef struct{
	KeypadFlagStatus_t MouseFlag;
	KeypadFlagStatus_t KeyboardFlag;
	Button_Handle_t Buttons[NUMBER_OF_BUTTONS];
	Joystick_Handle_t Joystick;
	SerialLED_Handle_t LED[NUMBER_OF_LEDS];
	TouchButton_Handle_t TouchButton[12];
	KeyPad_KeyboardUSBBuffer_t KeyboardUSBBuffer;
	KeyPad_MouseUSBBuffer_t MouseUSBBuffer;
}KeyPadHandle_t;

void KeyPadInit();
void UpdateKeyPad();
void AssignNewButtonFunction(uint8_t ButtonIndex, KeyFunction_t NewFunction);
void AssignNewJoystickFunction(Joystick_Init_Struct_t Settings);
void AssignNewTouchButtonFunction(uint8_t TouchButtonIndex);

extern KeyPadHandle_t Keypad;

#endif /* INC_KEYPAD_H_ */
