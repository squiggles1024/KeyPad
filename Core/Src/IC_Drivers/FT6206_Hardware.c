/*
 * FT6206_Hardware.c
 *
 *  Created on: May 26, 2022
 *      Author: evanl
 */
#include <FT6206_Hardware.h>
#include "i2c.h"
#include "gpio.h"
#include "dma.h"

static const uint8_t DevAddr = 0x70;

static void FT6206_IO_Init(void){
	I2C2_DMA_Init();
	I2C_GPIO_Init();
	I2C2_Init();
}

static void FT6206_IO_DeInit(void){
	HAL_NVIC_DisableIRQ(DMA1_Stream2_IRQn);
	HAL_NVIC_ClearPendingIRQ(DMA1_Stream2_IRQn);
}

static FT6206_Status_t FT6206_IO_Write(uint8_t Reg, uint8_t* pdata, uint8_t length){
	if(HAL_I2C_Mem_Write(&hi2c2, DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pdata, length, 100) != HAL_OK){
		return FT6206_Err;
	}
	return FT6206_Ok;
}

static FT6206_Status_t FT6206_IO_Read(uint8_t Reg, uint8_t* pdata, uint8_t length){
	if(HAL_I2C_Mem_Read_DMA(&hi2c2, DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pdata, length) != HAL_OK){
		return FT6206_Err;
	}
	return FT6206_Ok;
}

static uint8_t FT6206_IO_ioctl(FT6206_IO_Cmd_t Command){
	return FT6206_Ok;
}

FT6206_IO_Drv_t FT6202_Drv = {
		.init = FT6206_IO_Init,
		.deinit = FT6206_IO_DeInit,
		.write = FT6206_IO_Write,
		.read = FT6206_IO_Read,
        .ioctl = FT6206_IO_ioctl
};
