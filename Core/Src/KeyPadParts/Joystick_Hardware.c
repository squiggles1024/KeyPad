/*
 * Joystick_Hardware.c
 *
 *  Created on: May 20, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "Joystick_Hardware.h"
#include "gpio.h"
#include "adc.h"
#include "dma.h"

/**************************************//**************************************//**************************************
 * Private Variables
 **************************************//**************************************//**************************************/
static const uint8_t ADC_X_INDEX = 1;
static const uint8_t ADC_Y_INDEX = 0;
static const int16_t ADC_UPPER_LIMIT = 2047;
static const int16_t ADC_LOWER_LIMIT = -2048;
static const volatile int16_t adc_buffer[2];
static const int16_t ADC_X_OFFSET = 5;
static const int16_t ADC_Y_OFFSET = -30;

/**************************************//**************************************//**************************************
 * Private Function Defintions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Calls low level IO necessary to read joystick values
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: Low level hardware will be initialized. (DMA, ADC, GPIO)
 **************************************//**************************************/
static void JoystickIOInit(){
	ADC_GPIO_Init();
	ADC_DMA_Init();
	ADC1_Init();
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, 2);
}

/**************************************//**************************************
 *@Brief: Stops Joystick DMA transfers, disables its IRQ, and clears any pending IRQ.
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: DMA transfers from Joystick will be stopped.
 **************************************//**************************************/
static void JoystickIODeInit(void){
   HAL_ADC_Stop_DMA(&hadc1);
   HAL_NVIC_DisableIRQ(DMA2_Stream0_IRQn);
   HAL_NVIC_ClearPendingIRQ(DMA2_Stream0_IRQn);
}

/**************************************//**************************************
 *@Brief: Reads the joystick ADC buffer and scales the output to a 16 bit integer
 *@Params: Joystick Deadzone, X Position buffer, Y Position buffer
 *@Return: Position of the joystick
 *@Precondition: Joystick IO should be initialized
 *@Postcondition: X_Pos and Y_Pos will contain raw joystick value.
 **************************************//**************************************/
static JoystickState_t JoystickIORead(uint16_t Deadzone, int16_t *X_Pos, int16_t *Y_Pos){
	//Handle Deadzone values that are too large.
    if(Deadzone > INT16_MAX - 1){
    	Deadzone = INT16_MAX - 1;
    }

    //Calculate X Position
	int16_t temp = adc_buffer[ADC_X_INDEX] - 2048 + ADC_X_OFFSET;
	if(temp > ADC_UPPER_LIMIT){
		temp = ADC_UPPER_LIMIT;
	} else if (temp < ADC_LOWER_LIMIT){
		temp = ADC_LOWER_LIMIT;
	}
	temp = temp * 16; //convert to 16 bit number
	if(temp > Deadzone || temp < -(int16_t)Deadzone){
	    *X_Pos = temp;
	} else {
        *X_Pos = 0;
	}

	//Calculate Y Position
	temp = adc_buffer[ADC_Y_INDEX] - 2048 + ADC_Y_OFFSET;
	if(temp > ADC_UPPER_LIMIT){
		temp = ADC_UPPER_LIMIT;
	} else if (temp < ADC_LOWER_LIMIT){
		temp = ADC_LOWER_LIMIT;
	}
	temp = temp * 16; //convert to 16 bit number
	if(temp > Deadzone || temp < -(int16_t)Deadzone){
	    *Y_Pos = temp;
	} else {
        *Y_Pos = 0;
	}

	if(*X_Pos == 0 && *Y_Pos == 0){
		return JoystickNeutral;
	} else if(*X_Pos > 0 && *Y_Pos == 0){
		return Joystick_Right;

	} else if(*X_Pos > 0 && *Y_Pos > 0){
		return Joystick_UpRight;

	} else if(*X_Pos == 0 && *Y_Pos > 0){
		return Joystick_Up;

	} else if(*X_Pos < 0 && *Y_Pos > 0){
		return Joystick_UpLeft;

	} else if(*X_Pos < 0 && *Y_Pos == 0){
		return Joystick_Left;

	} else if(*X_Pos < 0 && *Y_Pos < 0){
		return Joystick_DownLeft;

	} else if(*X_Pos == 0 && *Y_Pos < 0){
		return Joystick_Down;
	}
	else{
		return Joystick_DownRight;
	}

}

/**************************************//**************************************//**************************************
 * Exported Variable Definitions
 **************************************//**************************************//**************************************/
const Joystick_IO_Drv_t JoystickIO_Driver = {
	.init = JoystickIOInit,
	.deinit = JoystickIODeInit,
	.read = JoystickIORead,
	.write = '\0',
	.ioctl = '\0'
};
