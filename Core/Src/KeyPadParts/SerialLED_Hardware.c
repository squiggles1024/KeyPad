/*
 * SerialLED_Hardware.c
 *
 *  Created on: May 22, 2022
 *      Author: evanl
 */

#include "SerialLED_Hardware.h"
#include "tim.h"
#include "dma.h"
#include "gpio.h"

#define BITS_PER_LED (24U)
#define RESET_SIGNAL_LENGTH (64) //(64 halfwords * 1.25uS per words = 80uS)
#define LED_DMA_BUFFER_LENGTH (NUMBER_OF_LEDS * BITS_PER_LED + RESET_SIGNAL_LENGTH)


typedef enum{
	LED_uninitialized = 0,
	LED_initialized
}LED_IO_Initialized_t;

static uint16_t LED_DMA_BUFFER[LED_DMA_BUFFER_LENGTH];
static LED_IO_Initialized_t initialize_status = LED_uninitialized;

//static const uint8_t TIM_PERIOD = 119;     //1.25uS with 96MHz clock
static const uint8_t ZERO_DUTY_CYCLE = 28; //.3uS
static const uint8_t ONE_DUTY_CYCLE = 58;  //.6uS
static const uint8_t RESET_DUTY_CYCLE = 0;

static void SerialLED_IO_Init(void){
	//ensure reset signal is 0
	for(uint32_t i = NUMBER_OF_LEDS * BITS_PER_LED; i < LED_DMA_BUFFER_LENGTH; i++){
		LED_DMA_BUFFER[i] = RESET_DUTY_CYCLE;
	}
	TIM3_GPIO_Init();
	TIM_DMA_Init();
    if(initialize_status == LED_uninitialized){
	    TIM3_Init();
	    initialize_status = LED_initialized;
    }

}

static void SerialLED_IO_DeInit(void){
	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
}

static void SerialLED_IO_Write(uint16_t Address, uint8_t red, uint8_t green, uint8_t blue){
	//HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
    for(uint16_t i = 0; i < 8; i++){
    	LED_DMA_BUFFER[(Address * BITS_PER_LED) + 0  + i] = green & (1 << (7 - i)) ? ONE_DUTY_CYCLE : ZERO_DUTY_CYCLE;
    	LED_DMA_BUFFER[(Address * BITS_PER_LED) + 8  + i] = red   & (1 << (7 - i)) ? ONE_DUTY_CYCLE : ZERO_DUTY_CYCLE;
    	LED_DMA_BUFFER[(Address * BITS_PER_LED) + 16 + i] = blue  & (1 << (7 - i)) ? ONE_DUTY_CYCLE : ZERO_DUTY_CYCLE;
    }
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t*)LED_DMA_BUFFER, LED_DMA_BUFFER_LENGTH);
}

SerialLED_IO_Drv_t LED_Drv = {
		.init = SerialLED_IO_Init,
		.deinit = SerialLED_IO_DeInit,
		.write = SerialLED_IO_Write
};
