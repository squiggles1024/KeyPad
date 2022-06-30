/*
 * SerialLED.c
 *
 *  Created on: May 22, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "SerialLED.h"

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes Serial LED
 *@Params: Init Struct settings, LED Handle Pointer, Low level IO Driver
 *@Return: None
 *@Precondition: None
 *@Postcondition: Low level hardware will be initialized (Timer, DMA)
 **************************************//**************************************/
void SerialLEDInit(SerialLED_InitStruct_t Settings, SerialLED_Handle_t *LED, SerialLED_IO_Drv_t IO){
    LED->IO_Driver = IO;
    LED->Address = Settings.address;
    LED->red = Settings.red;
    LED->green = Settings.green;
    LED->blue = Settings.blue;
    LED->IO_Driver.init();
    LED->IO_Driver.write(LED->Address, LED->red, LED->green, LED->blue);
}

/**************************************//**************************************
 *@Brief: Deinitializes Serial LED hardware
 *@Params: LED Handle pointer
 *@Return: None
 *@Precondition: LED Handle should be initialized
 *@Postcondition: Stops DMA engine and timer. De initialies LED IO Driver
 **************************************//**************************************/
void SerialLEDDeInit(SerialLED_Handle_t *LED){
	LED->IO_Driver.deinit();
    LED->IO_Driver.init = '\0';
    LED->IO_Driver.deinit = '\0';
    LED->IO_Driver.read = '\0';
    LED->IO_Driver.write = '\0';
    LED->IO_Driver.ioctl = '\0';
}

/**************************************//**************************************
 *@Brief: Sets color of LED
 *@Params: LED Handlep pointer, red value, green value, blue value
 *@Return: None
 *@Precondition: LED Should be initialized
 *@Postcondition: LED DMA Buffer will be updated with RGB values
 **************************************//**************************************/
void SerialLEDSetColor(SerialLED_Handle_t *LED, uint8_t red, uint8_t green, uint8_t blue){
	LED->IO_Driver.write(LED->Address, red, green, blue);
}
