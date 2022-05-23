/*
 * MCP23017_Hardware.h
 *
 *  Created on: May 17, 2022
 *      Author: evanl
 */

#ifndef INC_IC_DRIVERS_MCP23017_HARDWARE_H_
#define INC_IC_DRIVERS_MCP23017_HARDWARE_H_
#include <stdint.h>

typedef uint8_t MCP23017_IO_Cmd_t;
typedef enum{
	MCP23017_Ok,
	MCP23017_Err
}MCP23017_Status_t;

typedef struct{
	void (*Init)();                                            //Performs Low level IO initialization (e.g. GPIO, I2C or SPI)
	void (*DeInit)();                                          //De initializes Low Level IO drivers
	MCP23017_Status_t (*WriteReg)(uint8_t, uint8_t*, uint8_t); //Params: Reg Addr, Data, Length
	MCP23017_Status_t (*ReadReg)(uint8_t, uint8_t*, uint8_t);  //Params: Reg Addr, Data Buffer, Length
	uint8_t (*ioctl)(MCP23017_IO_Cmd_t);                       //Other desired functions (e.g. read INT pin, disable IRQ, etc.)
}MCP23017_IO_Drv_t;

extern const MCP23017_IO_Drv_t MCP23017_IO1_Drv;
extern const MCP23017_IO_Drv_t MCP23017_IO2_Drv;
extern const MCP23017_IO_Drv_t MCP23017_IO3_Drv;
extern const MCP23017_IO_Drv_t MCP23017_IO4_Drv;


#endif /* INC_IC_DRIVERS_MCP23017_HARDWARE_H_ */
