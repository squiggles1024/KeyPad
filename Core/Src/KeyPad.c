/*
 * KeyPad.c
 *
 *  Created on: Jun 23, 2022
 *      Author: evanl
 */

#include "KeyPad.h"

KeyPadHandle_t Keypad;

static void KeypadInitButtons();
static void KeypadInitLEDs();
static void KeypadInitTouchButtons();
static void KeypadInitJoystick();

void KeyPadInit(){
	  KeypadInitLEDs();
	  KeypadInitTouchButtons();
	  KeypadInitButtons();
	  KeypadInitJoystick();
}

static void KeypadInitButtons(){
	Button_Init_Struct_t Settings = {
			.KeyFunction = 0,
			.ModKeyFunction = 0,
			.MouseFunction = 0,
			.WheelFunction = 0,
	};
	for(uint8_t i = 0; i < NUMBER_OF_IO_EXPANDERS*PINS_PER_EXPANDER; i++){
		Settings.ButtonIDNumber = i;
        ButtonInit(Settings, &Keypad.Buttons[i], ButtonIO_Driver);
	}
}

void KeypadInitJoystick(){
    Joystick_Init_Struct_t Settings = {
    		.DeadZone = 2000,
			.Mode = Joystick4Way
    };
    JoystickInit(Settings, &Keypad.Joystick, JoystickIO_Driver);
}

void KeypadInitLEDs(){
	SerialLED_InitStruct_t LED_Settings[4] = {
			{.red= 0xFF,
			.green = 0x00,
			.blue = 0x00},

			{.red = 0x00,
			.green = 0xFF,
			.blue = 0x00},

			{.red = 0x00,
			 .green = 0x00,
			 .blue = 0xFF
			},
			{.red = 0xFF,
			 .green = 0xFF,
			 .blue = 0x00
			}
	};
	for(uint8_t i = 0; i < NUMBER_OF_LEDS; i++){
		LED_Settings[i].address = i;
		SerialLEDInit(LED_Settings[i],&Keypad.LED[i],LED_Drv);
	}
}

void KeypadInitTouchButtons(){
	TouchButton_Init_Struct_t Settings = {
			.TopLeftBound = {
					.X_Position = 40 - 31,
					.Y_Position = 60 - 31
			},
			.BottomRightBound = {
					.X_Position = 40 + 31,
					.Y_Position = 60 + 31
			},
			.KeyFunction = 0,
			.ModKeyFunction = 0,
			.WheelFunction = 0,
			.MouseFunction = 0
	};
	TouchButtonInit(Settings, &Keypad.TouchButton[0], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 120 - 31;
	Settings.BottomRightBound.X_Position = 120 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[1], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 200 - 31;
	Settings.BottomRightBound.X_Position = 200 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[2], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 280 - 31;
	Settings.BottomRightBound.X_Position = 280 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[3], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 40 - 31;
	Settings.BottomRightBound.X_Position = 40 + 31;
	Settings.TopLeftBound.Y_Position = 120 - 31;
	Settings.BottomRightBound.Y_Position = 120 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[4], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 120 - 31;
	Settings.BottomRightBound.X_Position = 120 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[5], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 200 - 31;
	Settings.BottomRightBound.X_Position = 200 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[6], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 280 - 31;
	Settings.BottomRightBound.X_Position = 280 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[7], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 40 - 31;
	Settings.BottomRightBound.X_Position = 40 + 31;
	Settings.TopLeftBound.Y_Position = 180 - 31;
	Settings.BottomRightBound.Y_Position = 180 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[8], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 120 - 31;
	Settings.BottomRightBound.X_Position = 120 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[9], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 200 - 31;
	Settings.BottomRightBound.X_Position = 200 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[10], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 280 - 31;
	Settings.BottomRightBound.X_Position = 280 + 31;
	TouchButtonInit(Settings, &Keypad.TouchButton[11], TouchButton_IO_Driver);
}
