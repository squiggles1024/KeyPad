/*
 * TouchButton_Hardware.h
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPADPARTS_TOUCHBUTTON_HARDWARE_H_
#define INC_KEYPADPARTS_TOUCHBUTTON_HARDWARE_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <stdint.h>
#include "FT6206.h"

/**************************************//**************************************//**************************************
 * Defines
 **************************************//**************************************//**************************************/
#define NUMBER_OF_TOUCH_BUTTONS 12U

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	TouchButtonPressed,
	TouchButtonUnpressed
}TouchButtonState_t;

typedef struct{
	uint16_t X_Position;
	uint16_t Y_Position;
}TouchButtonCoordinate_t;

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef struct{
    void (*init)(void);
    void (*deinit)(void);
    TouchButtonState_t (*read)(TouchButtonCoordinate_t,TouchButtonCoordinate_t);
    void (*write)(void);
    uint8_t (*ioctl)(uint8_t);
}TouchButton_IO_Drv_t;

/**************************************//**************************************//**************************************
 * Exported Variables
 **************************************//**************************************//**************************************/
extern const TouchButton_IO_Drv_t TouchButton_IO_Driver;
extern FT6206_Handle_t TouchScreen;

/**************************************//**************************************//**************************************
 * Public Functions
 **************************************//**************************************//**************************************/
void TouchScreenIRQCallback();


#endif /* INC_KEYPADPARTS_TOUCHBUTTON_HARDWARE_H_ */
