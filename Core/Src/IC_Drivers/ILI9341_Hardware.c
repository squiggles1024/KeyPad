/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <ILI9341_Hardware.h>
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "gpio.h"

/**************************************//**************************************//**************************************
 * Private Function Declarations
 **************************************//**************************************//**************************************/
static void ILI9341_CSState(uint8_t state);
static void ILI9341_DCRSState(uint8_t state);

/**************************************//**************************************//**************************************
 * Private Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes Low level hardware for ILI9431
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: GPIO and SPI Peripherals will be initialized
 **************************************//**************************************/
static void ILI9341_IO_Init(void){
  ILI9341_GPIO_Init();
  ILI9341_SPI_Init();
}

/**************************************//**************************************
 *@Brief: Deinitializes ILI9431 GPIO Pins
 *@Params: None
 *@Return: None
 *@Precondition: ILI9341 hardware should be initialized.
 *@Postcondition: ILI9431 GPIO Pins will be initialized (DCRS, CSN)
 **************************************//**************************************/
static void ILI9341_IO_DeInit(void){
	ILI9341_GPIO_DeInit();
}

/**************************************//**************************************
 *@Brief: Performs "Other" ILI9431 hardware commands
 *@Params: Command to perform
 *@Return: ILI9431 Ok
 *@Precondition: ILI9341 hardware should be initialized.
 *@Postcondition: None
 **************************************//**************************************/
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

/**************************************//**************************************
 *@Brief: Write to an ILI9431 Register
 *@Params: register to write, data buffer, qty of bytes to write
 *@Return: Err if data is not written, Ok if data is written
 *@Precondition: ILI9341 hardware should be initialized.
 *@Postcondition: ILI9431 register will contain written data
 **************************************//**************************************/
static ILI9341_Status_t ILI9341_IO_WriteReg(uint8_t reg, uint8_t* pdata, uint32_t length){
	ILI9341_CSState(GPIO_PIN_RESET);
	if(reg != 0xFF){
		ILI9341_DCRSState(GPIO_PIN_RESET);
		if(HAL_SPI_Transmit(&hspi1, &reg, 1, 1000) != HAL_OK){
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
    		if(HAL_SPI_Transmit(&hspi1, pdata, 1, 1000) != HAL_OK){
    			return ILI9341_Err;
    		}

    		if(HAL_SPI_Transmit(&hspi1, pdata + 1, 1, 1000) != HAL_OK){
    			return ILI9341_Err;
    		}

    		if(HAL_SPI_Transmit(&hspi1, pdata + 2, 1, 1000) != HAL_OK){
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

/**************************************//**************************************
 *@Brief: Reads an ILI9431 Register
 *@Params: register to read, data buffer, bytes to read
 *@Return: Err if data is not read, Ok if data is read
 *@Precondition: ILI9341 hardware should be initialized.
 *@Postcondition: pdata will contain read data
 **************************************//**************************************/
static ILI9341_Status_t ILI9341_IO_ReadReg(uint8_t reg, uint8_t* pdata, uint32_t length){
	ILI9341_CSState(GPIO_PIN_RESET);
	ILI9341_DCRSState(GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(&hspi1, &reg, 1, 1000) != HAL_OK){
        return ILI9341_Err;
	}
	ILI9341_DCRSState(GPIO_PIN_SET);

	if(length != 0){
		if(HAL_SPI_Receive(&hspi1, pdata, length, 1000) != HAL_OK){
			return ILI9341_Err;
		}
	}
	ILI9341_CSState(GPIO_PIN_SET);
	return ILI9341_Ok;
}

/**************************************//**************************************
 *@Brief: Sets/Clears Chip select line of ILI9341
 *@Params: desired state of CSN line
 *@Return: None
 *@Precondition: ILI9341 hardware should be initialized.
 *@Postcondition: CSN line will be set according to state
 **************************************//**************************************/
static void ILI9341_CSState(uint8_t state){
  if(state){
    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
  }
}

/**************************************//**************************************
 *@Brief: Sets Data/Command line to high or low
 *@Params: desired state
 *@Return: None
 *@Precondition: ILI9341 hardware should be initialized.
 *@Postcondition:ILI9341 data/command line will be set according to state parameter
 **************************************//**************************************/
static void ILI9341_DCRSState(uint8_t state){
  if(state){
    HAL_GPIO_WritePin(DCRS_GPIO_Port, DCRS_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(DCRS_GPIO_Port, DCRS_Pin, GPIO_PIN_RESET);
  }
}

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
ILI9341_IO_Drv_t ILI931_IO = {
		.init = ILI9341_IO_Init,
		.deinit = ILI9341_IO_DeInit,
		.write = ILI9341_IO_WriteReg,
		.read = ILI9341_IO_ReadReg,
		.ioctl = ILI9341_IO_ioctl
};
