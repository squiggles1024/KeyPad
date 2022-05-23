/*
 * SerialLED.c
 *
 *  Created on: May 22, 2022
 *      Author: evanl
 */
#include "SerialLED.h"

void SerialLEDInit(SerialLED_InitStruct_t Settings, SerialLED_Handle_t *LED, SerialLED_IO_Drv_t IO){
    LED->IO_Driver = IO;
    LED->Address = Settings.address;
    LED->red = Settings.red;
    LED->green = Settings.green;
    LED->blue = Settings.blue;
    LED->IO_Driver.init();
    LED->IO_Driver.write(LED->Address, LED->red, LED->green, LED->blue);
}

void SerialLEDDeInit(SerialLED_Handle_t *LED){
	LED->IO_Driver.deinit();
    LED->IO_Driver.init = '\0';
    LED->IO_Driver.deinit = '\0';
    LED->IO_Driver.read = '\0';
    LED->IO_Driver.write = '\0';
    LED->IO_Driver.ioctl = '\0';
}

void SerialLEDSetColor(SerialLED_Handle_t *LED, uint8_t red, uint8_t green, uint8_t blue){
	LED->IO_Driver.write(LED->Address, red, green, blue);
}
