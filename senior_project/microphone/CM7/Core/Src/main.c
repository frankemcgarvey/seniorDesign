/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


typedef enum{
	NONE,
	BUSY,
	READY,
	DONE,
	HALF,
	FULL,
}flag_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

CRC_HandleTypeDef hcrc;

SAI_HandleTypeDef hsai_BlockA1;
DMA_HandleTypeDef hdma_sai1_a;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_tx;

/* USER CODE BEGIN PV */

static volatile flag_t dmaFlag = NONE;
static volatile flag_t timFlag = NONE;
static buffer_t * const buffer = (buffer_t *) 0x30040000;
static dsp_buffer_t dsp[CHANNEL_NUMBER];
static float coeff[TAPS] = {0.000000e+00, 7.300727e-06, 1.243410e-05, 1.381998e-05, 1.003356e-05, -6.264190e-20, -1.682791e-05, -4.033069e-05, -6.964127e-05, -1.031370e-04, -1.385128e-04, -1.729364e-04, -2.032766e-04, -2.263896e-04, -2.394373e-04, -2.402103e-04, -2.274203e-04, -2.009315e-04, -1.618987e-04, -1.127899e-04, -5.727802e-05, -4.073263e-20, 5.380979e-05, 9.878695e-05, 1.299724e-04, 1.433707e-04, 1.364817e-04, 1.087504e-04, 6.188515e-05, -1.035705e-13, -7.045304e-05, -1.409774e-04, -2.015508e-04, -2.413475e-04, -2.496241e-04, -2.167071e-04, -1.350108e-04, -1.981424e-19, 1.889891e-04, 4.281532e-04, 7.089243e-04, 1.018024e-03, 1.337904e-03, 1.647567e-03, 1.923752e-03, 2.142413e-03, 2.280408e-03, 2.317285e-03, 2.237042e-03, 2.029705e-03, 1.692611e-03, 1.231262e-03, 6.596523e-04, -1.948869e-18, -7.181333e-04, -1.459325e-03, -2.184303e-03, -2.852382e-03, -3.424163e-03, -3.864329e-03, -4.144312e-03, -4.244661e-03, -4.156873e-03, -3.884549e-03, -3.443733e-03, -2.862350e-03, -2.178735e-03, -1.439300e-03, -6.954628e-04, 2.541807e-18, 5.969126e-04, 1.051724e-03, 1.331286e-03, 1.416094e-03, 1.302706e-03, 1.005118e-03, 5.548963e-04, -4.512864e-13, -5.977377e-04, -1.166370e-03, -1.628655e-03, -1.907666e-03, -1.932842e-03, -1.646078e-03, -1.007430e-03, 3.305444e-18, 1.366406e-03, 3.053181e-03, 4.992649e-03, 7.089783e-03, 9.225915e-03, 1.126436e-02, 1.305769e-02, 1.445633e-02, 1.531793e-02, 1.551707e-02, 1.495462e-02, 1.356612e-02, 1.132864e-02, 8.265652e-03, 4.449299e-03, -4.410362e-18, -4.916891e-03, -1.009727e-02, -1.530709e-02, -2.029343e-02, -2.479723e-02, -2.856705e-02, -3.137313e-02, -3.302088e-02, -3.336300e-02, -3.230956e-02, -2.983530e-02, -2.598367e-02, -2.086732e-02, -1.466479e-02, -7.613601e-03, 0.000000e+00, 7.854244e-03, 1.560718e-02, 2.291343e-02, 2.944148e-02, 3.489052e-02, 3.900587e-02, 4.159228e-02, 4.252416e-02, 4.159228e-02, 3.900587e-02, 3.489052e-02, 2.944148e-02, 2.291343e-02, 1.560718e-02, 7.854244e-03, 0.000000e+00, -7.613601e-03, -1.466479e-02, -2.086732e-02, -2.598367e-02, -2.983530e-02, -3.230956e-02, -3.336300e-02, -3.302088e-02, -3.137313e-02, -2.856705e-02, -2.479723e-02, -2.029343e-02, -1.530709e-02, -1.009727e-02, -4.916891e-03, -4.410362e-18, 4.449299e-03, 8.265652e-03, 1.132864e-02, 1.356612e-02, 1.495462e-02, 1.551707e-02, 1.531793e-02, 1.445633e-02, 1.305769e-02, 1.126436e-02, 9.225915e-03, 7.089783e-03, 4.992649e-03, 3.053181e-03, 1.366406e-03, 3.305444e-18, -1.007430e-03, -1.646078e-03, -1.932842e-03, -1.907666e-03, -1.628655e-03, -1.166370e-03, -5.977377e-04, -4.512864e-13, 5.548963e-04, 1.005118e-03, 1.302706e-03, 1.416094e-03, 1.331286e-03, 1.051724e-03, 5.969126e-04, 2.541807e-18, -6.954628e-04, -1.439300e-03, -2.178735e-03, -2.862350e-03, -3.443733e-03, -3.884549e-03, -4.156873e-03, -4.244661e-03, -4.144312e-03, -3.864329e-03, -3.424163e-03, -2.852382e-03, -2.184303e-03, -1.459325e-03, -7.181333e-04, -1.948869e-18, 6.596523e-04, 1.231262e-03, 1.692611e-03, 2.029705e-03, 2.237042e-03, 2.317285e-03, 2.280408e-03, 2.142413e-03, 1.923752e-03, 1.647567e-03, 1.337904e-03, 1.018024e-03, 7.089243e-04, 4.281532e-04, 1.889891e-04, -1.981424e-19, -1.350108e-04, -2.167071e-04, -2.496241e-04, -2.413475e-04, -2.015508e-04, -1.409774e-04, -7.045304e-05, -1.035705e-13, 6.188515e-05, 1.087504e-04, 1.364817e-04, 1.433707e-04, 1.299724e-04, 9.878695e-05, 5.380979e-05, -4.073263e-20, -5.727802e-05, -1.127899e-04, -1.618987e-04, -2.009315e-04, -2.274203e-04, -2.402103e-04, -2.394373e-04, -2.263896e-04, -2.032766e-04, -1.729364e-04, -1.385128e-04, -1.031370e-04, -6.964127e-05, -4.033069e-05, -1.682791e-05, -6.264190e-20, 1.003356e-05, 1.381998e-05, 1.243410e-05, 7.300727e-06, 0.000000e+00};
PDM_Filter_Handler_t  PDM_FilterHandler[CHANNEL_NUMBER];
PDM_Filter_Config_t   PDM_FilterConfig[CHANNEL_NUMBER];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_CRC_Init(void);
static void MX_SAI1_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
static void Clean(float *buffer, uint32_t byte);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
  int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

/* USER CODE BEGIN Boot_Mode_Sequence_1 */


/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
/* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
HSEM notification */
/*HW semaphore Clock enable*/
__HAL_RCC_HSEM_CLK_ENABLE();
/*Take HSEM */
HAL_HSEM_FastTake(HSEM_ID_0);
/*Release HSEM in order to notify the CPU2(CM4)*/
HAL_HSEM_Release(HSEM_ID_0,0);
/* wait until CPU2 wakes up from stop mode */
timeout = 0xFFFF;
while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
if ( timeout < 0 )
{
Error_Handler();
}
/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_CRC_Init();
  MX_SAI1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  FIR_Filter_Init(&dsp[0], CHANNEL_NUMBER, &coeff[0]);

  pdm_to_pcm_init((PDM_Filter_Handler_t*)&PDM_FilterHandler[0], (PDM_Filter_Config_t*)&PDM_FilterConfig[0], CHANNEL_NUMBER);

  timFlag = NONE;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  HAL_SAI_Receive_DMA(&hsai_BlockA1, (uint8_t*)&buffer->pdmBuffer[0], BUFFER_SIZE);

  HAL_Delay(2000);

  HAL_TIM_Base_Start_IT(&htim1);

  while (timFlag != DONE){

	  //================
	  //Wait for Half of the buffer to be filled
	  while(dmaFlag != HALF){}
	  //Reset Flag
	  dmaFlag = NONE;
	  //Filter PDM to PCM
	  pdm_to_pcm(&PDM_FilterHandler[0],	(uint8_t*)&buffer->pdmBuffer[0], (uint16_t(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer[0][0], CHANNEL_NUMBER);
	  //Q15 to Float
	  Q15_To_Float((q15_t(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer[0][0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[0][0], CHANNEL_NUMBER);
	  //FIR Filter
	  FIR_Filter(&dsp[0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[0][0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[0][0], CHANNEL_NUMBER);
	  //Clean
	  Clean((float*)&buffer->pcmBuffer_flt[0][0], 4*PCM_CHUNK_SIZE*CHANNEL_NUMBER);
	  //Transmit PCM
	  HAL_UART_Transmit_DMA(&huart3, (uint8_t*)&buffer->pcmBuffer_flt[0][0], 4*PCM_CHUNK_SIZE*CHANNEL_NUMBER);
	  //================

	  //================
	  //Wait for the second Half of the buffer to be filled
	  while(dmaFlag != FULL){}
	  //Reset Flag
	  dmaFlag = NONE;
	  //Filter PDM to PCM
	  pdm_to_pcm(&PDM_FilterHandler[0],	(uint8_t*)&buffer->pdmBuffer[BUFFER_SIZE/2], (uint16_t(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer[CHANNEL_NUMBER][0], CHANNEL_NUMBER);
	  //Q15 to Float
	  Q15_To_Float((q15_t(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer[CHANNEL_NUMBER][0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[CHANNEL_NUMBER][0], CHANNEL_NUMBER);
	  //FIR Filter
	  FIR_Filter(&dsp[0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[CHANNEL_NUMBER][0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[CHANNEL_NUMBER][0], CHANNEL_NUMBER);
	  //Clean
	  Clean((float*)&buffer->pcmBuffer_flt[CHANNEL_NUMBER][0], 4*PCM_CHUNK_SIZE*CHANNEL_NUMBER);
	  //Transmit PCM
	  HAL_UART_Transmit_DMA(&huart3, (uint8_t*)&buffer->pcmBuffer_flt[CHANNEL_NUMBER][0], 4*PCM_CHUNK_SIZE*CHANNEL_NUMBER);
	  //================
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }



  while(1){}
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV4;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  __HAL_CRC_DR_RESET(&hcrc);
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief SAI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SAI1_Init(void)
{

  /* USER CODE BEGIN SAI1_Init 0 */

  /* USER CODE END SAI1_Init 0 */

  /* USER CODE BEGIN SAI1_Init 1 */

  /* USER CODE END SAI1_Init 1 */
  hsai_BlockA1.Instance = SAI1_Block_A;
  hsai_BlockA1.Init.Protocol = SAI_FREE_PROTOCOL;
  hsai_BlockA1.Init.AudioMode = SAI_MODEMASTER_RX;
  hsai_BlockA1.Init.DataSize = SAI_DATASIZE_16;
  hsai_BlockA1.Init.FirstBit = SAI_FIRSTBIT_MSB;
  hsai_BlockA1.Init.ClockStrobing = SAI_CLOCKSTROBING_FALLINGEDGE;
  hsai_BlockA1.Init.Synchro = SAI_ASYNCHRONOUS;
  hsai_BlockA1.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
  hsai_BlockA1.Init.NoDivider = SAI_MASTERDIVIDER_DISABLE;
  hsai_BlockA1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_FULL;
  hsai_BlockA1.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_MCKDIV;
  hsai_BlockA1.Init.Mckdiv = 0;
  hsai_BlockA1.Init.MonoStereoMode = SAI_STEREOMODE;
  hsai_BlockA1.Init.CompandingMode = SAI_NOCOMPANDING;
  hsai_BlockA1.Init.PdmInit.Activation = ENABLE;
  hsai_BlockA1.Init.PdmInit.MicPairsNbr = 1;
  hsai_BlockA1.Init.PdmInit.ClockEnable = SAI_PDM_CLOCK1_ENABLE;
  hsai_BlockA1.FrameInit.FrameLength = 16;
  hsai_BlockA1.FrameInit.ActiveFrameLength = 1;
  hsai_BlockA1.FrameInit.FSDefinition = SAI_FS_STARTFRAME;
  hsai_BlockA1.FrameInit.FSPolarity = SAI_FS_ACTIVE_HIGH;
  hsai_BlockA1.FrameInit.FSOffset = SAI_FS_FIRSTBIT;
  hsai_BlockA1.SlotInit.FirstBitOffset = 0;
  hsai_BlockA1.SlotInit.SlotSize = SAI_SLOTSIZE_DATASIZE;
  hsai_BlockA1.SlotInit.SlotNumber = 1;
  hsai_BlockA1.SlotInit.SlotActive = 0x00000001;
  if (HAL_SAI_Init(&hsai_BlockA1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SAI1_Init 2 */

  /* USER CODE END SAI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 20000;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 60000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  __HAL_TIM_CLEAR_IT(&htim1, TIM_FLAG_UPDATE);
  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 4000000;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_8_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_8_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

static void Clean(float *buffer, uint32_t byte){
	SCB_CleanDCache_by_Addr((uint32_t*)&buffer[0], byte);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai){
	dmaFlag = HALF;
}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai){
	dmaFlag = FULL;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim1){
	  HAL_TIM_Base_Stop_IT(htim);
	  timFlag = DONE;
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
