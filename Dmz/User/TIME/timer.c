
//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "timer.h"
#include "delay.h"
#include "hc_sr04.h"
//-----------------------------------------------------------------




//-----------------------------------------------------------------
// vvoid TIM2_Init(u16 arr,u16 psc)
//-----------------------------------------------------------------
//
// 函数功能: 定时器3中断初始化
// 入口参数: u16 arr：自动重装值
//					 u16 psc：时钟预分频数
// 返回参数: 无
// 注意事项: 定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//					 Ft=定时器工作频率,单位:Mhz
//					 这里使用的是定时器3!(定时器3挂在APB1上)
//
//-----------------------------------------------------------------
void TIM2_Init(u16 arr,u16 psc)
{  
  TIM2_Handler.Instance=TIM2;                          		// 通用定时器3
  TIM2_Handler.Init.Prescaler=psc;                     		// 分频系数
  TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    		// 向上计数器
  TIM2_Handler.Init.Period=arr;                        		// 自动装载值
  TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;	// 时钟分频因子
  HAL_TIM_Base_Init(&TIM2_Handler);
    
//  HAL_TIM_Base_Start_IT(&TIM2_Handler); // 使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}

//-----------------------------------------------------------------
// void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
//-----------------------------------------------------------------
//
// 函数功能: 定时器底册驱动，开启时钟，设置中断优先级
// 入口参数: TIM_HandleTypeDef *htim：定时器3句柄
// 返回参数: 无
// 注意事项: 此函数会被HAL_TIM_Base_Init()函数调用
//
//-----------------------------------------------------------------
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            // 使能TIM2时钟
		HAL_NVIC_SetPriority(TIM2_IRQn,1,3);    // 设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          // 开启ITM3中断   
	}
}

//-----------------------------------------------------------------
// void TIM2_IRQHandler(void)
//-----------------------------------------------------------------
//
// 函数功能: /定时器3中断服务函数
// 入口参数: 无
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TIM2_Handler);
}

//-----------------------------------------------------------------
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//-----------------------------------------------------------------
//
// 函数功能: 定时器3中断服务函数
// 入口参数: TIM_HandleTypeDef *htim：定时器3句柄
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim==(&TIM2_Handler))
  {
		cont++;
  }
}








//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
