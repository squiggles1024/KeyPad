/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Button.h"
#include "Joystick.h"
#include "SerialLED.h"
#include "ILI9341.h"
#include "art.h"
#include "TouchButton.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void InitButtons();
void InitJoystick();
void InitLEDs();
void InitScreen();
void InitTouchButtons();
//void InitTouch();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
Button_Handle_t Buttons[64];
Joystick_Handle_t Joystick;
SerialLED_Handle_t LED[4];
ILI9341_Handle_t LCD;
TouchButton_Handle_t TouchButton[12];
//FT6206_Handle_t TouchScreen;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */
  //MX_GPIO_Init();
  //MX_USART1_UART_Init();
  MX_USB_DEVICE_Init();
  InitButtons();
  InitJoystick();
  InitLEDs();
  InitScreen();
  InitTouchButtons();
  //InitTouch();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 for(uint8_t i = 0; i < 64; i++){
		 ButtonRead(&Buttons[i]);
	 }
	 for(uint8_t i = 0; i < 12; i++){
		 TouchButtonRead(&TouchButton[i]);
	 }
	JoystickRead(&Joystick);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void InitButtons(){
	Button_Init_Struct_t Settings = {
			.KeyFunction = 0,
			.ModKeyFunction = 0,
			.MouseFunction = 0,
			.WheelFunction = 0,
	};
	for(uint8_t i = 0; i < NUMBER_OF_IO_EXPANDERS*PINS_PER_EXPANDER; i++){
		Settings.ButtonIDNumber = i;
        ButtonInit(Settings, &Buttons[i], ButtonIO_Driver);
	}
}

void InitJoystick(){
    Joystick_Init_Struct_t Settings = {
    		.DeadZone = 2000,
			.Mode = Joystick4Way
    };
    JoystickInit(Settings, &Joystick, JoystickIO_Driver);
}

void InitLEDs(){
	SerialLED_InitStruct_t LED_Settings = {
			.green = 0xFF,
			.red = 0x00,
			.blue = 0xFF
	};
	for(uint8_t i = 0; i < NUMBER_OF_LEDS; i++){
		LED_Settings.address = i;
		SerialLEDInit(LED_Settings,&LED[i],LED_Drv);
	}
}

void InitScreen(){
	ILI9341_Init_Struct_t Settings = {
			.Orientation = XYExchangeXYMirror,
			.ScreenHeight = 240,
			.ScreenWidth = 320
	};
	ILI9341_Init(Settings, &LCD, ILI931_IO);
    ILI9341_Color_t Color = {
    		.red = 0,
    		.green = 0,
			.blue = 0
    };
    ILI9341_FillSceen(&LCD, Color);
    ILI9341_Image_t Image = {
    		.Height = 62,
			.Width = 62,
			.ImageLength = 62*62*3,
			.ImageData = char_image
    };
    LCD.Cursor.X = 40 - Image.Width / 2;
    LCD.Cursor.Y = 40 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = bag_image;
    LCD.Cursor.X = 120 - Image.Width / 2;
    LCD.Cursor.Y = 40 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = mounts_image;
    LCD.Cursor.X = 200 - Image.Width / 2;
    LCD.Cursor.Y = 40 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = LFD_image;
    LCD.Cursor.X = 280 - Image.Width / 2;
    LCD.Cursor.Y = 40 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = spells_image;
    LCD.Cursor.X = 40 - Image.Width / 2;
    LCD.Cursor.Y = 120 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = talents_image;
    LCD.Cursor.X = 120 - Image.Width / 2;
    LCD.Cursor.Y = 120 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = social_image;
    LCD.Cursor.X = 200 - Image.Width / 2;
    LCD.Cursor.Y = 120 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = guild_image;
    LCD.Cursor.X = 280 - Image.Width / 2;
    LCD.Cursor.Y = 120 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = map_image;
    LCD.Cursor.X = 40 - Image.Width / 2;
    LCD.Cursor.Y = 200 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = achievements_image;
    LCD.Cursor.X = 120 - Image.Width / 2;
    LCD.Cursor.Y = 200 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = adventureguide_image;
    LCD.Cursor.X = 200 - Image.Width / 2;
    LCD.Cursor.Y = 200 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);

    Image.ImageData = menu_image;
    LCD.Cursor.X = 280 - Image.Width / 2;
    LCD.Cursor.Y = 200 - Image.Height / 2;
    ILI9341_DisplayImage(&LCD, Image);
}

//void InitTouch(){
    //FT6206_Init(&TouchScreen, FT6202_Drv);
//}
void InitTouchButtons(){
	TouchButton_Init_Struct_t Settings = {
			.TopLeftBound = {
					.X_Position = 40 - 31,
					.Y_Position = 60 - 31
			},
			.BottomRightBound = {
					.X_Position = 40 + 31,
					.Y_Position = 60 + 31
			},
			.KeyFunction = 0,
			.ModKeyFunction = 0,
			.WheelFunction = 0,
			.MouseFunction = 0
	};
	TouchButtonInit(Settings, &TouchButton[0], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 120 - 31;
	Settings.BottomRightBound.X_Position = 120 + 31;
	TouchButtonInit(Settings, &TouchButton[1], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 200 - 31;
	Settings.BottomRightBound.X_Position = 200 + 31;
	TouchButtonInit(Settings, &TouchButton[2], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 280 - 31;
	Settings.BottomRightBound.X_Position = 280 + 31;
	TouchButtonInit(Settings, &TouchButton[3], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 40 - 31;
	Settings.BottomRightBound.X_Position = 40 + 31;
	Settings.TopLeftBound.Y_Position = 120 - 31;
	Settings.BottomRightBound.Y_Position = 120 + 31;
	TouchButtonInit(Settings, &TouchButton[4], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 120 - 31;
	Settings.BottomRightBound.X_Position = 120 + 31;
	TouchButtonInit(Settings, &TouchButton[5], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 200 - 31;
	Settings.BottomRightBound.X_Position = 200 + 31;
	TouchButtonInit(Settings, &TouchButton[6], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 280 - 31;
	Settings.BottomRightBound.X_Position = 280 + 31;
	TouchButtonInit(Settings, &TouchButton[7], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 40 - 31;
	Settings.BottomRightBound.X_Position = 40 + 31;
	Settings.TopLeftBound.Y_Position = 180 - 31;
	Settings.BottomRightBound.Y_Position = 180 + 31;
	TouchButtonInit(Settings, &TouchButton[8], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 120 - 31;
	Settings.BottomRightBound.X_Position = 120 + 31;
	TouchButtonInit(Settings, &TouchButton[9], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 200 - 31;
	Settings.BottomRightBound.X_Position = 200 + 31;
	TouchButtonInit(Settings, &TouchButton[10], TouchButton_IO_Driver);

	Settings.TopLeftBound.X_Position = 280 - 31;
	Settings.BottomRightBound.X_Position = 280 + 31;
	TouchButtonInit(Settings, &TouchButton[11], TouchButton_IO_Driver);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
