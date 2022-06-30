/*
 * FT6206_Hardware.c
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <FT6206_Hardware.h>
#include "i2c.h"
#include "gpio.h"
#include "dma.h"

/**************************************//**************************************//**************************************
 * Private Constants
 **************************************//**************************************//**************************************/
static const uint8_t DevAddr = 0x70;

/**************************************//**************************************//**************************************
 * Private Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes FT6206 Low Level hardware
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: I2C2, DMA, and GPIO Peripherals will be initialized
 **************************************//**************************************/
static void FT6206_IO_Init(void){
	I2C2_DMA_Init();
	I2C_GPIO_Init();
	I2C2_Init();
}

/**************************************//**************************************
 *@Brief: Disables FT6206 IRQs and clears pending IRQs. Low level IO not deinitialized in case other hardware is using it.
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: DMA1 Stream2 IRQ will be disabled
 **************************************//**************************************/
static void FT6206_IO_DeInit(void){
	HAL_NVIC_DisableIRQ(DMA1_Stream2_IRQn);
	HAL_NVIC_ClearPendingIRQ(DMA1_Stream2_IRQn);
}

/**************************************//**************************************
 *@Brief: Writes to a FT6206 Register
 *@Params: Desired register to write, data to write, quantity of bytes to write
 *@Return: OK on success, Err on failure
 *@Precondition: FT6206 should be initialized
 *@Postcondition: FT6206 device register will be written to.
 **************************************//**************************************/
static FT6206_Status_t FT6206_IO_Write(uint8_t Reg, uint8_t* pdata, uint8_t length){
	if(HAL_I2C_Mem_Write(&hi2c2, DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pdata, length, 100) != HAL_OK){
		return FT6206_Err;
	}
	return FT6206_Ok;
}

/**************************************//**************************************
 *@Brief: Reads a FT6206 Register
 *@Params: register to read, data buffer, number of bytes to read
 *@Return: OK on success, Err on failure
 *@Precondition: FT6206 should be initialized. pdata must be able to fit length bytes
 *@Postcondition: FT6202 pdata will contain read bytes
 **************************************//**************************************/
static FT6206_Status_t FT6206_IO_Read(uint8_t Reg, uint8_t* pdata, uint8_t length){
	if(HAL_I2C_Mem_Read_DMA(&hi2c2, DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pdata, length) != HAL_OK){
		return FT6206_Err;
	}
	return FT6206_Ok;
}

/**************************************//**************************************
 *@Brief: Returns FT6206 OK. Modify to add hardware specific functionality
 *@Params: Desired command
 *@Return: FT6206_Ok
 *@Precondition: None (currently)
 *@Postcondition: None (currently)
 **************************************//**************************************/
static uint8_t FT6206_IO_ioctl(FT6206_IO_Cmd_t Command){
	return FT6206_Ok;
}

/**************************************//**************************************//**************************************
 * Public Variable Definitions
 **************************************//**************************************//**************************************/
FT6206_IO_Drv_t FT6202_Drv = {
		.init = FT6206_IO_Init,
		.deinit = FT6206_IO_DeInit,
		.write = FT6206_IO_Write,
		.read = FT6206_IO_Read,
        .ioctl = FT6206_IO_ioctl
};
