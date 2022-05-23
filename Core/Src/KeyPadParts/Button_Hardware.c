/*
 * Button_Hardware.c
 *
 *  Created on: May 18, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "Button_Hardware.h"
#include "MCP23017.h"
#include "i2c.h"

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	ButtonIO_Uninitialized = 0,
	ButtonIO_Initialized
}Button_IO_InitStatus_t;

/**************************************//**************************************//**************************************
 * Private Variables
 **************************************//**************************************//**************************************/
static Button_IO_InitStatus_t initialize_status = ButtonIO_Uninitialized;

/**************************************//**************************************//**************************************
 * Private Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes hardware devices needed to read a button state
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: GPIO, I2C, DMA Peripherals and clocks will be enabled and ready to use
 **************************************//**************************************/
static void Button_IO_init(void){
	const MCP23017_Init_Struct_t InitSettings = {
			.Config = 0,
			.DefaultValue = MCP23017_NoPins,
			.IRQControl = MCP23017_NoPins,
			.IntEnable = MCP23017_NoPins,
			.Mode = MCP23017_AllPins,
			.PullUp = MCP23017_AllPins,
			.Polarity = MCP23017_AllPins
	};

	if(initialize_status == ButtonIO_Uninitialized){
	    MCP23017_Init(InitSettings, &Expander[0], MCP23017_IO1_Drv);
	    MCP23017_Init(InitSettings, &Expander[1], MCP23017_IO2_Drv);
	    MCP23017_Init(InitSettings, &Expander[2], MCP23017_IO3_Drv);
	    MCP23017_Init(InitSettings, &Expander[3], MCP23017_IO4_Drv);
	    MCP23017_ReadPins(&Expander[0]); //Start the Button-Read-DMA Engine
	    initialize_status = ButtonIO_Initialized;
	}
}

static void Button_IO_deinit(void){

	if(initialize_status == ButtonIO_Initialized){
	    MCP23017_DeInit(&Expander[0]);
	    MCP23017_DeInit(&Expander[1]);
	    MCP23017_DeInit(&Expander[2]);
	    MCP23017_DeInit(&Expander[3]);
	    initialize_status = ButtonIO_Uninitialized;
	}
}

/**************************************//**************************************
 *@Brief: Reads the state of a button
 *@Params: Number of the button to read
 *@Return: ButtonUnpressed if the button is not pressed, ButtonPressed if it is pressed.
 *@Precondition: Button IO should be initialized
 *@Postcondition: None
 **************************************//**************************************/
static ButtonState_t Button_IO_Read(uint8_t ButtonNumber){
	uint8_t ExpanderNumber = ButtonNumber / PINS_PER_EXPANDER;
	if(ExpanderNumber >= NUMBER_OF_IO_EXPANDERS){
		return ButtonUnpressed;
	}

    uint16_t ButtonStates = Expander[ExpanderNumber].PinStates;
    uint16_t ButtonPosition = ButtonNumber % PINS_PER_EXPANDER;
    if((ButtonStates & (1 << ButtonPosition)) != 0){
    	return ButtonPressed;
    } else {
    	return ButtonUnpressed;
    }
}

/**************************************//**************************************//**************************************
 * Public Function Definition
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Cycles through MCP23017 ICs and reads the input pins
 *@Params: I2C Handle used to communicate with MCP23017 IC
 *@Return: None
 *@Precondition: Button IO should be initialized.
 *@Postcondition: MCP23017 Pin states will be updated.
 **************************************//**************************************/
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	static uint8_t counter = 1;
	MCP23017_ReadPins(&Expander[counter % NUMBER_OF_IO_EXPANDERS]);
	counter++;
}
/**************************************//**************************************//**************************************
 * Public Variables
 **************************************//**************************************//**************************************/
MCP23017_Handle_t Expander[NUMBER_OF_IO_EXPANDERS];

const Button_IO_Drv_t ButtonIO_Driver = {
		.init = Button_IO_init,
		.read = Button_IO_Read,
		.deinit = Button_IO_deinit,
		.write = '\0',
		.ioctl = '\0'
};
