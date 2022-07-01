/*
 * KeyPad.h
 *
 *  Created on: Jun 23, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <stdint.h>
#include "Button.h"
#include "Joystick.h"
#include "TouchButton.h"
#include "SerialLED.h"

/**************************************//**************************************//**************************************
 * Public Defines
 **************************************//**************************************//**************************************/
#define NUMBER_OF_BUTTONS (NUMBER_OF_IO_EXPANDERS*PINS_PER_EXPANDER) //64
#define SIMULTANEOUS_BUTTONS (37) //34 Buttons + 1 stick button + 1 joystick direction + 1 touch button can be pressed simultaneously.
#define CONFIG_CHANGE_BYTES  (6)  //1 byte = button type, 1 = Button address, 4 = button function

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	NoKeypadChange,
	MouseDataAvailable,
	KeyboardDataAvailable,
}KeypadFlagStatus_t;

typedef enum{
	ButtonType,
	TouchButtonType,
	JoystickType
}KeyType_t;

/**************************************//**************************************//**************************************
 * Structs
 **************************************//**************************************//**************************************/
typedef struct{
    KeyType_t KeyType;
    uint8_t KeyAddress;
    KeyFunction_t NewFunction;
}__attribute__((packed))KeyPadDataFrame_t; //Data Received from desktop application for key rebinding

typedef struct{
    uint8_t modifiers;
    const uint8_t reserved;
    uint8_t keycodes[SIMULTANEOUS_BUTTONS];
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
	KeypadFlagStatus_t NewDataFlag;
	Button_Handle_t Buttons[NUMBER_OF_BUTTONS];
	Joystick_Handle_t Joystick;
	SerialLED_Handle_t LED[NUMBER_OF_LEDS];
	TouchButton_Handle_t TouchButton[NUMBER_OF_TOUCH_BUTTONS];
	KeyPad_KeyboardUSBBuffer_t KeyboardUSBBuffer;
	KeyPad_MouseUSBBuffer_t MouseUSBBuffer;
}KeyPadHandle_t;

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
void KeyPadInit();
void UpdateKeyPadTxBuffers();
void KeyPadSendData();
void AssignNewButtonFunction(uint8_t ButtonIndex, KeyFunction_t NewFunction);
void AssignNewJoystickFunction(JoystickState_t Direction, KeyFunction_t NewFunction);
void AssignNewTouchButtonFunction(uint8_t TouchButtonIndex, KeyFunction_t NewFunction);

/**************************************//**************************************//**************************************
 * Exported Variables
 **************************************//**************************************//**************************************/
extern KeyPadHandle_t KeyPad;

#endif /* INC_KEYPAD_H_ */
