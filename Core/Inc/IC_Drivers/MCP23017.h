/*
 * MCP23017.h
 *
 *  Created on: May 17, 2022
 *      Author: evanl
 */

#ifndef MCP23017_H_
#define MCP23017_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <stdint.h>
#include "MCP23017_Hardware.h"
/**************************************//**************************************//**************************************
 * Typedefs / Enumerations
 **************************************//**************************************//**************************************/
typedef uint8_t MCP23017_Reg;
typedef uint16_t MCP23017_Pin;

typedef uint16_t MCP23017_PinMode;            //1 = Input, 0 = Output
typedef uint16_t MCP23017_PinPolarity;        //1 = Logic level on pin is opposite of what is read on bit, 0 = Logic level on pin is logic read on bit,
typedef uint16_t MCP23017_PinIntEnable;       //1 = Interrupt-on-change enabled on pin, 0 = Interrupt-on-change disabled on pin
typedef uint16_t MCP23017_PinDefaultValue;    //Configured logic level that triggers and interrupt (see below register)
typedef uint16_t MCP23017_PinIRQControl;      //1 = Interrupt triggered by comparison to DEFVAL, 0 = Interrupt triggered by comparison to previous state (any change)
typedef uint16_t MCP23017_PinPullUp;          //1 = Pull-up enabled
typedef uint8_t MCP23017_Config;              //See "Other Configuration Options" Below

/**************************************//**************************************//**************************************
 * Defines
 **************************************//**************************************//**************************************/
#define PINS_PER_EXPANDER (16U)

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef struct{
	MCP23017_PinMode Mode;
	MCP23017_PinPolarity Polarity;
	MCP23017_PinIntEnable IntEnable;
	MCP23017_PinDefaultValue DefaultValue;
	MCP23017_PinIRQControl IRQControl;
	MCP23017_PinPullUp PullUp;
	MCP23017_Config Config;
}MCP23017_Init_Struct_t;

typedef struct{
	volatile MCP23017_Pin PinStates;
	MCP23017_IO_Drv_t IO_Driver;
}MCP23017_Handle_t;

/**************************************//**************************************//**************************************
 * Register Addresses
 **************************************//**************************************//**************************************/
extern const MCP23017_Reg MCP23017_IODIRA;
extern const MCP23017_Reg MCP23017_IODIRB;
extern const MCP23017_Reg MCP23017_IPOLA;
extern const MCP23017_Reg MCP23017_IPOLB;
extern const MCP23017_Reg MCP23017_GPINTENA;
extern const MCP23017_Reg MCP23017_GPINTENB;
extern const MCP23017_Reg MCP23017_DEFVALA;
extern const MCP23017_Reg MCP23017_DEFVALB;
extern const MCP23017_Reg MCP23017_INTCONA;
extern const MCP23017_Reg MCP23017_INTCONB;
extern const MCP23017_Reg MCP23017_IOCON;
//extern const MCP23017_Reg MCP23017_IOCON = 0x0B;
extern const MCP23017_Reg MCP23017_GPPUA;
extern const MCP23017_Reg MCP23017_GPPUB;
extern const MCP23017_Reg MCP23017_INTFA;
extern const MCP23017_Reg MCP23017_INTFB;
extern const MCP23017_Reg MCP23017_INTCAPA;
extern const MCP23017_Reg MCP23017_INTCAPB;
extern const MCP23017_Reg MCP23017_GPIOA;
extern const MCP23017_Reg MCP23017_GPIOB;
extern const MCP23017_Reg MCP23017_OLATA;
extern const MCP23017_Reg MCP23017_OLATB;

/**************************************//**************************************//**************************************
 * Public Constants
 **************************************//**************************************//**************************************/
extern const MCP23017_Pin MCP23017_PinA0;
extern const MCP23017_Pin MCP23017_PinA1;
extern const MCP23017_Pin MCP23017_PinA2;
extern const MCP23017_Pin MCP23017_PinA3;
extern const MCP23017_Pin MCP23017_PinA4;
extern const MCP23017_Pin MCP23017_PinA5;
extern const MCP23017_Pin MCP23017_PinA6;
extern const MCP23017_Pin MCP23017_PinA7;
extern const MCP23017_Pin MCP23017_PinB0;
extern const MCP23017_Pin MCP23017_PinB1;
extern const MCP23017_Pin MCP23017_PinB2;
extern const MCP23017_Pin MCP23017_PinB3;
extern const MCP23017_Pin MCP23017_PinB4;
extern const MCP23017_Pin MCP23017_PinB5;
extern const MCP23017_Pin MCP23017_PinB6;
extern const MCP23017_Pin MCP23017_PinB7;
extern const MCP23017_Pin MCP23017_AllPins;
extern const MCP23017_Pin MCP23017_NoPins;

//Other Configuration Options
extern const MCP23017_Config MCP23017_IntPinActiveHigh;
extern const MCP23017_Config MCP23017_IntPinOpenDrain;
extern const MCP23017_Config MCP23017_SlewRateDisabled;
extern const MCP23017_Config MCP23017_SeqOpDisabled;
extern const MCP23017_Config MCP23017_IntMirrorMode;
extern const MCP23017_Config MCP23017_SeparateBanks; //Do not recommend changing. This will change the above register addresses.

/**************************************//**************************************//**************************************
 * Public Function Prototypes
 **************************************//**************************************//**************************************/
void MCP23017_Init(MCP23017_Init_Struct_t Settings, MCP23017_Handle_t *Dev, MCP23017_IO_Drv_t IO_Driver);
void MCP23017_DeInit(MCP23017_Handle_t *Dev);
void MCP23017_Reset(MCP23017_Handle_t *Dev);
MCP23017_Status_t MCP23017_ReadReg(MCP23017_Handle_t *Dev, MCP23017_Reg RegAddr, uint8_t *pdata, uint8_t length);
MCP23017_Status_t MCP23017_WriteReg(MCP23017_Handle_t *Dev, MCP23017_Reg RegAddr, uint8_t *pdata, uint8_t length);
MCP23017_Status_t MCP23017_WritePins(MCP23017_Handle_t *Dev, MCP23017_Pin Pins);
MCP23017_Status_t MCP23017_ReadPins(MCP23017_Handle_t *Dev);


#endif /* INC_IC_DRIVERS_MCP23017_H_ */
