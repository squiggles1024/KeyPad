/*
 * Joystick.c
 *
 *  Created on: May 20, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "Joystick.h"

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes a joystick handle
 *@Params: Init struct with desired user settings, Joystick handle to initialize, Low level IO Driver
 *@Return: None
 *@Precondition: None
 *@Postcondition: Joystick handle and low level hardware will be initialized and ready to use.
 **************************************//**************************************/
void JoystickInit(Joystick_Init_Struct_t Settings, Joystick_Handle_t *Joystick, Joystick_IO_Drv_t IO){
	Joystick->IO_Driver.init = IO.init;
	Joystick->IO_Driver.deinit = IO.deinit;
	Joystick->IO_Driver.read = IO.read;
	Joystick->IO_Driver.write = IO.write;
	Joystick->IO_Driver.ioctl = IO.ioctl;
	Joystick->IO_Driver.init();

	Joystick->DeadZone          = Settings.DeadZone;
	Joystick->UpFunction        = Settings.UpFunction;
	Joystick->LeftFunction      = Settings.LeftFunction;
	Joystick->RightFunction     = Settings.RightFunction;
	Joystick->UpRightFunction   = Settings.UpRightFunction;
	Joystick->UpLeftFunction    = Settings.UpLeftFunction;
	Joystick->DownFunction      = Settings.DownFunction;
	Joystick->DownLeftFunction  = Settings.DownLeftFunction;
	Joystick->DownRightFunction = Settings.DownRightFunction;
	Joystick->Mode = Settings.Mode;
	Joystick->Position = JoystickNeutral;
	Joystick->X_PosRaw = 0;
	Joystick->Y_PosRaw = 0;
}

/**************************************//**************************************
 *@Brief: Updates Joystick Position and Raw X/Y Coordinate
 *@Params: Joystick Handle
 *@Return: JoystickChanged if previous position != new position. Uses XPosRaw/YPosRaw in analog mode
 *@Precondition: JoystickHandle must be initialized
 *@Postcondition: Joystick XPosRaw/YPosRaw/State will be updated.
 **************************************//**************************************/
JoystickStatus_t JoystickRead(Joystick_Handle_t *Joystick){
	JoystickState_t PreviousState = Joystick->Position;
	int16_t PreviousX = Joystick->X_PosRaw;
	int16_t PreviousY = Joystick->Y_PosRaw;
	Joystick->Position = Joystick->IO_Driver.read(Joystick->DeadZone, &Joystick->X_PosRaw, &Joystick->Y_PosRaw);

	if(Joystick->Mode == Joystick4Way || Joystick->Mode == Joystick8Way){
	    if(Joystick->Position != PreviousState){
		    return JoystickChanged;
	    } else {
		    return JoystickUnchanged;
	    }
	}

	if(Joystick->X_PosRaw != PreviousX || Joystick->Y_PosRaw != PreviousY){
		return JoystickChanged;
	} else {
		return JoystickUnchanged;
	}
}

/**************************************//**************************************
 *@Brief: Changes a direction function of a joystick handle
 *@Params: Joystick handle to modify, Position to assign new function to, and the desired new function.
 *@Return: None
 *@Precondition: None
 *@Postcondition: Joystick ___Position function will be updated.
 **************************************//**************************************/
void JoystickSetFunction(Joystick_Handle_t* Joystick, JoystickState_t Position, JoystickDirectionFunction_t NewFunction){

	switch(Position){
	case(Joystick_Right):
			Joystick->RightFunction = NewFunction;
			break;
	case(Joystick_UpRight):
		    Joystick->UpRightFunction = NewFunction;
			break;
	case(Joystick_Up):
		    Joystick->UpFunction = NewFunction;
			break;
	case(Joystick_UpLeft):
		    Joystick->UpLeftFunction = NewFunction;
			break;
	case(Joystick_Left):
		    Joystick->LeftFunction = NewFunction;
			break;
	case(Joystick_DownLeft):
		    Joystick->DownLeftFunction = NewFunction;
			break;
	case(Joystick_Down):
		    Joystick->DownFunction = NewFunction;
			break;
	case(Joystick_DownRight):
		    Joystick->DownRightFunction = NewFunction;
			break;
	default:
			break;
	}

}
