/*
 * SerialLED.h
 *
 *  Created on: May 22, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPADPARTS_SERIALLED_H_
#define INC_KEYPADPARTS_SERIALLED_H_
#include <stdint.h>
#include "SerialLED_Hardware.h"

typedef struct{
	uint16_t address;
	uint8_t green;
	uint8_t red;
	uint8_t blue;
}SerialLED_InitStruct_t;

typedef struct{
	uint16_t Address;
	uint8_t green;
	uint8_t red;
	uint8_t blue;
	SerialLED_IO_Drv_t IO_Driver;
}SerialLED_Handle_t;

void SerialLEDInit(SerialLED_InitStruct_t Settings, SerialLED_Handle_t *LED, SerialLED_IO_Drv_t IO);
void SerialLEDDeInit(SerialLED_Handle_t *LED);
void SerialLEDSetColor(SerialLED_Handle_t *LED, uint8_t red, uint8_t green, uint8_t blue);


#endif /* INC_KEYPADPARTS_SERIALLED_H_ */
