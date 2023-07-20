

//-----------------------------------------------------------------
// ͷ�ļ�����
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
// ��������: ���ڳ�ʼ��
// ��ڲ���: ��
// ���ز���: ��
// ע������: ��
//
//-----------------------------------------------------------------
void uart_init(void)
{	
#if UART1_FIFO_EN == 1
	UART1_T.uart = USART1;								// STM32 �����豸
	UART1_T.TxBuf = UART1_TxBuf;					// ���ͻ�����ָ��
	UART1_T.RxBuf = UART1_RxBuf;					// ���ջ�����ָ��
	UART1_T.TxBufSize = UART1_TX_BUF_SIZE;// ���ͻ�������С
	UART1_T.RxBufSize = UART1_RX_BUF_SIZE;// ���ջ�������С
	UART1_T.TxWrite = 0;									// ����FIFOд����
	UART1_T.TxRead = 0;										// ����FIFO������
	UART1_T.RxWrite = 0;									// ����FIFOд����
	UART1_T.RxRead = 0;										// ����FIFO������
	UART1_T.RxCount = 0;									// ���յ��������ݸ���
	UART1_T.TxCount = 0;									// �����͵����ݸ���
	UART1_T.Sending = 0;									// ���ڷ����б�־
	
	SetUartParam(USART1,  UART1_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);

#endif

#if UART3_FIFO_EN == 1
	UART3_T.uart = USART3;								// STM32 �����豸
	UART3_T.TxBuf = UART3_TxBuf;					// ���ͻ�����ָ��
	UART3_T.RxBuf = UART3_RxBuf;					// ���ջ�����ָ��
	UART3_T.TxBufSize = UART3_TX_BUF_SIZE;// ���ͻ�������С
	UART3_T.RxBufSize = UART3_RX_BUF_SIZE;// ���ջ�������С
	UART3_T.TxWrite = 0;									// ����FIFOд����
	UART3_T.TxRead = 0;										// ����FIFO������
	UART3_T.RxWrite = 0;									// ����FIFOд����
	UART3_T.RxRead = 0;										// ����FIFO������
	UART3_T.RxCount = 0;									// ���յ��������ݸ���
	UART3_T.TxCount = 0;									// �����͵����ݸ���
	UART3_T.Sending = 0;									// ���ڷ����б�־
	SetUartParam(USART3,  UART3_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);
#endif
#if UART4_FIFO_EN == 1
	UART4_T.uart = UART4;								// STM32 �����豸
	UART4_T.TxBuf = UART4_TxBuf;					// ���ͻ�����ָ��
	UART4_T.RxBuf = UART4_RxBuf;					// ���ջ�����ָ��
	UART4_T.TxBufSize = UART4_TX_BUF_SIZE;// ���ͻ�������С
	UART4_T.RxBufSize = UART4_RX_BUF_SIZE;// ���ջ�������С
	UART4_T.TxWrite = 0;									// ����FIFOд����
	UART4_T.TxRead = 0;										// ����FIFO������
	UART4_T.RxWrite = 0;									// ����FIFOд����
	UART4_T.RxRead = 0;										// ����FIFO������
	UART4_T.RxCount = 0;									// ���յ��������ݸ���
	UART4_T.TxCount = 0;									// �����͵����ݸ���
	UART4_T.Sending = 0;									// ���ڷ����б�־
	SetUartParam(UART4,  UART4_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);
#endif
#if UART5_FIFO_EN == 1
	UART5_T.uart = UART5;								// STM32 �����豸
	UART5_T.TxBuf = UART5_TxBuf;					// ���ͻ�����ָ��
	UART5_T.RxBuf = UART5_RxBuf;					// ���ջ�����ָ��
	UART5_T.TxBufSize = UART5_TX_BUF_SIZE;// ���ͻ�������С
	UART5_T.RxBufSize = UART5_RX_BUF_SIZE;// ���ջ�������С
	UART5_T.TxWrite = 0;									// ����FIFOд����
	UART5_T.TxRead = 0;										// ����FIFO������
	UART5_T.RxWrite = 0;									// ����FIFOд����
	UART5_T.RxRead = 0;										// ����FIFO������
	UART5_T.RxCount = 0;									// ���յ��������ݸ���
	UART5_T.TxCount = 0;									// �����͵����ݸ���
	UART5_T.Sending = 0;									// ���ڷ����б�־
	SetUartParam(UART5,  UART5_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);
#endif

}

//-----------------------------------------------------------------
// void HAL_UART_MspInit(UART_HandleTypeDef *huart)
//-----------------------------------------------------------------
//
// ��������: UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
// ��ڲ���: huart:���ھ��
// ���ز���: ��
// ע������: �˺����ᱻHAL_UART_Init()����
//
//-----------------------------------------------------------------
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)// ����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();				 		// ʹ��USART1ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_9;				 			// PA9 -> USART1_TX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 		// �����������
		GPIO_Initure.Pull=GPIO_PULLUP;				 		// ����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	// ����
		GPIO_Initure.Alternate=GPIO_AF7_USART1;		// ����ΪUSART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		// ��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_10;				 			// PA10 -> USART1_RX
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		// ��ʼ��PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);			   	// ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART1_IRQn,3,0);  	// ��ռ���ȼ�3�������ȼ�0
		
		SET_BIT(USART1->ICR, USART_ICR_TCCF);			// ���TC������ɱ�־
		SET_BIT(USART1->RQR, USART_RQR_RXFRQ);  	// ���RXNE���ձ�־
		SET_BIT(USART1->CR1, USART_CR1_RXNEIE);		// ʹ��PE. RX�����ж�
	}
	else if(huart->Instance==USART3)// ����Ǵ���3�����д���3 MSP��ʼ��
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_USART3_CLK_ENABLE();				 		// ʹ��USART3ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_10;				 			// PB10 -> USART3_TX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 		// �����������
		GPIO_Initure.Pull=GPIO_PULLUP;				 		// ����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	// ����
		GPIO_Initure.Alternate=GPIO_AF7_USART3;		// ����ΪUSART3
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   		// ��ʼ��PB10

		GPIO_Initure.Pin=GPIO_PIN_11;				 			// PB11 -> USART3_RX
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   		// ��ʼ��PB11
		
		HAL_NVIC_EnableIRQ(USART3_IRQn);			   	// ʹ��USART3�ж�ͨ��
		HAL_NVIC_SetPriority(USART3_IRQn,3,1);  	// ��ռ���ȼ�3�������ȼ�1
		
		SET_BIT(USART3->ICR, USART_ICR_TCCF);			// ���TC������ɱ�־
		SET_BIT(USART3->RQR, USART_RQR_RXFRQ);  	// ���RXNE���ձ�־
		SET_BIT(USART3->CR1, USART_CR1_RXNEIE);		// ʹ��PE. RX�����ж�
	}
	else if(huart->Instance==UART4)// ����Ǵ���4�����д���4 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_UART4_CLK_ENABLE();				 		// ʹ��USART4ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_0;				 			// PA0 -> USART4_TX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 		// �����������
		GPIO_Initure.Pull=GPIO_PULLUP;				 		// ����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	// ����
		GPIO_Initure.Alternate=GPIO_AF8_UART4;		// ����ΪUSART4
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		// ��ʼ��PA0

		GPIO_Initure.Pin=GPIO_PIN_1;				 			// PA1 -> USART4_RX
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		// ��ʼ��PA1
		
		HAL_NVIC_EnableIRQ(UART4_IRQn);			   	// ʹ��USART4�ж�ͨ��
		HAL_NVIC_SetPriority(UART4_IRQn,3,2);  	// ��ռ���ȼ�3�������ȼ�2
		
		SET_BIT(UART4->ICR, USART_ICR_TCCF);			// ���TC������ɱ�־
		SET_BIT(UART4->RQR, USART_RQR_RXFRQ);  	// ���RXNE���ձ�־
		SET_BIT(UART4->CR1, USART_CR1_RXNEIE);		// ʹ��PE. RX�����ж�
	}
		else if(huart->Instance==UART5)// ����Ǵ���5�����д���5 MSP��ʼ��
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_UART5_CLK_ENABLE();				 		// ʹ��USART5ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_12;				 			// PC12 -> USART5_TX
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 		// �����������
		GPIO_Initure.Pull=GPIO_PULLUP;				 		// ����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	// ����
		GPIO_Initure.Alternate=GPIO_AF8_UART5;		// ����ΪUSART5
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);	   		// ��ʼ��PC12

		GPIO_Initure.Pin=GPIO_PIN_2;				 			// PD2 -> USART5_RX
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   		// ��ʼ��PD2
		
		HAL_NVIC_EnableIRQ(UART5_IRQn);			   	// ʹ��USART5�ж�ͨ��
		HAL_NVIC_SetPriority(UART5_IRQn,3,3);  	// ��ռ���ȼ�3�������ȼ�3
		
		SET_BIT(UART5->ICR, USART_ICR_TCCF);			// ���TC������ɱ�־
		SET_BIT(UART5->RQR, USART_RQR_RXFRQ);  	// ���RXNE���ձ�־
		SET_BIT(UART5->CR1, USART_CR1_RXNEIE);		// ʹ��PE. RX�����ж�
	}
}

//-----------------------------------------------------------------
// UART_T *ComToUart(COM_PORT_E Port)
//-----------------------------------------------------------------
//
// ��������: ��COM�˿ں�ת��ΪUARTָ��
// ��ڲ���: COM_PORT_E Port���˿ںţ�COM1��COM3��COM4��COM5��COM6��
// ���ز���: UARTָ��
// ע������: ��
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
// ��������: ��COM�˿ں�ת��Ϊ USART_TypeDef* USARTx
// ��ڲ���: COM_PORT_E Port���˿ںţ�COM1��COM3��COM4��COM5��COM6��
// ���ز���: USART_TypeDef*,  USART1��USART3��UART4��UART5��USART6
// ע������: ��
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
// ��������: ���ô��ڵĲ�����
// ��ڲ���: COM_PORT_E _ucPort���˿ںţ�COM1��COM3��COM4��COM5��COM6��
//					 uint32_t _BaudRate�����õĲ�����
// ���ز���: ��
// ע������: ��
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
// ��������: ���ô��ڵ�Ӳ�������������ʣ�����λ��ֹͣλ����ʼλ��У��λ���ж�ʹ�ܣ�
// ��ڲ���: USART_TypeDef *Instance��USART_TypeDef���ͽṹ��
//					 uint32_t _BaudRate�����õĲ�����
//					 uint32_t Parity��У�����ͣ���У�����żУ��
//					 uint32_t Mode�����ͺͽ���ģʽʹ��
// ���ز���: ��
// ע������: ��
//
//-----------------------------------------------------------------
void SetUartParam(USART_TypeDef *Instance,  uint32_t BaudRate, uint32_t Parity, uint32_t Mode)
{

	if(Instance == USART1)
	{
		USART1_Handler.Instance=Instance;					    				// USART1
		USART1_Handler.Init.BaudRate=BaudRate;				    		// ������
		USART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;		// �ֳ�Ϊ8λ���ݸ�ʽ
		USART1_Handler.Init.StopBits=UART_STOPBITS_1;	    		// һ��ֹͣλ
		USART1_Handler.Init.Parity=Parity;		  							// ����żУ��λ
		USART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;		// ��Ӳ������
		USART1_Handler.Init.Mode=Mode;		    								// �շ�ģʽ
		HAL_UART_Init(&USART1_Handler);					    					// HAL_UART_Init()��ʹ��UART1
	}
	else if(Instance == USART3)
	{
		USART3_Handler.Instance=Instance;					    				// USART3
		USART3_Handler.Init.BaudRate=BaudRate;				    		// ������
		USART3_Handler.Init.WordLength=UART_WORDLENGTH_8B;		// �ֳ�Ϊ8λ���ݸ�ʽ
		USART3_Handler.Init.StopBits=UART_STOPBITS_1;	    		// һ��ֹͣλ
		USART3_Handler.Init.Parity=Parity;		  							// ����żУ��λ
		USART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;		// ��Ӳ������
		USART3_Handler.Init.Mode=Mode;		    								// �շ�ģʽ
		HAL_UART_Init(&USART3_Handler);					    					// HAL_UART_Init()��ʹ��UART3
	}
	else if(Instance == UART4)
	{
		UART4_Handler.Instance=Instance;					    				// UART4
		UART4_Handler.Init.BaudRate=BaudRate;				    		// ������
		UART4_Handler.Init.WordLength=UART_WORDLENGTH_8B;		// �ֳ�Ϊ8λ���ݸ�ʽ
		UART4_Handler.Init.StopBits=UART_STOPBITS_1;	    		// һ��ֹͣλ
		UART4_Handler.Init.Parity=Parity;		  							// ����żУ��λ
		UART4_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;		// ��Ӳ������
		UART4_Handler.Init.Mode=Mode;		    								// �շ�ģʽ
		HAL_UART_Init(&UART4_Handler);					    					// HAL_UART_Init()��ʹ��UART3
	}
	else if(Instance == UART5)
	{
		UART5_Handler.Instance=Instance;					    				// UART5
		UART5_Handler.Init.BaudRate=BaudRate;				    		// ������
		UART5_Handler.Init.WordLength=UART_WORDLENGTH_8B;		// �ֳ�Ϊ8λ���ݸ�ʽ
		UART5_Handler.Init.StopBits=UART_STOPBITS_1;	    		// һ��ֹͣλ
		UART5_Handler.Init.Parity=Parity;		  							// ����żУ��λ
		UART5_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;		// ��Ӳ������
		UART5_Handler.Init.Mode=Mode;		    								// �շ�ģʽ
		HAL_UART_Init(&UART5_Handler);					    					// HAL_UART_Init()��ʹ��UART3
	}
}

//-----------------------------------------------------------------
// void comSendBuf(COM_PORT_E Port, uint8_t *TxBuf, uint16_t Len)
//-----------------------------------------------------------------
//
// ��������: �򴮿ڷ���һ�����ݡ����ݷŵ����ͻ��������������أ����жϷ�������ں�̨��ɷ���
// ��ڲ���: COM_PORT_E Port���˿ںţ�COM1��COM3��COM4��COM5��COM6��
//					 uint8_t *TxBuf�������͵����ݻ�����
//					 uint16_t Len�����ݳ���
// ���ز���: ��
// ע������: ��
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
// ��������: �򴮿ڷ���1���ֽڡ����ݷŵ����ͻ��������������أ����жϷ�������ں�̨��ɷ���
// ��ڲ���: COM_PORT_E Port���˿ںţ�COM1��COM3��COM4��COM5��COM6��
//					 uint8_t Byte�������͵�����
// ���ز���: ��
// ע������: ��
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
// ��������: �ӽ��ջ�������ȡ1�ֽڣ��������������������ݾ��������ء�
// ��ڲ���: COM_PORT_E Port���˿ںţ�COM1��COM3��COM4��COM5��COM6��
//					 uint8_t Byte�������յ�����
// ���ز���: 0 ��ʾ������, 1 ��ʾ��ȡ����Ч�ֽ�
// ע������: ��
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
// ��������: ���㴮�ڷ��ͻ�����
// ��ڲ���: COM_PORT_E Port���˿ںţ�COM1��COM3��COM4��COM5��COM6��
// ���ز���: ��
// ע������: ��
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
// ��������: ���㴮�ڽ��ջ�����
// ��ڲ���: COM_PORT_E Port���˿ںţ�COM1��COM3��COM4��COM5��COM6��
// ���ز���: ��
// ע������: ��
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
// ��������: ��д���ݵ�UART���ͻ�����,�����������жϡ��жϴ�����������Ϻ��Զ��رշ����ж�
// ��ڲ���: UartSend(UART_T *pUart�������豸
//					 uint8_t *Buf�������͵�����
//					 uint16_t Len�����ݳ���
// ���ز���: ��
// ע������: ��
//
//-----------------------------------------------------------------
static void UartSend(UART_T *pUart, uint8_t *Buf, uint16_t Len)
{
	uint16_t i;

	for (i = 0; i < Len; i++)
	{
		// ������ͻ������Ѿ����ˣ���ȴ���������
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
			else if(usCount == pUart->TxBufSize)// ����������������
			{
				if((pUart->uart->CR1 & USART_CR1_TXEIE) == 0)
				{
					SET_BIT(pUart->uart->CR1, USART_CR1_TXEIE);
				}  
			}
		}

		// �����������뷢�ͻ�����
		pUart->TxBuf[pUart->TxWrite] = Buf[i];

		DISABLE_INT();
		if (++pUart->TxWrite >= pUart->TxBufSize)
		{
			pUart->TxWrite = 0;
		}
		pUart->TxCount++;
		ENABLE_INT();
	}

	SET_BIT(pUart->uart->CR1, USART_CR1_TXEIE);	// ʹ�ܷ����жϣ��������գ�
}

//-----------------------------------------------------------------
// static uint8_t UartGetChar(UART_T *pUart, uint8_t *Byte)
//-----------------------------------------------------------------
//
// ��������: �Ӵ��ڽ��ջ�������ȡ1�ֽ����� ��������������ã�
// ��ڲ���: UartSend(UART_T *pUart�������豸
//					 uint8_t *Buf����ȡ������
// ���ز���: 0 ��ʾ������  1��ʾ��ȡ������
// ע������: ��
//
//-----------------------------------------------------------------
static uint8_t UartGetChar(UART_T *pUart, uint8_t *Byte)
{
	uint16_t usCount;

	// RxWrite �������жϺ����б���д���������ȡ�ñ���ʱ����������ٽ�������
	DISABLE_INT();
	usCount = pUart->RxCount;
	ENABLE_INT();

	if (usCount == 0)	// �Ѿ�û������
	{
		return 0;
	}
	else
	{
		*Byte = pUart->RxBuf[pUart->RxRead];	// �Ӵ��ڽ���FIFOȡ1������

		// ��дFIFO������
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
// ��������: �жϷ��ͻ������Ƿ�Ϊ�ա�
// ��ڲ���: COM_PORT_E Port���˿ںţ�COM1��COM3��COM4��COM5��COM6��
// ���ز���: 1Ϊ�ա�0Ϊ���ա�
// ע������: ��
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
// ��������: ���жϷ��������ã�ͨ�ô����жϴ�����
// ��ڲ���: UART_T *pUart�������豸
// ���ز���: ��
// ע������: ��
//
//-----------------------------------------------------------------
static void UartIRQ(UART_T *pUart)
{
	uint8_t RX_DATA;
	uint32_t isrflags   = READ_REG(pUart->uart->ISR);	// ��ȡ�жϺ�״̬
	uint32_t cr1its     = READ_REG(pUart->uart->CR1);	// ����1
	uint32_t cr3its     = READ_REG(pUart->uart->CR3);	// ����3
	
	// ��������ж�
	if ((isrflags & USART_ISR_RXNE) != RESET)				// ��ȡ�����ݼĴ�����Ϊ��
	{
		RX_DATA = READ_REG(pUart->uart->RDR);					// �ӽ������ݼĴ�����ȡ��������
		pUart->RxBuf[pUart->RxWrite] = RX_DATA;		// ������д��FIFO
		if (++pUart->RxWrite >= pUart->RxBufSize)
		{
			pUart->RxWrite = 0;
		}
		if (pUart->RxCount < pUart->RxBufSize)
		{
			pUart->RxCount++;
		}
	}

	// �����ͻ��������ж�
	if ( ((isrflags & USART_ISR_TXE) != RESET) && (cr1its & USART_CR1_TXEIE) != RESET)
	{
		if (pUart->TxCount == 0)
		{
			// ���ͻ�������������ȡ��ʱ�� ��ֹ���ͻ��������ж� ��ע�⣺��ʱ���1�����ݻ�δ����������ϣ�
			CLEAR_BIT(pUart->uart->CR1, USART_CR1_TXEIE);

			// ʹ�����ݷ�������ж�
			SET_BIT(pUart->uart->CR1, USART_CR1_TCIE);
		}
		else
		{
			pUart->Sending = 1;
			
			// �ӷ���FIFOȡ1���ֽ�д�봮�ڷ������ݼĴ���
			pUart->uart->TDR = pUart->TxBuf[pUart->TxRead];
			if (++pUart->TxRead >= pUart->TxBufSize)
			{
				pUart->TxRead = 0;
			}
			pUart->TxCount--;
		}

	}
	// ����bitλȫ��������ϵ��ж�
	if (((isrflags & USART_ISR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
	{
		if (pUart->TxCount == 0)
		{
			// �������FIFO������ȫ��������ϣ���ֹ���ݷ�������ж�
			CLEAR_BIT(pUart->uart->CR1, USART_CR1_TCIE);
			pUart->Sending = 0;
		}
		else
		{
			// ��������£��������˷�֧

			// �������FIFO�����ݻ�δ��ϣ���ӷ���FIFOȡ1������д�뷢�����ݼĴ���
			pUart->uart->TDR = pUart->TxBuf[pUart->TxRead];
			if (++pUart->TxRead >= pUart->TxBufSize)
			{
				pUart->TxRead = 0;
			}
			pUart->TxCount--;
		}
	}
	
	// ����жϱ�־
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
// ��������: USART1_IRQHandler  USART2_IRQHandler USART3_IRQHandler UART4_IRQHandler UART5_IRQHandler��
// ��ڲ���: ��
// ���ز���: ��
// ע������: ��
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
// ��������: �ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���
// ��ڲ���: ��
// ���ز���: ��
// ע������: ��
//
//-----------------------------------------------------------------
int fputc(int ch, FILE *f)
{
#if 0	// ����Ҫprintf���ַ�ͨ�������ж�FIFO���ͳ�ȥ��printf��������������
	comSendChar(COM1, ch);
	
	return ch;
#else	// ����������ʽ����ÿ���ַ�,�ȴ����ݷ������
	// дһ���ֽڵ�USART1
	USART1->TDR = ch;
	
	// �ȴ����ͽ���
	while((USART1->ISR & USART_ISR_TC) == 0)
	{}
	
	return ch;
#endif
}

//-----------------------------------------------------------------
// int fgetc(FILE *f)
//-----------------------------------------------------------------
//
// ��������: �ض���getc��������������ʹ��getchar�����Ӵ���1��������
// ��ڲ���: ��
// ���ز���: ��
// ע������: ��
//
//-----------------------------------------------------------------
int fgetc(FILE *f)
{

#if 1	// �Ӵ��ڽ���FIFO��ȡ1������, ֻ��ȡ�����ݲŷ���
	uint8_t ucData;

	while(comGetChar(COM1, &ucData) == 0);

	return ucData;
#else
	// �ȴ����յ�����
	while((USART1->ISR & USART_ISR_RXNE) == 0)
	{}

	return (int)USART1->RDR;
#endif
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
