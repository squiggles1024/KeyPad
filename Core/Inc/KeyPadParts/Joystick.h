/*
 * Joystick.h
 *
 *  Created on: May 20, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPADPARTS_JOYSTICK_H_
#define INC_KEYPADPARTS_JOYSTICK_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "Joystick_Hardware.h"
#include "KeyFunctions.h"
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	JoystickChanged = 0,
	JoystickUnchanged,
	JoystickErr
}JoystickStatus_t;

typedef enum{
	JoystickAnalog = 0,
	Joystick4Way,
	Joystick8Way
}JoystickMode_t;

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef struct{
	KeyScanCode KeyFunction;
	ModifierKey ModKeyFunction;
    MouseClick  MouseFunction;
    MouseWheel  WheelFunction;
}JoystickDirectionFunction_t;

typedef struct{
	uint16_t DeadZone;
	JoystickMode_t Mode;
	JoystickDirectionFunction_t RightFunction;
	JoystickDirectionFunction_t UpRightFunction;
	JoystickDirectionFunction_t UpFunction;
	JoystickDirectionFunction_t UpLeftFunction;
	JoystickDirectionFunction_t LeftFunction;
	JoystickDirectionFunction_t DownLeftFunction;
	JoystickDirectionFunction_t DownFunction;
	JoystickDirectionFunction_t DownRightFunction;
}Joystick_Init_Struct_t;

typedef struct{
    int16_t X_PosRaw;
    int16_t Y_PosRaw;
    JoystickState_t Position;
    uint16_t DeadZone;
    JoystickMode_t Mode;
	JoystickDirectionFunction_t RightFunction;
	JoystickDirectionFunction_t UpRightFunction;
	JoystickDirectionFunction_t UpFunction;
	JoystickDirectionFunction_t UpLeftFunction;
	JoystickDirectionFunction_t LeftFunction;
	JoystickDirectionFunction_t DownLeftFunction;
	JoystickDirectionFunction_t DownFunction;
	JoystickDirectionFunction_t DownRightFunction;
    Joystick_IO_Drv_t IO_Driver;
}Joystick_Handle_t;

/**************************************//**************************************//**************************************
 * Public Function Declarations
 **************************************//**************************************//**************************************/
void JoystickInit(Joystick_Init_Struct_t Settings, Joystick_Handle_t *Joystick, Joystick_IO_Drv_t IO);
JoystickStatus_t JoystickRead(Joystick_Handle_t *Joystick);
void JoystickSetFunction(Joystick_Handle_t* Joystick, JoystickState_t Position, JoystickDirectionFunction_t NewFunction);
void JoystickSetMode(Joystick_Handle_t* Joystick, JoystickMode_t NewMode);


#endif /* INC_KEYPADPARTS_JOYSTICK_H_ */
