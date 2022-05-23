/*
 * Joystick_Hardware.h
 *
 *  Created on: May 20, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPADPARTS_JOYSTICK_HARDWARE_H_
#define INC_KEYPADPARTS_JOYSTICK_HARDWARE_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	JoystickNeutral = 0,
	Joystick_Right,
	Joystick_UpRight,
	Joystick_Up,
	Joystick_UpLeft,
	Joystick_Left,
	Joystick_DownLeft,
	Joystick_Down,
	Joystick_DownRight
}JoystickState_t;

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef struct{
    void (*init)(void); //4 byte buffer to store data
    void (*deinit)(void);
    JoystickState_t (*read)(uint16_t, int16_t*, int16_t*); //Deadzone, X Pos buffer, Y Pos buffer
    void (*write)(void);
    uint8_t (*ioctl)(uint8_t);
}Joystick_IO_Drv_t;

/**************************************//**************************************//**************************************
 * Exported Variables
 **************************************//**************************************//**************************************/
extern const Joystick_IO_Drv_t JoystickIO_Driver;

#endif /* INC_KEYPADPARTS_JOYSTICK_HARDWARE_H_ */
