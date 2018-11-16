/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f3xx.h"
#include "stm32f3_discovery.h"
			
void GPIO_Init(void);
void TIM_Init(void);
void NVIC_Init(void);
void UART4_Init(void);

UART_HandleTypeDef huart4;
TIM_HandleTypeDef htim3;
uint32_t inputCaptureVal;


int main(void)
{

	GPIO_Init();
	TIM_Init();
	NVIC_Init();
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_5);


	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);

	char buffer[16];

	for(;;)
	{
		inputCaptureVal = __HAL_TIM_GET_COUNTER(&htim3);
		sprintf(buffer,"Val:%ld\n", inputCaptureVal);
		HAL_Delay(500);
		HAL_UART_Transmit(&huart4, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
	}
}

void GPIO_Init(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();	// Timer, Output
	__HAL_RCC_GPIOD_CLK_ENABLE();	// Output
	__HAL_RCC_GPIOC_CLK_ENABLE();	// UART

	GPIO_InitTypeDef GPIOA6_Init;

	GPIOA6_Init.Pin = GPIO_PIN_6;		// Pin6 is Tim3Ch1
	GPIOA6_Init.Mode = GPIO_MODE_AF_PP;	// AF Push Pull
	GPIOA6_Init.Alternate = GPIO_AF2_TIM3; // Alternate Function
	GPIOA6_Init.Pull = GPIO_NOPULL;
	GPIOA6_Init.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &GPIOA6_Init);

	GPIO_InitTypeDef GPIOA0_Init;

	GPIOA0_Init.Pin = GPIO_PIN_0;
	GPIOA0_Init.Mode = GPIO_MODE_IT_RISING;
	GPIOA0_Init.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA, &GPIOA0_Init);

	GPIO_InitTypeDef GPIOD_Init;

	GPIOD_Init.Pin = GPIO_PIN_5;
	GPIOD_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOD_Init.Pull = GPIO_NOPULL;
	GPIOD_Init.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOD, &GPIOD_Init);


	GPIO_InitTypeDef GPIOA4_Init;

	GPIOA4_Init.Pin = GPIO_PIN_4;
	GPIOA4_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOA4_Init.Pull = GPIO_NOPULL;
	GPIOA4_Init.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &GPIOA4_Init);

	GPIO_InitTypeDef UART_Init;
	/* Peripheral clock enable */
	__HAL_RCC_UART4_CLK_ENABLE();

	/**UART4 GPIO Configuration
	PC10     ------> UART4_TX
	PC11     ------> UART4_RX
	 */
	UART_Init.Pin = GPIO_PIN_10|GPIO_PIN_11;
	UART_Init.Mode = GPIO_MODE_AF_PP;
	UART_Init.Pull = GPIO_NOPULL;
	UART_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	UART_Init.Alternate = GPIO_AF5_UART4;
	HAL_GPIO_Init(GPIOC, &UART_Init);



}

void TIM_Init(void) {
		//Enable clock for TIM3
		__HAL_RCC_TIM3_CLK_ENABLE();

		// TIM3 Base Initialization
		htim3.Instance = TIM3;
		htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim3.Init.Period = 65535;
		htim3.Init.Prescaler = 48000;
		HAL_TIM_Base_Init(&htim3);

		// Clock source configuration
		TIM_ClockConfigTypeDef clkSrcConfig;
		clkSrcConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
		HAL_TIM_ConfigClockSource(&htim3, &clkSrcConfig);

		// Initialize Input capture
		HAL_TIM_IC_Init(&htim3);

		// Master Config
		TIM_MasterConfigTypeDef mstrCfg;
		mstrCfg.MasterOutputTrigger = TIM_TRGO_RESET;
		mstrCfg.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		HAL_TIMEx_MasterConfigSynchronization(&htim3, &mstrCfg);

		// Input Capture Configuration
		TIM_IC_InitTypeDef IC_config;
		IC_config.ICFilter = 15;	// Why?
		IC_config.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
		IC_config.ICPrescaler = TIM_ICPSC_DIV1;
		IC_config.ICSelection = TIM_ICSELECTION_DIRECTTI;
		HAL_TIM_IC_ConfigChannel(&htim3, &IC_config, TIM_CHANNEL_1);

		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);

		HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
		HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
		HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}



void NVIC_Init(void) {
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	/* UART4 interrupt Init */
	HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(UART4_IRQn);

}

void UART4_Init(void)
{


	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	HAL_UART_Init(&huart4);
}
