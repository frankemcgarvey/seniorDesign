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
static buffer_t * const buffer = (buffer_t *) 0x30000000;
static dsp_buffer_t dsp[CHANNEL_NUMBER];
static float coeff[TAPS] = {-0.0000001708, -0.0000002072, -0.0000002839, -0.0000004056, -0.0000005722, -0.0000007792, -0.0000010175, -0.0000012738, -0.0000015317, -0.0000017714, -0.0000019718, -0.0000021107, -0.0000021664, -0.0000021195, -0.0000019540, -0.0000016590, -0.0000012305, -0.0000006729, 0.0000000000, 0.0000007640, 0.0000015840, 0.0000024139, 0.0000031980, 0.0000038724, 0.0000043672, 0.0000046105, 0.0000045326, 0.0000040711, 0.0000031769, 0.0000018207, 0.0000000000, -0.0000022540, -0.0000048702, -0.0000077314, -0.0000106698, -0.0000134641, -0.0000158383, -0.0000174636, -0.0000179629, -0.0000169184, -0.0000138833, -0.0000083961, 0.0000000000, 0.0000117360, 0.0000271918, 0.0000466687, 0.0000703603, 0.0000983228, 0.0001304450, 0.0001664201, 0.0002057210, 0.0002475790, 0.0002909693, 0.0003346029, 0.0003769283, 0.0004161424, 0.0004502125, 0.0004769106, 0.0004938592, 0.0004985898, 0.0004886130, 0.0004614993, 0.0004149700, 0.0003469949, 0.0002558953, 0.0001404502, -0.0000000000, -0.0001654534, -0.0003551552, -0.0005675193, -0.0008000660, -0.0010493804, -0.0013110950, -0.0015799000, -0.0018495834, -0.0021131027, -0.0023626911, -0.0025899960, -0.0027862496, -0.0029424720, -0.0030496991, -0.0030992355, -0.0030829236, -0.0029934247, -0.0028245046, -0.0025713127, -0.0022306510, -0.0018012194, -0.0012838305, -0.0006815852, 0.0000000000, 0.0007529215, 0.0015666786, 0.0024283314, 0.0033226281, 0.0042322059, 0.0051378626, 0.0060188994, 0.0068535269, 0.0076193302, 0.0082937833, 0.0088548018, 0.0092813214, 0.0095538879, 0.0096552437, 0.0095708966, 0.0092896475, 0.0088040717, 0.0081109283, 0.0072114873, 0.0061117630, 0.0048226360, 0.0033598649, 0.0017439707, -0.0000000000, -0.0018428368, -0.0037516486, -0.0056904596, -0.0076209079, -0.0095030330, -0.0112961382, -0.0129597001, -0.0144543145, -0.0157426503, -0.0167903882, -0.0175671130, -0.0180471539, -0.0182103217, -0.0180425569, -0.0175364278, -0.0166915022, -0.0155145479, -0.0140195815, -0.0122277252, -0.0101669105, -0.0078714006, -0.0053811576, -0.0027410621, 0.0000000000, 0.0027901600, 0.0055756764, 0.0083021037, 0.0109154973, 0.0133636147, 0.0155971004, 0.0175706018, 0.0192438122, 0.0205823965, 0.0215587877, 0.0221528225, 0.0223522093, 0.0221528225, 0.0215587877, 0.0205823965, 0.0192438122, 0.0175706018, 0.0155971004, 0.0133636147, 0.0109154973, 0.0083021037, 0.0055756764, 0.0027901600, 0.0000000000, -0.0027410621, -0.0053811576, -0.0078714006, -0.0101669105, -0.0122277252, -0.0140195815, -0.0155145479, -0.0166915022, -0.0175364278, -0.0180425569, -0.0182103217, -0.0180471539, -0.0175671130, -0.0167903882, -0.0157426503, -0.0144543145, -0.0129597001, -0.0112961382, -0.0095030330, -0.0076209079, -0.0056904596, -0.0037516486, -0.0018428368, -0.0000000000, 0.0017439707, 0.0033598649, 0.0048226360, 0.0061117630, 0.0072114873, 0.0081109283, 0.0088040717, 0.0092896475, 0.0095708966, 0.0096552437, 0.0095538879, 0.0092813214, 0.0088548018, 0.0082937833, 0.0076193302, 0.0068535269, 0.0060188994, 0.0051378626, 0.0042322059, 0.0033226281, 0.0024283314, 0.0015666786, 0.0007529215, 0.0000000000, -0.0006815852, -0.0012838305, -0.0018012194, -0.0022306510, -0.0025713127, -0.0028245046, -0.0029934247, -0.0030829236, -0.0030992355, -0.0030496991, -0.0029424720, -0.0027862496, -0.0025899960, -0.0023626911, -0.0021131027, -0.0018495834, -0.0015799000, -0.0013110950, -0.0010493804, -0.0008000660, -0.0005675193, -0.0003551552, -0.0001654534, -0.0000000000, 0.0001404502, 0.0002558953, 0.0003469949, 0.0004149700, 0.0004614993, 0.0004886130, 0.0004985898, 0.0004938592, 0.0004769106, 0.0004502125, 0.0004161424, 0.0003769283, 0.0003346029, 0.0002909693, 0.0002475790, 0.0002057210, 0.0001664201, 0.0001304450, 0.0000983228, 0.0000703603, 0.0000466687, 0.0000271918, 0.0000117360, 0.0000000000, -0.0000083961, -0.0000138833, -0.0000169184, -0.0000179629, -0.0000174636, -0.0000158383, -0.0000134641, -0.0000106698, -0.0000077314, -0.0000048702, -0.0000022540, 0.0000000000, 0.0000018207, 0.0000031769, 0.0000040711, 0.0000045326, 0.0000046105, 0.0000043672, 0.0000038724, 0.0000031980, 0.0000024139, 0.0000015840, 0.0000007640, 0.0000000000, -0.0000006729, -0.0000012305, -0.0000016590, -0.0000019540, -0.0000021195, -0.0000021664, -0.0000021107, -0.0000019718, -0.0000017714, -0.0000015317, -0.0000012738, -0.0000010175, -0.0000007792, -0.0000005722, -0.0000004056, -0.0000002839, -0.0000002072, -0.0000001708};
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

  FIR_Filter_Init(&dsp[0], &coeff[0]);

  pdm_to_pcm_init((PDM_Filter_Handler_t*)&PDM_FilterHandler[0], (PDM_Filter_Config_t*)&PDM_FilterConfig[0]);

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
	  pdm_to_pcm(&PDM_FilterHandler[0],	(uint8_t*)&buffer->pdmBuffer[0], (uint16_t(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer[0][0]);
	  //Q15 to Float
	  Q15_To_Float((q15_t(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer[0][0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[0][0]);
	  //FIR Filter
	  FIR_Filter(&dsp[0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[0][0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[0][0]);
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
	  pdm_to_pcm(&PDM_FilterHandler[0],	(uint8_t*)&buffer->pdmBuffer[BUFFER_SIZE/2], (uint16_t(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer[CHANNEL_NUMBER][0]);
	  //Q15 to Float
	  Q15_To_Float((q15_t(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer[CHANNEL_NUMBER][0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[CHANNEL_NUMBER][0]);
	  //FIR Filter
	  FIR_Filter(&dsp[0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[CHANNEL_NUMBER][0], (float(*)[PCM_CHUNK_SIZE])&buffer->pcmBuffer_flt[CHANNEL_NUMBER][0]);
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
