#include <ILI9341_Hardware.h>
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "gpio.h"

static void ILI9341_CSState(uint8_t state);
static void ILI9341_DCRSState(uint8_t state);

static void ILI9341_IO_Init(void){
  ILI9341_GPIO_Init();
  ILI9341_SPI_Init();
}

static void ILI9341_IO_DeInit(void){
	ILI9341_GPIO_DeInit();
}

static ILI9341_Status_t ILI9341_IO_ioctl(ILI9341_Cmd_t Command){
    switch(Command){
    case(ILI9341_Delay150):
    		HAL_Delay(150);
            return ILI9341_Ok;
    case(ILI9341_Delay1000):
    		HAL_Delay(1000);
            return ILI9341_Ok;
    default:
    	return ILI9341_Ok;
    }
}

static ILI9341_Status_t ILI9341_IO_WriteReg(uint8_t reg, uint8_t* pdata, uint32_t length){
	ILI9341_CSState(GPIO_PIN_RESET);
	if(reg != 0xFF){
		ILI9341_DCRSState(GPIO_PIN_RESET);
		if(HAL_SPI_Transmit(&hspi1, &reg, 1, 10) != HAL_OK){
			return ILI9341_Err;
		}
	}

	ILI9341_DCRSState(GPIO_PIN_SET);
	if(length != 0 && reg != 0xFF){
		if(HAL_SPI_Transmit(&hspi1, pdata, length, 1000) != HAL_OK){
			return ILI9341_Err;
		}
	}else if(length != 0 && reg == 0xFF){
        for(uint32_t i = 0; i < length; i = i + 3){
    		if(HAL_SPI_Transmit(&hspi1, pdata, 1, 10) != HAL_OK){
    			return ILI9341_Err;
    		}

    		if(HAL_SPI_Transmit(&hspi1, pdata + 1, 1, 10) != HAL_OK){
    			return ILI9341_Err;
    		}

    		if(HAL_SPI_Transmit(&hspi1, pdata + 2, 1, 10) != HAL_OK){
    			return ILI9341_Err;
    		}
    		if(i == length - 10000){
    			uint8_t j =0;
    			j++;
    		}
        }
	}else {
		ILI9341_CSState(GPIO_PIN_SET);
	}
	return ILI9341_Ok;
}

static ILI9341_Status_t ILI9341_IO_ReadReg(uint8_t reg, uint8_t* pdata, uint32_t length){
	ILI9341_CSState(GPIO_PIN_RESET);
	ILI9341_DCRSState(GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(&hspi1, &reg, 1, 10) != HAL_OK){
        return ILI9341_Err;
	}
	ILI9341_DCRSState(GPIO_PIN_SET);

	if(length != 0){
		if(HAL_SPI_Receive(&hspi1, pdata, length, 10) != HAL_OK){
			return ILI9341_Err;
		}
	}
	ILI9341_CSState(GPIO_PIN_SET);
	return ILI9341_Ok;
}

static void ILI9341_CSState(uint8_t state){
  if(state){
    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
  }
}

static void ILI9341_DCRSState(uint8_t state){
  if(state){
    HAL_GPIO_WritePin(DCRS_GPIO_Port, DCRS_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(DCRS_GPIO_Port, DCRS_Pin, GPIO_PIN_RESET);
  }
}

ILI9341_IO_Drv_t ILI931_IO = {
		.init = ILI9341_IO_Init,
		.deinit = ILI9341_IO_DeInit,
		.write = ILI9341_IO_WriteReg,
		.read = ILI9341_IO_ReadReg,
		.ioctl = ILI9341_IO_ioctl
};
