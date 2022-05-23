/*
 * SerialLED_Hardware.h
 *
 *  Created on: May 22, 2022
 *      Author: evanl
 */

#ifndef INC_KEYPADPARTS_SERIALLED_HARDWARE_H_
#define INC_KEYPADPARTS_SERIALLED_HARDWARE_H_
#include <stdint.h>
#define NUMBER_OF_LEDS (4U)

typedef struct{
    void (*init)(void);
    void (*deinit)(void);
    void (*read)(void);
    void (*write)(uint16_t, uint8_t, uint8_t, uint8_t);
    void (*ioctl)(void);
}SerialLED_IO_Drv_t;

extern SerialLED_IO_Drv_t LED_Drv;

#endif /* INC_KEYPADPARTS_SERIALLED_HARDWARE_H_ */
