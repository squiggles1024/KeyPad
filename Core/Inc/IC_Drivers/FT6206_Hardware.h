/*
 * FT6206__Hardware.h
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */

#ifndef INC_IC_DRIVERS_FT6206_HARDWARE_H_
#define INC_IC_DRIVERS_FT6206_HARDWARE_H_
#include <stdint.h>

typedef uint8_t FT6206_IO_Cmd_t;
typedef enum{
	FT6206_Ok,
	FT6206_Err
}FT6206_Status_t;

typedef struct{
    void (*init)(void);
    void (*deinit)(void);
    FT6206_Status_t (*write)(uint8_t,uint8_t*,uint8_t);
    FT6206_Status_t (*read)(uint8_t,uint8_t*,uint8_t);
    uint8_t (*ioctl)(FT6206_IO_Cmd_t);
}FT6206_IO_Drv_t;

extern FT6206_IO_Drv_t FT6202_Drv;

#endif /* INC_KEYPADPARTS_FT6206_HARDWARE_H_ */
