/*
 * KeyPad.c
 *
 *  Created on: Jun 23, 2022
 *      Author: evanl
 */

#include "KeyPad.h"
#include "KeyPadConfig.h"
#include "usb_device.h"
#include "usbd_customhid.h"

KeyPadHandle_t KeyPad;

static void KeypadInitButtons();
static void KeypadInitLEDs();
static void KeypadInitTouchButtons();
static void KeypadInitJoystick();

void KeyPadInit(){
	  KeyPad.MouseUSBBuffer.button_reg = 0;
	  KeyPad.MouseUSBBuffer.wheel_movement = 0;
	  KeyPad.MouseUSBBuffer.x_movement = 0;
	  KeyPad.MouseUSBBuffer.y_movement = 0;
	  KeyPad.KeyboardUSBBuffer.modifiers = 0;
	  for(uint8_t i = 0; i < SIMULTANEOUS_BUTTONS; i++){
          KeyPad.KeyboardUSBBuffer.keycodes[i] = KEY_NONE;
	  }
	  KeypadInitLEDs();
	  KeypadInitTouchButtons();
	  KeypadInitButtons();
	  KeypadInitJoystick();
	  MX_USB_DEVICE_Init();
}

void UpdateKeyPadTxBuffers(){
	uint8_t PressedKeys = 0;           //Track number of pressed keys (For adding KeyScanCodes to KeyboardUSBBuffer)
	uint8_t MouseButtons = 0;          //Stores Mouse buttons clicked (will later be added to MouseUSBBuffer
	uint8_t KeyBoardModKeys = 0;       //Stores Modifier Keys pressed (will later be added to KeyboardUSBBuffer)


	KeypadFlagStatus_t KeyboardStatus = NoKeypadChange; //Keep track of whether a keyboard button has changed. Assigned to KeyPad.KeyboardFlag later.
	KeypadFlagStatus_t MouseStatus = NoKeypadChange;    //Keep track of whether a keyboard button has changed. Assigned to KeyPad.KeyboardFlag later.

	MouseWheel_t WheelMovement = 0;
    ButtonStatus_t ButtonStatus;

    //Loop through all buttons
    for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++){
    	//Update Button State and store its status
        ButtonStatus = ButtonRead(&KeyPad.Buttons[i]);
        if(KeyPad.Buttons[i].State == ButtonPressed){
            if(KeyPad.Buttons[i].KeyFunction.KeyScanCode != KEY_NONE){
                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Buttons[i].KeyFunction.KeyScanCode;
                PressedKeys++;
            }

            if(KeyPad.Buttons[i].KeyFunction.ModifierKey != KEY_MOD_NOMOD){
            	KeyBoardModKeys |= KeyPad.Buttons[i].KeyFunction.ModifierKey;
            }

            if(KeyPad.Buttons[i].KeyFunction.MouseClick != MOUSE_CLICK_NONE){
            	MouseButtons |= KeyPad.Buttons[i].KeyFunction.MouseClick;
            }

            if(KeyPad.Buttons[i].KeyFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                WheelMovement += KeyPad.Buttons[i].KeyFunction.MouseWheel;
            }
        }

        if(ButtonStatus == ButtonChanged){
        	if(KeyPad.Buttons[i].KeyFunction.KeyScanCode != KEY_NONE || KeyPad.Buttons[i].KeyFunction.ModifierKey != KEY_MOD_NOMOD){
        		KeyboardStatus = KeyboardDataAvailable;
        	}

        	if(KeyPad.Buttons[i].KeyFunction.MouseClick != MOUSE_CLICK_NONE){
        		MouseStatus = MouseDataAvailable;
        	}
        }
    }

    TouchButton_Status_t TouchButtonStatus;
    //Loop through all touch buttons
    for(uint8_t i = 0; i < NUMBER_OF_TOUCH_BUTTONS; i++){
    	//Update Button State and store its status
    	TouchButtonStatus = TouchButtonRead(&KeyPad.TouchButton[i]);
        if(KeyPad.TouchButton[i].State == TouchButtonPressed){
            if(KeyPad.TouchButton[i].KeyFunction.KeyScanCode != KEY_NONE){
                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.TouchButton[i].KeyFunction.KeyScanCode;
                PressedKeys++;
            }

            if(KeyPad.TouchButton[i].KeyFunction.ModifierKey != KEY_MOD_NOMOD){
            	KeyBoardModKeys |= KeyPad.TouchButton[i].KeyFunction.ModifierKey;
            }

            if(KeyPad.TouchButton[i].KeyFunction.MouseClick != MOUSE_CLICK_NONE){
            	MouseButtons |= KeyPad.TouchButton[i].KeyFunction.MouseClick;
            }

            if(KeyPad.TouchButton[i].KeyFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                WheelMovement += KeyPad.TouchButton[i].KeyFunction.MouseWheel;
            }

        }

        if(TouchButtonStatus == TouchButtonChanged){
        	if(KeyPad.TouchButton[i].KeyFunction.KeyScanCode != KEY_NONE || KeyPad.TouchButton[i].KeyFunction.ModifierKey != KEY_MOD_NOMOD){
        		KeyboardStatus = KeyboardDataAvailable;
        	}

        	if(KeyPad.TouchButton[i].KeyFunction.MouseClick != MOUSE_CLICK_NONE){
        		MouseStatus = MouseDataAvailable;
        	}
        }

    }

    //Handle Joystick
    JoystickStatus_t JoystickStatus;
    JoystickStatus = JoystickRead(&KeyPad.Joystick);

	switch(KeyPad.Joystick.Position){
			case(Joystick_Up):
                            if(KeyPad.Joystick.UpFunction.KeyScanCode != KEY_NONE){
                                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Joystick.UpFunction.KeyScanCode;
                                PressedKeys++;
                            }

                            if(KeyPad.Joystick.UpFunction.ModifierKey != KEY_MOD_NOMOD){
                            	KeyBoardModKeys |= KeyPad.Joystick.UpFunction.ModifierKey;
                            }

                            if(KeyPad.Joystick.UpFunction.MouseClick != MOUSE_CLICK_NONE){
                            	MouseButtons |= KeyPad.Joystick.UpFunction.MouseClick;
                            }

                            if(KeyPad.Joystick.UpFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                                WheelMovement += KeyPad.Joystick.UpFunction.MouseWheel;
                            }


                            if(JoystickStatus == JoystickChanged){
                            	if(KeyPad.Joystick.UpFunction.KeyScanCode != KEY_NONE || KeyPad.Joystick.UpFunction.ModifierKey != KEY_MOD_NOMOD){
                            		KeyboardStatus = KeyboardDataAvailable;
                            	}

                            	if(KeyPad.Joystick.UpFunction.MouseClick != MOUSE_CLICK_NONE){
                            		MouseStatus = MouseDataAvailable;
                            	}
                            }
					break;
			case(Joystick_UpRight):
                            if(KeyPad.Joystick.UpRightFunction.KeyScanCode != KEY_NONE){
                                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Joystick.UpRightFunction.KeyScanCode;
                                PressedKeys++;
                            }

                            if(KeyPad.Joystick.UpRightFunction.ModifierKey != KEY_MOD_NOMOD){
                            	KeyBoardModKeys |= KeyPad.Joystick.UpRightFunction.ModifierKey;
                            }

                            if(KeyPad.Joystick.UpRightFunction.MouseClick != MOUSE_CLICK_NONE){
                            	MouseButtons |= KeyPad.Joystick.UpRightFunction.MouseClick;
                            }

                            if(KeyPad.Joystick.UpRightFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                                WheelMovement += KeyPad.Joystick.UpRightFunction.MouseWheel;
                            }


                            if(JoystickStatus == JoystickChanged){
                            	if(KeyPad.Joystick.UpRightFunction.KeyScanCode != KEY_NONE || KeyPad.Joystick.UpRightFunction.ModifierKey != KEY_MOD_NOMOD){
                            		KeyboardStatus = KeyboardDataAvailable;
                            	}

                            	if(KeyPad.Joystick.UpRightFunction.MouseClick != MOUSE_CLICK_NONE){
                            		MouseStatus = MouseDataAvailable;
                            	}
                            }
					break;
			case(Joystick_Right):
                            if(KeyPad.Joystick.RightFunction.KeyScanCode != KEY_NONE){
                                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Joystick.RightFunction.KeyScanCode;
                                PressedKeys++;
                            }

                            if(KeyPad.Joystick.RightFunction.ModifierKey != KEY_MOD_NOMOD){
                            	KeyBoardModKeys |= KeyPad.Joystick.RightFunction.ModifierKey;
                            }

                            if(KeyPad.Joystick.RightFunction.MouseClick != MOUSE_CLICK_NONE){
                            	MouseButtons |= KeyPad.Joystick.RightFunction.MouseClick;
                            }

                            if(KeyPad.Joystick.RightFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                                WheelMovement += KeyPad.Joystick.RightFunction.MouseWheel;
                            }


                            if(JoystickStatus == JoystickChanged){
                            	if(KeyPad.Joystick.RightFunction.KeyScanCode != KEY_NONE || KeyPad.Joystick.RightFunction.ModifierKey != KEY_MOD_NOMOD){
                            		KeyboardStatus = KeyboardDataAvailable;
                            	}

                            	if(KeyPad.Joystick.RightFunction.MouseClick != MOUSE_CLICK_NONE){
                            		MouseStatus = MouseDataAvailable;
                            	}
                            }
					break;
			case(Joystick_DownRight):
                            if(KeyPad.Joystick.DownRightFunction.KeyScanCode != KEY_NONE){
                                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Joystick.DownRightFunction.KeyScanCode;
                                PressedKeys++;
                            }

                            if(KeyPad.Joystick.DownRightFunction.ModifierKey != KEY_MOD_NOMOD){
                            	KeyBoardModKeys |= KeyPad.Joystick.DownRightFunction.ModifierKey;
                            }

                            if(KeyPad.Joystick.DownRightFunction.MouseClick != MOUSE_CLICK_NONE){
                            	MouseButtons |= KeyPad.Joystick.DownRightFunction.MouseClick;
                            }

                            if(KeyPad.Joystick.DownRightFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                                WheelMovement += KeyPad.Joystick.DownRightFunction.MouseWheel;
                            }


                            if(JoystickStatus == JoystickChanged){
                            	if(KeyPad.Joystick.DownRightFunction.KeyScanCode != KEY_NONE || KeyPad.Joystick.DownRightFunction.ModifierKey != KEY_MOD_NOMOD){
                            		KeyboardStatus = KeyboardDataAvailable;
                            	}

                            	if(KeyPad.Joystick.DownRightFunction.MouseClick != MOUSE_CLICK_NONE){
                            		MouseStatus = MouseDataAvailable;
                            	}
                            }
					break;
			case(Joystick_Down):
                            if(KeyPad.Joystick.DownFunction.KeyScanCode != KEY_NONE){
                                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Joystick.DownFunction.KeyScanCode;
                                PressedKeys++;
                            }

                            if(KeyPad.Joystick.DownFunction.ModifierKey != KEY_MOD_NOMOD){
                            	KeyBoardModKeys |= KeyPad.Joystick.DownFunction.ModifierKey;
                            }

                            if(KeyPad.Joystick.DownFunction.MouseClick != MOUSE_CLICK_NONE){
                            	MouseButtons |= KeyPad.Joystick.DownFunction.MouseClick;
                            }

                            if(KeyPad.Joystick.DownFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                                WheelMovement += KeyPad.Joystick.DownFunction.MouseWheel;
                            }


                            if(JoystickStatus == JoystickChanged){
                            	if(KeyPad.Joystick.DownFunction.KeyScanCode != KEY_NONE || KeyPad.Joystick.DownFunction.ModifierKey != KEY_MOD_NOMOD){
                            		KeyboardStatus = KeyboardDataAvailable;
                            	}

                            	if(KeyPad.Joystick.DownFunction.MouseClick != MOUSE_CLICK_NONE){
                            		MouseStatus = MouseDataAvailable;
                            	}
                            }
					break;
			case(Joystick_DownLeft):
                            if(KeyPad.Joystick.DownLeftFunction.KeyScanCode != KEY_NONE){
                                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Joystick.DownLeftFunction.KeyScanCode;
                                PressedKeys++;
                            }

                            if(KeyPad.Joystick.DownLeftFunction.ModifierKey != KEY_MOD_NOMOD){
                            	KeyBoardModKeys |= KeyPad.Joystick.DownLeftFunction.ModifierKey;
                            }

                            if(KeyPad.Joystick.DownLeftFunction.MouseClick != MOUSE_CLICK_NONE){
                            	MouseButtons |= KeyPad.Joystick.DownLeftFunction.MouseClick;
                            }

                            if(KeyPad.Joystick.DownLeftFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                                WheelMovement += KeyPad.Joystick.DownLeftFunction.MouseWheel;
                            }


                            if(JoystickStatus == JoystickChanged){
                            	if(KeyPad.Joystick.DownLeftFunction.KeyScanCode != KEY_NONE || KeyPad.Joystick.DownLeftFunction.ModifierKey != KEY_MOD_NOMOD){
                            		KeyboardStatus = KeyboardDataAvailable;
                            	}

                            	if(KeyPad.Joystick.DownLeftFunction.MouseClick != MOUSE_CLICK_NONE){
                            		MouseStatus = MouseDataAvailable;
                            	}
                            }
					break;
			case(Joystick_Left):
                            if(KeyPad.Joystick.LeftFunction.KeyScanCode != KEY_NONE){
                                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Joystick.LeftFunction.KeyScanCode;
                                PressedKeys++;
                            }

                            if(KeyPad.Joystick.LeftFunction.ModifierKey != KEY_MOD_NOMOD){
                            	KeyBoardModKeys |= KeyPad.Joystick.LeftFunction.ModifierKey;
                            }

                            if(KeyPad.Joystick.LeftFunction.MouseClick != MOUSE_CLICK_NONE){
                            	MouseButtons |= KeyPad.Joystick.LeftFunction.MouseClick;
                            }

                            if(KeyPad.Joystick.LeftFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                                WheelMovement += KeyPad.Joystick.LeftFunction.MouseWheel;
                            }


                            if(JoystickStatus == JoystickChanged){
                            	if(KeyPad.Joystick.LeftFunction.KeyScanCode != KEY_NONE || KeyPad.Joystick.LeftFunction.ModifierKey != KEY_MOD_NOMOD){
                            		KeyboardStatus = KeyboardDataAvailable;
                            	}

                            	if(KeyPad.Joystick.LeftFunction.MouseClick != MOUSE_CLICK_NONE){
                            		MouseStatus = MouseDataAvailable;
                            	}
                            }
					break;
			case(Joystick_UpLeft):
                            if(KeyPad.Joystick.UpLeftFunction.KeyScanCode != KEY_NONE){
                                KeyPad.KeyboardUSBBuffer.keycodes[PressedKeys] = KeyPad.Joystick.UpLeftFunction.KeyScanCode;
                                PressedKeys++;
                            }

                            if(KeyPad.Joystick.UpLeftFunction.ModifierKey != KEY_MOD_NOMOD){
                            	KeyBoardModKeys |= KeyPad.Joystick.UpLeftFunction.ModifierKey;
                            }

                            if(KeyPad.Joystick.UpLeftFunction.MouseClick != MOUSE_CLICK_NONE){
                            	MouseButtons |= KeyPad.Joystick.UpLeftFunction.MouseClick;
                            }

                            if(KeyPad.Joystick.UpLeftFunction.MouseWheel != MOUSE_WHEEL_NO_MOVE){
                                WheelMovement += KeyPad.Joystick.UpLeftFunction.MouseWheel;
                            }


                            if(JoystickStatus == JoystickChanged){
                            	if(KeyPad.Joystick.UpLeftFunction.KeyScanCode != KEY_NONE || KeyPad.Joystick.UpLeftFunction.ModifierKey != KEY_MOD_NOMOD){
                            		KeyboardStatus = KeyboardDataAvailable;
                            	}

                            	if(KeyPad.Joystick.UpLeftFunction.MouseClick != MOUSE_CLICK_NONE){
                            		MouseStatus = MouseDataAvailable;
                            	}
                            }
                    break;
			default:
                if(JoystickStatus == JoystickChanged){
                	KeyboardStatus = KeyboardDataAvailable;
                	MouseStatus = MouseDataAvailable;
                }
				break;

	 }



    //Zero all unused buffer space
    for(uint8_t i = PressedKeys; i < SIMULTANEOUS_BUTTONS; i++){
         KeyPad.KeyboardUSBBuffer.keycodes[i] = KEY_NONE;
    }

    if(KeyPad.MouseUSBBuffer.wheel_movement != WheelMovement || WheelMovement != 0){
    	MouseStatus = MouseDataAvailable;
    	KeyPad.MouseUSBBuffer.wheel_movement = WheelMovement;
    } else {

    }

    if(KeyPad.KeyboardUSBBuffer.modifiers != KeyBoardModKeys){
        KeyPad.KeyboardUSBBuffer.modifiers = KeyBoardModKeys;
    }

    if(KeyPad.MouseUSBBuffer.button_reg != MouseButtons){
        KeyPad.MouseUSBBuffer.button_reg = MouseButtons;
    }

    if(KeyboardStatus == KeyboardDataAvailable){
    	KeyPad.KeyboardFlag = KeyboardDataAvailable;
    }

    if(MouseStatus == MouseDataAvailable){
        KeyPad.MouseFlag = MouseDataAvailable;
    }

}

static void KeypadInitButtons(){
	Button_Init_Struct_t Settings;
	for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++){
		Settings.ButtonIDNumber = i;
		Settings.KeyFunction = ButtonFunctionsDefault[i];
        ButtonInit(Settings, &KeyPad.Buttons[i], ButtonIO_Driver);
	}
}

static void KeypadInitJoystick(){
    Joystick_Init_Struct_t Settings = {
    		.DeadZone = 3500,
			.Mode = Joystick4Way,
			.UpFunction = JoystickFunctionsDefault[0],
			.UpRightFunction = JoystickFunctionsDefault[1],
			.RightFunction = JoystickFunctionsDefault[2],
			.DownRightFunction = JoystickFunctionsDefault[3],
			.DownFunction = JoystickFunctionsDefault[4],
			.DownLeftFunction = JoystickFunctionsDefault[5],
			.LeftFunction = JoystickFunctionsDefault[6],
			.UpLeftFunction = JoystickFunctionsDefault[7]
    };
    JoystickInit(Settings, &KeyPad.Joystick, JoystickIO_Driver);
}

static void KeypadInitLEDs(){
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
		SerialLEDInit(LED_Settings[i],&KeyPad.LED[i],LED_Drv);
	}
}

static void KeypadInitTouchButtons(){
	TouchButton_Init_Struct_t Settings;
	for(uint8_t i = 0; i < NUMBER_OF_TOUCH_BUTTONS; i++){                                                                                                     // Coefficients:
        Settings.TopLeftBound.X_Position = (TOUCH_BUTTON1_X_CENTER - TOUCH_BUTTON_HALFWIDTH) + TOUCH_BUTTON_ROW_PITCH * ((i % TOUCH_BUTTONS_PER_ROW));        // 012301230123
        Settings.BottomRightBound.X_Position = (TOUCH_BUTTON1_X_CENTER + TOUCH_BUTTON_HALFWIDTH) + TOUCH_BUTTON_ROW_PITCH * ((i % TOUCH_BUTTONS_PER_ROW));    // 012301230123
        Settings.TopLeftBound.Y_Position = (TOUCH_BUTTON1_Y_CENTER - TOUCH_BUTTON_HALFWIDTH) + TOUCH_BUTTON_COLUMN_PITCH * ((i / TOUCH_BUTTONS_PER_ROW));     // 111122223333
        Settings.BottomRightBound.Y_Position = (TOUCH_BUTTON1_Y_CENTER + TOUCH_BUTTON_HALFWIDTH) + TOUCH_BUTTON_COLUMN_PITCH * ((i / TOUCH_BUTTONS_PER_ROW)); // 111122223333
        Settings.KeyFunction = TouchButtonFunctionsDefault[i];
        TouchButtonInit(Settings, &KeyPad.TouchButton[i], TouchButton_IO_Driver);

	}
}
void KeyPadSendData(){
	uint8_t i = 0;
	if(hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED){
		i++;
	}
	 if(KeyPad.KeyboardFlag == KeyboardDataAvailable){
		 USBD_LL_Resume(&hUsbDeviceFS);
         USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&KeyPad.KeyboardUSBBuffer, sizeof(KeyPad_KeyboardUSBBuffer_t), KEYBOARD_HID_EPIN_ADDR);
         KeyPad.KeyboardFlag = NoKeypadChange;
	 }

	 if(KeyPad.MouseFlag == MouseDataAvailable){
		  USBD_LL_Resume(&hUsbDeviceFS);
		  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&KeyPad.MouseUSBBuffer, sizeof(KeyPad_MouseUSBBuffer_t), MOUSE_HID_EPIN_ADDR);
		  KeyPad.MouseFlag = NoKeypadChange;
	 }
}

void AssignNewButtonFunction(uint8_t ButtonIndex, KeyFunction_t NewFunction){
	if(ButtonIndex >= NUMBER_OF_BUTTONS){
		return;
	} else {
		KeyPad.Buttons[ButtonIndex].KeyFunction = NewFunction;
	}

}

void AssignNewTouchButtonFunction(uint8_t TouchButtonIndex, KeyFunction_t NewFunction){
	if(TouchButtonIndex >= NUMBER_OF_TOUCH_BUTTONS){
		return;
	} else {
        KeyPad.TouchButton[TouchButtonIndex].KeyFunction = NewFunction;
	}
}

void AssignNewJoystickFunction(JoystickState_t Direction, KeyFunction_t NewFunction){
	if(Direction > Joystick_DownRight && Direction <= JoystickNeutral){
		return;
	}

	switch(Direction){
	case(Joystick_Up):
			KeyPad.Joystick.UpFunction = NewFunction;
			break;
	case(Joystick_UpRight):
		    KeyPad.Joystick.UpRightFunction = NewFunction;
			break;
	case(Joystick_Right):
		    KeyPad.Joystick.RightFunction = NewFunction;
			break;
	case(Joystick_DownRight):
		    KeyPad.Joystick.DownRightFunction = NewFunction;
			break;
	case(Joystick_Down):
    	    KeyPad.Joystick.DownFunction = NewFunction;
			break;
	case(Joystick_DownLeft):
    	    KeyPad.Joystick.DownLeftFunction = NewFunction;
			break;
	case(Joystick_Left):
    	    KeyPad.Joystick.LeftFunction = NewFunction;
			break;
	case(Joystick_UpLeft):
    	    KeyPad.Joystick.UpLeftFunction = NewFunction;
			break;
	default:
			break;
	}
}




