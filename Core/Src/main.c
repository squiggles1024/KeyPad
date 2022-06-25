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
#include "usb_device.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "KeyPad.h"
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

void InitScreen();

//void InitTouch();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
ILI9341_Handle_t LCD;
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
  MX_USB_DEVICE_Init();
  InitScreen();
  KeyPadInit();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 /*
	 for(uint8_t i = 0; i < 64; i++){
		 ButtonRead(&KeyPad.Buttons[i]);
	 }
	 for(uint8_t i = 0; i < 12; i++){
		 TouchButtonRead(&KeyPad.TouchButton[i]);
	 }
	JoystickRead(&KeyPad.Joystick);
	*/
	 UpdateKeyPadTxBuffers();
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
    HAL_Delay(100);
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
