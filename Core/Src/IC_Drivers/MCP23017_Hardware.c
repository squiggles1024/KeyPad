/*
 * MCP23017_Hardware.c
 *
 *  Created on: May 17, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "MCP23017_Hardware.h"
#include "i2c.h"
#include "gpio.h"
#include "dma.h"
#include "log.h"
/**************************************//**************************************//**************************************
 * Defines / Constants
 **************************************//**************************************//**************************************/
static const uint8_t MCP23017_Address1 = 0x40;
static const uint8_t MCP23017_Address2 = 0x42;
static const uint8_t MCP23017_Address3 = 0x44;
static const uint8_t MCP23017_Address4 = 0x46;
/**************************************//**************************************//**************************************
 * Private Function Definitions
 **************************************//**************************************//**************************************/

/**************************************//**************************************
 *@Brief: Initializes GPIO Clk and I2C Peripheral
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: GPIO B Clk will be enabled and I2C1 Peripheral will be initialized
 **************************************//**************************************/
static void MCP23017_IO_Init(){
	I2C_DMA_Init();
	I2C_GPIO_Init();
	I2C1_Init();
}

/**************************************//**************************************
 *@Brief: Not yet implemented. Do not de-initialize I2C Peripheral in the event that other devices share the same bus.
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: None
 **************************************//**************************************/
static void MCP23017_IO_DeInit(){
	HAL_NVIC_DisableIRQ(DMA1_Stream0_IRQn);
	HAL_NVIC_ClearPendingIRQ(DMA1_Stream0_IRQn);
}

/**************************************//**************************************
 *@Brief: Writes to a MCP23017 Device Register
 *@Params: MCP23017 Device Address, Register to write to, data to write, data length in bytes
 *@Return: Error if the write fails, otherwise Ok
 *@Precondition: I2C Bus should be initialized
 *@Postcondition: Device register will be written to
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO_WriteReg(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	if(HAL_I2C_Mem_Write(&hi2c1, DevAddr, RegAddr, I2C_MEMADD_SIZE_8BIT, Data, Length, 50) != HAL_OK){
		_log(log_i2c,"Write to MCP23017 Reg address %x failed.", RegAddr);
		return MCP23017_Err;
	}
	return MCP23017_Ok;
}

/**************************************//**************************************
 *@Brief: Reads a MCP23017 Device Register
 *@Params: MCP23017 Device Address, Register to read to, data buffer to read into, data length in bytes,
 *@Return: Error if the read fails, otherwise Ok
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Data buffer will have the read data
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO_ReadReg(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	//HAL_I2C_Mem_Read_DMA(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size)
	//if(HAL_I2C_Mem_Read(&hi2c1, DevAddr, RegAddr, I2C_MEMADD_SIZE_8BIT, Data, Length, 50) != HAL_OK){
	if(HAL_I2C_Mem_Read_DMA(&hi2c1, DevAddr, RegAddr, I2C_MEMADD_SIZE_8BIT, Data, Length) != HAL_OK){
		_log(log_i2c,"Read from MCP23017 Reg address %x failed.", RegAddr);
		return MCP23017_Err;
	}
	return MCP23017_Ok;
}

/**************************************//**************************************
 *@Brief: Not Yet Implemented. Function is reserved for other IO control functionality (e.g. IRQ pin reading)
 *@Params: Command
 *@Return: None
 *@Precondition: None
 *@Postcondition: None
 **************************************//**************************************/
static uint8_t MCP23017_IO_ioctl(MCP23017_IO_Cmd_t command){
	return MCP23017_Ok;
}

/**************************************//**************************************
 *@Brief: Writes to MCP23017 Device with Address1
 *@Params: Register to write to, data to write, length of data in bytes
 *@Return: Err if write fails, Ok otherwise
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Device (w/ Address1) register will be modified
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO1_WriteReg(uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	static const uint8_t address = MCP23017_Address1;
    return MCP23017_IO_WriteReg(address, RegAddr, Data, Length);
}

/**************************************//**************************************
 *@Brief: Reads a MCP23017 Device Register with Address1
 *@Params: Register to read from, data buffer to read into, length of data in bytes
 *@Return: Err if read fails, Ok otherwise
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Data buffer will contain data from device (w/ Address1) register
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO1_ReadReg(uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	static const uint8_t address = MCP23017_Address1;
	return MCP23017_IO_ReadReg(address, RegAddr, Data, Length);
}

/**************************************//**************************************
 *@Brief: Writes to MCP23017 Device with Address2
 *@Params: Register to write to, data to write, length of data in bytes
 *@Return: Err if write fails, Ok otherwise
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Device (w/ Address2) register will be modified
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO2_WriteReg(uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	static const uint8_t address = MCP23017_Address2;
    return MCP23017_IO_WriteReg(address, RegAddr, Data, Length);
}

/**************************************//**************************************
 *@Brief: Reads a MCP23017 Device Register with Address2
 *@Params: Register to read from, data buffer to read into, length of data in bytes
 *@Return: Err if read fails, Ok otherwise
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Data buffer will contain data from device (w/ Address2) register
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO2_ReadReg(uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	static const uint8_t address = MCP23017_Address2;
	return MCP23017_IO_ReadReg(address, RegAddr, Data, Length);
}

/**************************************//**************************************
 *@Brief: Writes to MCP23017 Device with Address3
 *@Params: Register to write to, data to write, length of data in bytes
 *@Return: Err if write fails, Ok otherwise
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Device (w/ Address3) register will be modified
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO3_WriteReg(uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	static const uint8_t address = MCP23017_Address3;
    return MCP23017_IO_WriteReg(address, RegAddr, Data, Length);
}

/**************************************//**************************************
 *@Brief: Reads a MCP23017 Device Register with Address3
 *@Params: Register to read from, data buffer to read into, length of data in bytes
 *@Return: Err if read fails, Ok otherwise
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Data buffer will contain data from device (w/ Address3) register
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO3_ReadReg(uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	static const uint8_t address = MCP23017_Address3;
	return MCP23017_IO_ReadReg(address, RegAddr, Data, Length);
}

/**************************************//**************************************
 *@Brief: Writes to MCP23017 Device with Address4
 *@Params: Register to write to, data to write, length of data in bytes
 *@Return: Err if write fails, Ok otherwise
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Device (w/ Address4) register will be modified
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO4_WriteReg(uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	static const uint8_t address = MCP23017_Address4;
    return MCP23017_IO_WriteReg(address, RegAddr, Data, Length);
}

/**************************************//**************************************
 *@Brief: Reads a MCP23017 Device Register with Address4
 *@Params: Register to read from, data buffer to read into, length of data in bytes
 *@Return: Err if read fails, Ok otherwise
 *@Precondition: I2C Bus must be initialized
 *@Postcondition: Data buffer will contain data from device (w/ Address4) register
 **************************************//**************************************/
static MCP23017_Status_t MCP23017_IO4_ReadReg(uint8_t RegAddr, uint8_t *Data, uint8_t Length){
	static const uint8_t address = MCP23017_Address4;
	return MCP23017_IO_ReadReg(address, RegAddr, Data, Length);
}


/**************************************//**************************************//**************************************
 * Public Variable Definitions
 **************************************//**************************************//**************************************/
const MCP23017_IO_Drv_t MCP23017_IO1_Drv = {
		.Init = MCP23017_IO_Init,
		.DeInit = MCP23017_IO_DeInit,
		.WriteReg = MCP23017_IO2_WriteReg,
		.ReadReg = MCP23017_IO2_ReadReg,
		.ioctl = MCP23017_IO_ioctl
};

const MCP23017_IO_Drv_t MCP23017_IO2_Drv = {
		.Init = MCP23017_IO_Init,
		.DeInit = MCP23017_IO_DeInit,
		.WriteReg = MCP23017_IO2_WriteReg,
		.ReadReg = MCP23017_IO2_ReadReg,
		.ioctl = MCP23017_IO_ioctl
};

const MCP23017_IO_Drv_t MCP23017_IO3_Drv = {
		.Init = MCP23017_IO_Init,
		.DeInit = MCP23017_IO_DeInit,
		.WriteReg = MCP23017_IO2_WriteReg,
		.ReadReg = MCP23017_IO2_ReadReg,
		.ioctl = MCP23017_IO_ioctl
};

const MCP23017_IO_Drv_t MCP23017_IO4_Drv = {
		.Init = MCP23017_IO_Init,
		.DeInit = MCP23017_IO_DeInit,
		.WriteReg = MCP23017_IO2_WriteReg,
		.ReadReg = MCP23017_IO2_ReadReg,
		.ioctl = MCP23017_IO_ioctl
};
