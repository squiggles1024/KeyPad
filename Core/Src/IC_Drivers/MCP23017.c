/*
 * MCP23017.c
 *
 *  Created on: May 17, 2022
 *      Author: evanl
 */

#ifndef MCP23017_C_
#define MCP23017_C_
#include "MCP23017.h"
#include "log.h"
/**************************************//**************************************//**************************************
 * Register Addresses
 **************************************//**************************************//**************************************/
const MCP23017_Reg MCP23017_IODIRA = 0x00;
const MCP23017_Reg MCP23017_IODIRB = 0x01;
const MCP23017_Reg MCP23017_IPOLA = 0x02;
const MCP23017_Reg MCP23017_IPOLB = 0x03;
const MCP23017_Reg MCP23017_GPINTENA = 0x04;
const MCP23017_Reg MCP23017_GPINTENB = 0x05;
const MCP23017_Reg MCP23017_DEFVALA = 0x06;
const MCP23017_Reg MCP23017_DEFVALB = 0x07;
const MCP23017_Reg MCP23017_INTCONA = 0x08;
const MCP23017_Reg MCP23017_INTCONB = 0x09;
const MCP23017_Reg MCP23017_IOCON = 0x0A;
//const MCP23017_Reg MCP23017_IOCON = 0x0B;
const MCP23017_Reg MCP23017_GPPUA = 0x0C;
const MCP23017_Reg MCP23017_GPPUB = 0x0D;
const MCP23017_Reg MCP23017_INTFA = 0x0E;
const MCP23017_Reg MCP23017_INTFB = 0x0F;
const MCP23017_Reg MCP23017_INTCAPA = 0x10;
const MCP23017_Reg MCP23017_INTCAPB = 0x11;
const MCP23017_Reg MCP23017_GPIOA = 0x12;
const MCP23017_Reg MCP23017_GPIOB = 0x13;
const MCP23017_Reg MCP23017_OLATA = 0x14;
const MCP23017_Reg MCP23017_OLATB = 0x15;

/**************************************//**************************************//**************************************
 * Pin Masks
 **************************************//**************************************//**************************************/
const MCP23017_Pin MCP23017_PinA0   = 0x0001;
const MCP23017_Pin MCP23017_PinA1   = 0x0002;
const MCP23017_Pin MCP23017_PinA2   = 0x0004;
const MCP23017_Pin MCP23017_PinA3   = 0x0008;
const MCP23017_Pin MCP23017_PinA4   = 0x0010;
const MCP23017_Pin MCP23017_PinA5   = 0x0020;
const MCP23017_Pin MCP23017_PinA6   = 0x0040;
const MCP23017_Pin MCP23017_PinA7   = 0x0080;
const MCP23017_Pin MCP23017_PinB0   = 0x0100;
const MCP23017_Pin MCP23017_PinB1   = 0x0200;
const MCP23017_Pin MCP23017_PinB2   = 0x0400;
const MCP23017_Pin MCP23017_PinB3   = 0x0800;
const MCP23017_Pin MCP23017_PinB4   = 0x1000;
const MCP23017_Pin MCP23017_PinB5   = 0x2000;
const MCP23017_Pin MCP23017_PinB6   = 0x4000;
const MCP23017_Pin MCP23017_PinB7   = 0x8000;
const MCP23017_Pin MCP23017_AllPins = 0xFFFF;
const MCP23017_Pin MCP23017_NoPins  = 0x0000;

/**************************************//**************************************//**************************************
 * Other Configuration Options
 **************************************//**************************************//**************************************/
const MCP23017_Config MCP23017_IntPinActiveHigh = 0x02;
const MCP23017_Config MCP23017_IntPinOpenDrain = 0x04;
const MCP23017_Config MCP23017_SlewRateDisabled = 0x10;
const MCP23017_Config MCP23017_SeqOpDisabled = 0x20;
const MCP23017_Config MCP23017_IntMirrorMode = 0x40;
const MCP23017_Config MCP23017_SeparateBanks = 0x80;

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/

/**************************************//**************************************
 *@Brief: Initializes MCP23017 Device Handle
 *@Params: Init Struct with desired settings, Device handle to initialize, a low level IO Driver struct
 *@Return: None
 *@Precondition: Init Struct should have desired settings
 *@Postcondition: Device struct will be intialized and ready to use
 **************************************//**************************************/
void MCP23017_Init(MCP23017_Init_Struct_t Settings, MCP23017_Handle_t *Dev, MCP23017_IO_Drv_t IO_Driver){
	Dev->IO_Driver.Init = IO_Driver.Init;
	Dev->IO_Driver.DeInit = IO_Driver.DeInit;
	Dev->IO_Driver.ReadReg = IO_Driver.ReadReg;
	Dev->IO_Driver.WriteReg = IO_Driver.WriteReg;
	Dev->IO_Driver.ioctl = IO_Driver.ioctl;
	Dev->IO_Driver.Init();

	if(Dev->IO_Driver.WriteReg(MCP23017_IOCON, (uint8_t*)&Settings.Config,1) != MCP23017_Ok){
		_log(log_mcp23017, "Initialization: IOCON Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_IODIRA, (uint8_t*)&Settings.Mode,2) != MCP23017_Ok){
		_log(log_mcp23017, "Initialization: IODIR Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_IPOLA, (uint8_t*)&Settings.Polarity,2) != MCP23017_Ok){
		_log(log_mcp23017, "Initialization: IPOL Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_GPINTENA, (uint8_t*)&Settings.IntEnable,2) != MCP23017_Ok){
		_log(log_mcp23017, "Initialization: INTENA Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_DEFVALA, (uint8_t*)&Settings.DefaultValue,2) != MCP23017_Ok){
		_log(log_mcp23017, "Initialization: DEFVAL Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_INTCONA, (uint8_t*)&Settings.IRQControl,2) != MCP23017_Ok){
		_log(log_mcp23017, "Initialization: INTCON Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_GPPUA, (uint8_t*)&Settings.PullUp,2) != MCP23017_Ok){
		_log(log_mcp23017, "Initialization: GPPU Write Failed");
	}

}

/**************************************//**************************************
 *@Brief: Resets MCP23017 Device to default settings and deinitializes it's Low Level IO Driver
 *@Params: MCP23017 Device handle to deinitialize
 *@Return: None
 *@Precondition: Device handle should be initialized
 *@Postcondition: Device handle will be deinitialized and device registers set to default settings
 **************************************//**************************************/
void MCP23017_DeInit(MCP23017_Handle_t *Dev){
	MCP23017_Reset(Dev);
	Dev->IO_Driver.Init = '\0';
	Dev->IO_Driver.DeInit = '\0';
	Dev->IO_Driver.ReadReg = '\0';
	Dev->IO_Driver.WriteReg = '\0';
	Dev->IO_Driver.ioctl = '\0';
}

/**************************************//**************************************
 *@Brief: Resets MCP23017 Device
 *@Params: MCP23017 Device Handle to reset
 *@Return: None
 *@Precondition: Device handle should be initialized
 *@Postcondition: Device registers will be set to default settings
 **************************************//**************************************/
void MCP23017_Reset(MCP23017_Handle_t *Dev){
	uint16_t Settings = 0;
	Dev->IO_Driver.DeInit(); //Turn off DMA IRQ and clear pending IRQ
	if(Dev->IO_Driver.WriteReg(MCP23017_IOCON, (uint8_t*)&Settings,1) != MCP23017_Ok){
		_log(log_mcp23017, "DeInitialization: IOCON Write Failed");
	}

	Settings = 0xFFFF;
	if(Dev->IO_Driver.WriteReg(MCP23017_IODIRA, (uint8_t*)&Settings,2) != MCP23017_Ok){
		_log(log_mcp23017, "DeInitialization: IODIR Write Failed");
	}

	Settings = 0x0000;
	if(Dev->IO_Driver.WriteReg(MCP23017_IPOLA, (uint8_t*)&Settings,2) != MCP23017_Ok){
		_log(log_mcp23017, "DeInitialization: IPOL Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_GPINTENA, (uint8_t*)&Settings,2) != MCP23017_Ok){
		_log(log_mcp23017, "DeInitialization: INTENA Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_DEFVALA, (uint8_t*)&Settings,2) != MCP23017_Ok){
		_log(log_mcp23017, "DeInitialization: DEFVAL Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_INTCONA, (uint8_t*)&Settings,2) != MCP23017_Ok){
		_log(log_mcp23017, "DeInitialization: INTCON Write Failed");
	}

	if(Dev->IO_Driver.WriteReg(MCP23017_GPPUA, (uint8_t*)&Settings,2) != MCP23017_Ok){
		_log(log_mcp23017, "DeInitialization: GPPU Write Failed");
	}
}

/**************************************//**************************************
 *@Brief: Reads a MCP23017 Device Register
 *@Params: MCP23017 Device Handle, Reg to read, buffer to store read data, data length
 *@Return: Err if read fails, Ok otherwise
 *@Precondition: Device handle must be initialized
 *@Postcondition: pdata will contain value of read register
 **************************************//**************************************/
MCP23017_Status_t MCP23017_ReadReg(MCP23017_Handle_t *Dev, MCP23017_Reg RegAddr, uint8_t *pdata, uint8_t length){
	if(Dev->IO_Driver.ReadReg(RegAddr, pdata, length) != MCP23017_Ok){
		_log(log_mcp23017, "Read Reg: Addr %x Failed",RegAddr);
		return MCP23017_Err;
	}
	return MCP23017_Ok;
}

/**************************************//**************************************
 *@Brief: Write to a MCP23017 Device Register
 *@Params: MCP23017 Device Handle, Reg to write, buffer with data to write, data length
 *@Return: Err if write fails, Ok otherwise
 *@Precondition: Device handle must be initialized
 *@Postcondition: device register will take on value stored in pdata
 **************************************//**************************************/
MCP23017_Status_t MCP23017_WriteReg(MCP23017_Handle_t *Dev, MCP23017_Reg RegAddr, uint8_t *pdata, uint8_t length){
	if(Dev->IO_Driver.WriteReg(RegAddr, pdata, length) != MCP23017_Ok){
		_log(log_mcp23017, "Write Reg: Addr %x Failed", RegAddr);
		return MCP23017_Err;
	}
	return MCP23017_Ok;
}

/**************************************//**************************************
 *@Brief: Write to pins of MCP23017 device
 *@Params: MCP23017 Device Handle, Pins to write 1 to (Bitwise OR'd together)
 *@Return: Err if write fails, Ok otherwise
 *@Precondition: Device handle must be initialized
 *@Postcondition: Device pins in the Pins Param will be set, others will be cleared
 **************************************//**************************************/
MCP23017_Status_t MCP23017_WritePins(MCP23017_Handle_t *Dev, MCP23017_Pin Pins){
	if(Dev->IO_Driver.WriteReg(MCP23017_OLATA, (uint8_t*)&Pins, 2) != MCP23017_Ok){
		_log(log_mcp23017, "Write Pins Failed");
		return MCP23017_Err;
	}
	return MCP23017_Ok;
}

/**************************************//**************************************
 *@Brief: Read pins of MCP23017 device
 *@Params: MCP23017 Device Handle
 *@Return: Err if read fails, Ok otherwise
 *@Precondition: Device handle must be initialized
 *@Postcondition: Device Handle PinStates will contain new states of pins
 **************************************//**************************************/
MCP23017_Status_t MCP23017_ReadPins(MCP23017_Handle_t *Dev){
	if(Dev->IO_Driver.ReadReg(MCP23017_GPIOA, (uint8_t*)&Dev->PinStates, 2) != MCP23017_Ok){
		_log(log_mcp23017, "Read Pins Failed");
		return MCP23017_Err;
	}
	return MCP23017_Ok;
}

#endif /* SRC_IC_DRIVERS_MCP23017_C_ */
