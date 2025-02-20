/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "font.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define uchar unsigned char
#define uint unsigned int
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LCD_RST0 HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET)  
#define LCD_RST1 HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET)

#define LCD_CE0  HAL_GPIO_WritePin(LCD_CE_GPIO_Port,LCD_CE_Pin,GPIO_PIN_RESET)
#define LCD_CE1  HAL_GPIO_WritePin(LCD_CE_GPIO_Port,LCD_CE_Pin,GPIO_PIN_SET)

#define LCD_DC0  HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)
#define LCD_DC1  HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET)

#define LCD_DIN0 HAL_GPIO_WritePin(LCD_DIN_GPIO_Port,LCD_DIN_Pin,GPIO_PIN_RESET)
#define LCD_DIN1 HAL_GPIO_WritePin(LCD_DIN_GPIO_Port,LCD_DIN_Pin,GPIO_PIN_SET)

#define LCD_CLK0 HAL_GPIO_WritePin(LCD_CLK_GPIO_Port,LCD_CLK_Pin,GPIO_PIN_RESET)
#define LCD_CLK1 HAL_GPIO_WritePin(LCD_CLK_GPIO_Port,LCD_CLK_Pin,GPIO_PIN_SET)

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
void LCD_WriteByte(uchar dat, uchar command);
void LCD_Clear(void);
void LCD_Init(void);
void LCD_Set_XY(uchar X, uchar Y);
void LCD_WriteString(uchar X,uchar Y,char *s);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void LCD_WriteByte(uchar dat, uchar command)
{
    uchar i;
    LCD_CE0;                    // 使能芯片
    if (command == 0)           // 写命令
        LCD_DC0;
    else                        // 写数据
        LCD_DC1;
    
    for(i=0; i<8; i++)         // 发送一个字节
    {
        if(dat & 0x80)
            LCD_DIN1;
        else
            LCD_DIN0;
        LCD_CLK0;
        dat = dat << 1;
        LCD_CLK1;
    }
    LCD_CE1;                    // 禁止芯片
}

void LCD_Set_XY(uchar X, uchar Y)
{
    LCD_WriteByte(0x40 | Y, 0);    // Y轴地址
    LCD_WriteByte(0x80 | X, 0);    // X轴地址
}

void LCD_Clear(void)
{
    uchar i, j;
    for(i=0; i<6; i++)
    {
        LCD_Set_XY(0,i);
        for(j=0; j<84; j++)
            LCD_WriteByte(0x00, 1);
    }
}

void LCD_Init(void)
{
    LCD_RST0;                  // 复位LCD
    HAL_Delay(100);
    LCD_RST1;
    
    LCD_WriteByte(0x21, 0);    // 使用扩展指令集
    LCD_WriteByte(0xC8, 0);    // 设置LCD偏置电压
    LCD_WriteByte(0x06, 0);    // 温度校正
    LCD_WriteByte(0x13, 0);    // 1:48
    LCD_WriteByte(0x20, 0);    // 使用基本指令集
    LCD_WriteByte(0x0C, 0);    // 普通模式显示
    
    LCD_Clear();               // 清屏
}

void LCD_WriteChar(uchar x, uchar y, uchar c)
{
    uchar i;
    c -= 32;
    LCD_Set_XY(x, y);
    for(i=0; i<6; i++)
    {
        LCD_WriteByte(ASCII[c][i], 1);
    }
}

void LCD_WriteString(uchar X, uchar Y, char *s)
{
    while(*s)
    {
        LCD_WriteChar(X, Y, *s);
        s++;
        X += 6;
    }
}

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
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
	LCD_Init();
  HAL_Delay(100);
  
  LCD_WriteString(0, 0, "xidian");	//学校
	LCD_WriteString(0, 1, "xx");	//学院
	LCD_WriteString(0, 2, "xxx");		//专业
	LCD_WriteString(0, 3, "xxx");	//姓名
	LCD_WriteString(0, 4, "xxx");	//学号

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
