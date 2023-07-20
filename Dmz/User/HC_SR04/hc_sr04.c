
#include "hc_sr04.h"
TIM_HandleTypeDef TIM2_Handler;      // 定时器3句柄
#include "time.h"
float lengh=0;
int cont=0;

void gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin=TRIG_Pin_F|TRIG_Pin_L|TRIG_Pin_R;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(TRIG_GPIO_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin=ECHO_Pin_F|ECHO_Pin_L|ECHO_Pin_R;
	HAL_GPIO_Init(TRIG_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(TRIG_GPIO_Port, ECHO_Pin_F, GPIO_PIN_RESET);
	
	
}

float hc_sr04(int direction)
{
	lengh =0;
	for(int i =0;i<10;i++){
		switch(direction)
		{
			case front:
			{
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin_F, GPIO_PIN_SET);
				delay_us(11);
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin_F, GPIO_PIN_RESET);
				while(HAL_GPIO_ReadPin(TRIG_GPIO_Port, ECHO_Pin_F)==GPIO_PIN_RESET);
				HAL_TIM_Base_Start_IT(&TIM2_Handler);
				while(HAL_GPIO_ReadPin(TRIG_GPIO_Port, ECHO_Pin_F)==GPIO_PIN_SET);
				HAL_TIM_Base_Stop_IT(&TIM2_Handler);
			}
				break;
			case lift:
			{
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin_L, GPIO_PIN_SET);
				delay_us(11);
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin_L, GPIO_PIN_RESET);
				while(HAL_GPIO_ReadPin(TRIG_GPIO_Port, ECHO_Pin_L)==GPIO_PIN_RESET);
				HAL_TIM_Base_Start_IT(&TIM2_Handler);
				while(HAL_GPIO_ReadPin(TRIG_GPIO_Port, ECHO_Pin_L)==GPIO_PIN_SET);
				HAL_TIM_Base_Stop_IT(&TIM2_Handler);
			}
				break;
			case right:
			{
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin_R, GPIO_PIN_SET);
				delay_us(11);
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin_R, GPIO_PIN_RESET);
				while(HAL_GPIO_ReadPin(TRIG_GPIO_Port, ECHO_Pin_R)==GPIO_PIN_RESET);
				HAL_TIM_Base_Start_IT(&TIM2_Handler);
				while(HAL_GPIO_ReadPin(TRIG_GPIO_Port, ECHO_Pin_R)==GPIO_PIN_SET);
				HAL_TIM_Base_Stop_IT(&TIM2_Handler);
			}
				break;			
		}
		
		int time  = __HAL_TIM_GET_COUNTER(&TIM2_Handler);
		lengh = lengh +(time + cont * 10000) / 58.0;
		__HAL_TIM_SET_COUNTER(&TIM2_Handler, 0);//定时器计数寄存器置0
		cont = 0;
	}
	return lengh/10;
}


void hc_sr04_function()
{
	if(hc_sr04(front)<2)
		{
			comSendBuf(COM5,(uint8_t*)"cmd6",8);
			delay_ms(2000);
		}			
		
		if(hc_sr04(lift)<2) 
			{
			comSendBuf(COM5,(uint8_t*)"cmd7",8);
			delay_ms(2000);
		}		
		if(hc_sr04(right)<2) 
		{
			comSendBuf(COM5,(uint8_t*)"cmd8",8);
			delay_ms(2000);
		}

}



