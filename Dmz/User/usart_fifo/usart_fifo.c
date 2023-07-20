

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "usart_fifo.h"
#include "delay.h"
#include "string.h"
//-----------------------------------------------------------------
UART_HandleTypeDef USART1_Handler;	
UART_HandleTypeDef USART3_Handler;	
UART_HandleTypeDef UART4_Handler;	
UART_HandleTypeDef UART5_Handler;	
//-----------------------------------------------------------------
// void uart_init(void)
//-----------------------------------------------------------------
//
// 函数功能: 串口初始化
// 入口参数: 无
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void uart_init(void)
{	
#if UART1_FIFO_EN == 1
	UART1_T.uart = USART1;								// STM32 串口设备
	UART1_T.TxBuf = UART1_TxBuf;					// 发送缓冲区指针
	UART1_T.RxBuf = UART1_RxBuf;					// 接收缓冲区指针
	UART1_T.TxBufSize = UART1_TX_BUF_SIZE;// 发送缓冲区大小
	UART1_T.RxBufSize = UART1_RX_BUF_SIZE;// 接收缓冲区大小
	UART1_T.TxWrite = 0;									// 发送FIFO写索引
	UART1_T.TxRead = 0;										// 发送FIFO读索引
	UART1_T.RxWrite = 0;									// 接收FIFO写索引
	UART1_T.RxRead = 0;										// 接收FIFO读索引
	UART1_T.RxCount = 0;									// 接收到的新数据个数
	UART1_T.TxCount = 0;									// 待发送的数据个数
	UART1_T.Sending = 0;									// 正在发送中标志
	
	SetUartParam(USART1,  UART1_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);

#endif

#if UART3_FIFO_EN == 1
	UART3_T.uart = USART3;								// STM32 串口设备
	UART3_T.TxBuf = UART3_TxBuf;					// 发送缓冲区指针
	UART3_T.RxBuf = UART3_RxBuf;					// 接收缓冲区指针
	UART3_T.TxBufSize = UART3_TX_BUF_SIZE;// 发送缓冲区大小
	UART3_T.RxBufSize = UART3_RX_BUF_SIZE;// 接收缓冲区大小
	UART3_T.TxWrite = 0;									// 发送FIFO写索引
	UART3_T.TxRead = 0;										// 发送FIFO读索引
	UART3_T.RxWrite = 0;									// 接收FIFO写索引
	UART3_T.RxRead = 0;										// 接收FIFO读索引
	UART3_T.RxCount = 0;									// 接收到的新数据个数
	UART3_T.TxCount = 0;									// 待发送的数据个数
	UART3_T.Sending = 0;									// 正在发送中标志
	SetUartParam(USART3,  UART3_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);
#endif
#if UART4_FIFO_EN == 1
	UART4_T.uart = UART4;								// STM32 串口设备
	UART4_T.TxBuf = UART4_TxBuf;					// 发送缓冲区指针
	UART4_T.RxBuf = UART4_RxBuf;					// 接收缓冲区指针
	UART4_T.TxBufSize = UART4_TX_BUF_SIZE;// 发送缓冲区大小
	UART4_T.RxBufSize = UART4_RX_BUF_SIZE;// 接收缓冲区大小
	UART4_T.TxWrite = 0;									// 发送FIFO写索引
	UART4_T.TxRead = 0;										// 发送FIFO读索引
	UART4_T.RxWrite = 0;									// 接收FIFO写索引
	UART4_T.RxRead = 0;										// 接收FIFO读索引
	UART4_T.RxCount = 0;									// 接收到的新数据个数
	UART4_T.TxCount = 0;									// 待发送的数据个数
	UART4_T.Sending = 0;									// 正在发送中标志
	SetUartParam(UART4,  UART4_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);
#endif
#if UART5_FIFO_EN == 1
	UART5_T.uart = UART5;								// STM32 串口设备
	UART5_T.TxBuf = UART5_TxBuf;					// 发送缓冲区指针
	UART5_T.RxBuf = UART5_RxBuf;					// 接收缓冲区指针
	UART5_T.TxBufSize = UART5_TX_BUF_SIZE;// 发送缓冲区大小
	UART5_T.RxBufSize = UART5_RX_BUF_SIZE;// 接收缓冲区大小
	UART5_T.TxWrite = 0;									// 发送FIFO写索引
	UART5_T.TxRead = 0;										// 发送FIFO读索引
	UART5_T.RxWrite = 0;									// 接收FIFO写索引
	UART5_T.RxRead = 0;										// 接收FIFO读索引
	UART5_T.RxCount = 0;									// 接收到的新数据个数
	UART5_T.TxCount = 0;									// 待发送的数据个数
	UART5_T.Sending = 0;									// 正在发送中标志
	SetUartParam(UART5,  UART5_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);
#endif

}

//-----------------------------------------------------------------
// void HAL_UART_MspInit(UART_HandleTypeDef *huart)
//-----------------------------------------------------------------
//
// 函数功能: UART底层初始化，时钟使能，引脚配置，中断配置
// 入口参数: huart:串口句柄
// 返回参数: 无
// 注意事项: 此函数会被HAL_UART_Init()调用
//
//-----------------------------------------------------------------
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)// 如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();				 		// 使能USART1时钟
	
		GPIO_Initure.Pin=GPIO_PIN_9;				 			// PA9 -> USART1_TX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 		// 复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;				 		// 上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	// 高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;		// 复用为USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		// 初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;				 			// PA10 -> USART1_RX
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		// 初始化PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);			   	// 使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,0);  	// 抢占优先级3，子优先级0
		
		SET_BIT(USART1->ICR, USART_ICR_TCCF);			// 清除TC发送完成标志
		SET_BIT(USART1->RQR, USART_RQR_RXFRQ);  	// 清除RXNE接收标志
		SET_BIT(USART1->CR1, USART_CR1_RXNEIE);		// 使能PE. RX接受中断
	}
	else if(huart->Instance==USART3)// 如果是串口3，进行串口3 MSP初始化
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_USART3_CLK_ENABLE();				 		// 使能USART3时钟
	
		GPIO_Initure.Pin=GPIO_PIN_10;				 			// PB10 -> USART3_TX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 		// 复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;				 		// 上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	// 高速
		GPIO_Initure.Alternate=GPIO_AF7_USART3;		// 复用为USART3
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   		// 初始化PB10

		GPIO_Initure.Pin=GPIO_PIN_11;				 			// PB11 -> USART3_RX
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   		// 初始化PB11
		
		HAL_NVIC_EnableIRQ(USART3_IRQn);			   	// 使能USART3中断通道
		HAL_NVIC_SetPriority(USART3_IRQn,3,1);  	// 抢占优先级3，子优先级1
		
		SET_BIT(USART3->ICR, USART_ICR_TCCF);			// 清除TC发送完成标志
		SET_BIT(USART3->RQR, USART_RQR_RXFRQ);  	// 清除RXNE接收标志
		SET_BIT(USART3->CR1, USART_CR1_RXNEIE);		// 使能PE. RX接受中断
	}
	else if(huart->Instance==UART4)// 如果是串口4，进行串口4 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_UART4_CLK_ENABLE();				 		// 使能USART4时钟
	
		GPIO_Initure.Pin=GPIO_PIN_0;				 			// PA0 -> USART4_TX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 		// 复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;				 		// 上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	// 高速
		GPIO_Initure.Alternate=GPIO_AF8_UART4;		// 复用为USART4
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		// 初始化PA0

		GPIO_Initure.Pin=GPIO_PIN_1;				 			// PA1 -> USART4_RX
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		// 初始化PA1
		
		HAL_NVIC_EnableIRQ(UART4_IRQn);			   	// 使能USART4中断通道
		HAL_NVIC_SetPriority(UART4_IRQn,3,2);  	// 抢占优先级3，子优先级2
		
		SET_BIT(UART4->ICR, USART_ICR_TCCF);			// 清除TC发送完成标志
		SET_BIT(UART4->RQR, USART_RQR_RXFRQ);  	// 清除RXNE接收标志
		SET_BIT(UART4->CR1, USART_CR1_RXNEIE);		// 使能PE. RX接受中断
	}
		else if(huart->Instance==UART5)// 如果是串口5，进行串口5 MSP初始化
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_UART5_CLK_ENABLE();				 		// 使能USART5时钟
	
		GPIO_Initure.Pin=GPIO_PIN_12;				 			// PC12 -> USART5_TX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 		// 复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;				 		// 上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	// 高速
		GPIO_Initure.Alternate=GPIO_AF8_UART5;		// 复用为USART5
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);	   		// 初始化PC12

		GPIO_Initure.Pin=GPIO_PIN_2;				 			// PD2 -> USART5_RX
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   		// 初始化PD2
		
		HAL_NVIC_EnableIRQ(UART5_IRQn);			   	// 使能USART5中断通道
		HAL_NVIC_SetPriority(UART5_IRQn,3,3);  	// 抢占优先级3，子优先级3
		
		SET_BIT(UART5->ICR, USART_ICR_TCCF);			// 清除TC发送完成标志
		SET_BIT(UART5->RQR, USART_RQR_RXFRQ);  	// 清除RXNE接收标志
		SET_BIT(UART5->CR1, USART_CR1_RXNEIE);		// 使能PE. RX接受中断
	}
}

//-----------------------------------------------------------------
// UART_T *ComToUart(COM_PORT_E Port)
//-----------------------------------------------------------------
//
// 函数功能: 将COM端口号转换为UART指针
// 入口参数: COM_PORT_E Port：端口号（COM1、COM3、COM4、COM5、COM6）
// 返回参数: UART指针
// 注意事项: 无
//
//-----------------------------------------------------------------
UART_T *ComToUart(COM_PORT_E Port)
{
	if (Port == COM1)
	{
		#if UART1_FIFO_EN == 1
			return &UART1_T;
		#else
			return 0;
		#endif
	}
	else if (Port == COM3)
	{
		#if UART3_FIFO_EN == 1
			return &UART3_T;
		#else
			return 0;
		#endif
	}
	else if (Port == COM4)
	{
		#if UART4_FIFO_EN == 1
			return &UART4_T;
		#else
			return 0;
		#endif
	}
	else if (Port == COM5)
	{
		#if UART4_FIFO_EN == 1
			return &UART5_T;
		#else
			return 0;
		#endif
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------
// USART_TypeDef *ComToUSARTx(COM_PORT_E Port)
//-----------------------------------------------------------------
//
// 函数功能: 将COM端口号转换为 USART_TypeDef* USARTx
// 入口参数: COM_PORT_E Port：端口号（COM1、COM3、COM4、COM5、COM6）
// 返回参数: USART_TypeDef*,  USART1、USART3、UART4、UART5、USART6
// 注意事项: 无
//
//-----------------------------------------------------------------
USART_TypeDef *ComToUSARTx(COM_PORT_E Port)
{
	if (Port == COM1)
	{
		#if UART1_FIFO_EN == 1
			return USART1;
		#else
			return 0;
		#endif
	}
	else if (Port == COM3)
	{
		#if UART3_FIFO_EN == 1
			return USART3;
		#else
			return 0;
		#endif
	}
	else if (Port == COM4)
	{
		#if UART4_FIFO_EN == 1
			return UART4;
		#else
			return 0;
		#endif
	}
	else if (Port == COM5)
	{
		#if UART5_FIFO_EN == 1
			return UART5;
		#else
			return 0;
		#endif
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------
// void comSetBaud(COM_PORT_E Port, uint32_t BaudRate)
//-----------------------------------------------------------------
//
// 函数功能: 设置串口的波特率
// 入口参数: COM_PORT_E _ucPort：端口号（COM1、COM3、COM4、COM5、COM6）
//					 uint32_t _BaudRate：设置的波特率
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void comSetBaud(COM_PORT_E Port, uint32_t BaudRate)
{
	USART_TypeDef* USARTx;
	
	USARTx = ComToUSARTx(Port);
	if (USARTx == 0)
	{
		return;
	}
	SetUartParam(USARTx,  BaudRate, UART_PARITY_NONE, UART_MODE_TX_RX);
}

//-----------------------------------------------------------------
// void SetUartParam(USART_TypeDef *Instance,  uint32_t BaudRate, uint32_t Parity, uint32_t Mode))
//-----------------------------------------------------------------
//
// 函数功能: 配置串口的硬件参数（波特率，数据位，停止位，起始位，校验位，中断使能）
// 入口参数: USART_TypeDef *Instance；USART_TypeDef类型结构体
//					 uint32_t _BaudRate：设置的波特率
//					 uint32_t Parity：校验类型，奇校验或者偶校验
//					 uint32_t Mode；发送和接收模式使能
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void SetUartParam(USART_TypeDef *Instance,  uint32_t BaudRate, uint32_t Parity, uint32_t Mode)
{

	if(Instance == USART1)
	{
		USART1_Handler.Instance=Instance;					    				// USART1
		USART1_Handler.Init.BaudRate=BaudRate;				    		// 波特率
		USART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;		// 字长为8位数据格式
		USART1_Handler.Init.StopBits=UART_STOPBITS_1;	    		// 一个停止位
		USART1_Handler.Init.Parity=Parity;		  							// 无奇偶校验位
		USART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;		// 无硬件流控
		USART1_Handler.Init.Mode=Mode;		    								// 收发模式
		HAL_UART_Init(&USART1_Handler);					    					// HAL_UART_Init()会使能UART1
	}
	else if(Instance == USART3)
	{
		USART3_Handler.Instance=Instance;					    				// USART3
		USART3_Handler.Init.BaudRate=BaudRate;				    		// 波特率
		USART3_Handler.Init.WordLength=UART_WORDLENGTH_8B;		// 字长为8位数据格式
		USART3_Handler.Init.StopBits=UART_STOPBITS_1;	    		// 一个停止位
		USART3_Handler.Init.Parity=Parity;		  							// 无奇偶校验位
		USART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;		// 无硬件流控
		USART3_Handler.Init.Mode=Mode;		    								// 收发模式
		HAL_UART_Init(&USART3_Handler);					    					// HAL_UART_Init()会使能UART3
	}
	else if(Instance == UART4)
	{
		UART4_Handler.Instance=Instance;					    				// UART4
		UART4_Handler.Init.BaudRate=BaudRate;				    		// 波特率
		UART4_Handler.Init.WordLength=UART_WORDLENGTH_8B;		// 字长为8位数据格式
		UART4_Handler.Init.StopBits=UART_STOPBITS_1;	    		// 一个停止位
		UART4_Handler.Init.Parity=Parity;		  							// 无奇偶校验位
		UART4_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;		// 无硬件流控
		UART4_Handler.Init.Mode=Mode;		    								// 收发模式
		HAL_UART_Init(&UART4_Handler);					    					// HAL_UART_Init()会使能UART3
	}
	else if(Instance == UART5)
	{
		UART5_Handler.Instance=Instance;					    				// UART5
		UART5_Handler.Init.BaudRate=BaudRate;				    		// 波特率
		UART5_Handler.Init.WordLength=UART_WORDLENGTH_8B;		// 字长为8位数据格式
		UART5_Handler.Init.StopBits=UART_STOPBITS_1;	    		// 一个停止位
		UART5_Handler.Init.Parity=Parity;		  							// 无奇偶校验位
		UART5_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;		// 无硬件流控
		UART5_Handler.Init.Mode=Mode;		    								// 收发模式
		HAL_UART_Init(&UART5_Handler);					    					// HAL_UART_Init()会使能UART3
	}
}

//-----------------------------------------------------------------
// void comSendBuf(COM_PORT_E Port, uint8_t *TxBuf, uint16_t Len)
//-----------------------------------------------------------------
//
// 函数功能: 向串口发送一组数据。数据放到发送缓冲区后立即返回，由中断服务程序在后台完成发送
// 入口参数: COM_PORT_E Port：端口号（COM1、COM3、COM4、COM5、COM6）
//					 uint8_t *TxBuf：待发送的数据缓冲区
//					 uint16_t Len：数据长度
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void comSendBuf(COM_PORT_E Port, uint8_t *TxBuf, uint16_t Len)
{
	UART_T *pUart;

	pUart = ComToUart(Port);
	if (pUart == 0)
	{
		return;
	}

	UartSend(pUart, TxBuf, Len);
}

//-----------------------------------------------------------------
// void comSendChar(COM_PORT_E Port, uint8_t Byte)
//-----------------------------------------------------------------
//
// 函数功能: 向串口发送1个字节。数据放到发送缓冲区后立即返回，由中断服务程序在后台完成发送
// 入口参数: COM_PORT_E Port：端口号（COM1、COM3、COM4、COM5、COM6）
//					 uint8_t Byte：待发送的数据
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void comSendChar(COM_PORT_E Port, uint8_t Byte)
{
	comSendBuf(Port, &Byte, 1);
}

//-----------------------------------------------------------------
// uint8_t comGetChar(COM_PORT_E Port, uint8_t *Byte)
//-----------------------------------------------------------------
//
// 函数功能: 从接收缓冲区读取1字节，非阻塞。无论有无数据均立即返回。
// 入口参数: COM_PORT_E Port：端口号（COM1、COM3、COM4、COM5、COM6）
//					 uint8_t Byte：待接收的数据
// 返回参数: 0 表示无数据, 1 表示读取到有效字节
// 注意事项: 无
//
//-----------------------------------------------------------------
uint8_t comGetChar(COM_PORT_E Port, uint8_t *Byte)
{
	UART_T *pUart;

	pUart = ComToUart(Port);
	if (pUart == 0)
	{
		return 0;
	}

	return UartGetChar(pUart, Byte);
}

//-----------------------------------------------------------------
// void comClearTxFifo(COM_PORT_E Port)
//-----------------------------------------------------------------
//
// 函数功能: 清零串口发送缓冲区
// 入口参数: COM_PORT_E Port：端口号（COM1、COM3、COM4、COM5、COM6）
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void comClearTxFifo(COM_PORT_E Port)
{
	UART_T *pUart;

	pUart = ComToUart(Port);
	if (pUart == 0)
	{
		return;
	}

	pUart->TxWrite = 0;
	pUart->TxRead = 0;
	pUart->TxCount = 0;
}

//-----------------------------------------------------------------
// void comClearRxFifo(COM_PORT_E Port)
//-----------------------------------------------------------------
//
// 函数功能: 清零串口接收缓冲区
// 入口参数: COM_PORT_E Port：端口号（COM1、COM3、COM4、COM5、COM6）
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void comClearRxFifo(COM_PORT_E Port)
{
	UART_T *pUart;

	pUart = ComToUart(Port);
	if (pUart == 0)
	{
		return;
	}

	pUart->RxWrite = 0;
	pUart->RxRead = 0;
	pUart->RxCount = 0;
}

//-----------------------------------------------------------------
// static void UartSend(UART_T *pUart, uint8_t *Buf, uint16_t Len)
//-----------------------------------------------------------------
//
// 函数功能: 填写数据到UART发送缓冲区,并启动发送中断。中断处理函数发送完毕后，自动关闭发送中断
// 入口参数: UartSend(UART_T *pUart：串口设备
//					 uint8_t *Buf：待发送的数据
//					 uint16_t Len：数据长度
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
static void UartSend(UART_T *pUart, uint8_t *Buf, uint16_t Len)
{
	uint16_t i;

	for (i = 0; i < Len; i++)
	{
		// 如果发送缓冲区已经满了，则等待缓冲区空
		while (1)
		{
			__IO uint16_t usCount;

			DISABLE_INT();
			usCount = pUart->TxCount;
			ENABLE_INT();

			if (usCount < pUart->TxBufSize)
			{
				break;
			}
			else if(usCount == pUart->TxBufSize)// 数据已填满缓冲区
			{
				if((pUart->uart->CR1 & USART_CR1_TXEIE) == 0)
				{
					SET_BIT(pUart->uart->CR1, USART_CR1_TXEIE);
				}  
			}
		}

		// 将新数据填入发送缓冲区
		pUart->TxBuf[pUart->TxWrite] = Buf[i];

		DISABLE_INT();
		if (++pUart->TxWrite >= pUart->TxBufSize)
		{
			pUart->TxWrite = 0;
		}
		pUart->TxCount++;
		ENABLE_INT();
	}

	SET_BIT(pUart->uart->CR1, USART_CR1_TXEIE);	// 使能发送中断（缓冲区空）
}

//-----------------------------------------------------------------
// static uint8_t UartGetChar(UART_T *pUart, uint8_t *Byte)
//-----------------------------------------------------------------
//
// 函数功能: 从串口接收缓冲区读取1字节数据 （用于主程序调用）
// 入口参数: UartSend(UART_T *pUart：串口设备
//					 uint8_t *Buf：读取的数据
// 返回参数: 0 表示无数据  1表示读取到数据
// 注意事项: 无
//
//-----------------------------------------------------------------
static uint8_t UartGetChar(UART_T *pUart, uint8_t *Byte)
{
	uint16_t usCount;

	// RxWrite 变量在中断函数中被改写，主程序读取该变量时，必须进行临界区保护
	DISABLE_INT();
	usCount = pUart->RxCount;
	ENABLE_INT();

	if (usCount == 0)	// 已经没有数据
	{
		return 0;
	}
	else
	{
		*Byte = pUart->RxBuf[pUart->RxRead];	// 从串口接收FIFO取1个数据

		// 改写FIFO读索引
		DISABLE_INT();
		if (++pUart->RxRead >= pUart->RxBufSize)
		{
			pUart->RxRead = 0;
		}
		pUart->RxCount--;
		ENABLE_INT();
		return 1;
	}
}

//-----------------------------------------------------------------
// uint8_t UartTxEmpty(COM_PORT_E Port)
//-----------------------------------------------------------------
//
// 函数功能: 判断发送缓冲区是否为空。
// 入口参数: COM_PORT_E Port：端口号（COM1、COM3、COM4、COM5、COM6）
// 返回参数: 1为空。0为不空。
// 注意事项: 无
//
//-----------------------------------------------------------------
uint8_t UartTxEmpty(COM_PORT_E Port)
{
   UART_T *pUart;
   uint8_t Sending;
   
   pUart = ComToUart(Port);
   if (pUart == 0)
   {
      return 0;
   }

   Sending = pUart->Sending;

   if (Sending != 0)
   {
      return 0;
   }
   return 1;
}

//-----------------------------------------------------------------
// static void UartIRQ(UART_T *pUart)
//-----------------------------------------------------------------
//
// 函数功能: 供中断服务程序调用，通用串口中断处理函数
// 入口参数: UART_T *pUart：串口设备
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
static void UartIRQ(UART_T *pUart)
{
	uint8_t RX_DATA;
	uint32_t isrflags   = READ_REG(pUart->uart->ISR);	// 读取中断和状态
	uint32_t cr1its     = READ_REG(pUart->uart->CR1);	// 控制1
	uint32_t cr3its     = READ_REG(pUart->uart->CR3);	// 控制3
	
	// 处理接收中断
	if ((isrflags & USART_ISR_RXNE) != RESET)				// 读取的数据寄存器不为空
	{
		RX_DATA = READ_REG(pUart->uart->RDR);					// 从接收数据寄存器获取接收数据
		pUart->RxBuf[pUart->RxWrite] = RX_DATA;		// 将数据写入FIFO
		if (++pUart->RxWrite >= pUart->RxBufSize)
		{
			pUart->RxWrite = 0;
		}
		if (pUart->RxCount < pUart->RxBufSize)
		{
			pUart->RxCount++;
		}
	}

	// 处理发送缓冲区空中断
	if ( ((isrflags & USART_ISR_TXE) != RESET) && (cr1its & USART_CR1_TXEIE) != RESET)
	{
		if (pUart->TxCount == 0)
		{
			// 发送缓冲区的数据已取完时， 禁止发送缓冲区空中断 （注意：此时最后1个数据还未真正发送完毕）
			CLEAR_BIT(pUart->uart->CR1, USART_CR1_TXEIE);

			// 使能数据发送完毕中断
			SET_BIT(pUart->uart->CR1, USART_CR1_TCIE);
		}
		else
		{
			pUart->Sending = 1;
			
			// 从发送FIFO取1个字节写入串口发送数据寄存器
			pUart->uart->TDR = pUart->TxBuf[pUart->TxRead];
			if (++pUart->TxRead >= pUart->TxBufSize)
			{
				pUart->TxRead = 0;
			}
			pUart->TxCount--;
		}

	}
	// 数据bit位全部发送完毕的中断
	if (((isrflags & USART_ISR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
	{
		if (pUart->TxCount == 0)
		{
			// 如果发送FIFO的数据全部发送完毕，禁止数据发送完毕中断
			CLEAR_BIT(pUart->uart->CR1, USART_CR1_TCIE);
			pUart->Sending = 0;
		}
		else
		{
			// 正常情况下，不会进入此分支

			// 如果发送FIFO的数据还未完毕，则从发送FIFO取1个数据写入发送数据寄存器
			pUart->uart->TDR = pUart->TxBuf[pUart->TxRead];
			if (++pUart->TxRead >= pUart->TxBufSize)
			{
				pUart->TxRead = 0;
			}
			pUart->TxCount--;
		}
	}
	
	// 清除中断标志
	SET_BIT(pUart->uart->ICR, UART_CLEAR_PEF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_FEF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_NEF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_OREF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_IDLEF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_TCF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_LBDF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_CTSF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_CMF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_WUF);
	SET_BIT(pUart->uart->ICR, UART_CLEAR_TXFECF);
}

//-----------------------------------------------------------------
// static void USART1_IRQHandler(void)
//-----------------------------------------------------------------
//
// 函数功能: USART1_IRQHandler  USART2_IRQHandler USART3_IRQHandler UART4_IRQHandler UART5_IRQHandler等
// 入口参数: 无
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
#if UART1_FIFO_EN == 1
void USART1_IRQHandler(void)
{
	UartIRQ(&UART1_T);
}
#endif

#if UART3_FIFO_EN == 1
void USART3_IRQHandler(void)
{
	UartIRQ(&UART3_T);
}
#endif

#if UART4_FIFO_EN == 1
void UART4_IRQHandler(void)
{
	UartIRQ(&UART4_T);
}
#endif

#if UART5_FIFO_EN == 1
void UART5_IRQHandler(void)
{
	UartIRQ(&UART5_T);
}
#endif

#if UART6_FIFO_EN == 1
void USART6_IRQHandler(void)
{
	UartIRQ(&UART6_T);
}
#endif


//-----------------------------------------------------------------
// int fputc(int ch, FILE *f)
//-----------------------------------------------------------------
//
// 函数功能: 重定义putc函数，这样可以使用printf函数从串口1打印输出
// 入口参数: 无
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
int fputc(int ch, FILE *f)
{
#if 0	// 将需要printf的字符通过串口中断FIFO发送出去，printf函数会立即返回
	comSendChar(COM1, ch);
	
	return ch;
#else	// 采用阻塞方式发送每个字符,等待数据发送完毕
	// 写一个字节到USART1
	USART1->TDR = ch;
	
	// 等待发送结束
	while((USART1->ISR & USART_ISR_TC) == 0)
	{}
	
	return ch;
#endif
}

//-----------------------------------------------------------------
// int fgetc(FILE *f)
//-----------------------------------------------------------------
//
// 函数功能: 重定义getc函数，这样可以使用getchar函数从串口1输入数据
// 入口参数: 无
// 返回参数: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
int fgetc(FILE *f)
{

#if 1	// 从串口接收FIFO中取1个数据, 只有取到数据才返回
	uint8_t ucData;

	while(comGetChar(COM1, &ucData) == 0);

	return ucData;
#else
	// 等待接收到数据
	while((USART1->ISR & USART_ISR_RXNE) == 0)
	{}

	return (int)USART1->RDR;
#endif
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
