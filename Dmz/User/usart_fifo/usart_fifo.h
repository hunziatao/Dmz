//-----------------------------------------------------------------
// ��������:
// 		 ����ͨѶ��������ͷ�ļ�
// ��    ��: ���ǵ���
// ��ʼ����: 2020-11-11
// �������: 2020-11-11
// �޸�����: 
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0: (2020-11-11)���ڳ�ʼ���������ж�
// ���Թ���: ����STM32H750���İ塢LZE_ST_LINK2
// ˵    ��: 
//    
//-----------------------------------------------------------------
#ifndef _USART_FIFO_H
#define _USART_FIFO_H
#include "system.h"

//-----------------------------------------------------------------
// ����USART����
//-----------------------------------------------------------------
// ����˿ں�
typedef enum
{
	COM1 = 0,			// USART1
	COM3 = 2,			// USART3
	COM4 = 3,			// UART4
	COM5 = 4,			// UART5
	COM6 = 5,			// USART6	
}COM_PORT_E;

// �����豸�ṹ��
typedef struct
{
	USART_TypeDef *uart;		// STM32�ڲ������豸ָ��
	uint8_t *TxBuf;					// ���ͻ�����
	uint8_t *RxBuf;					// ���ջ�����
	uint16_t TxBufSize;			// ���ͻ�������С
	uint16_t RxBufSize;			// ���ջ�������С
	__IO uint16_t TxWrite;	// ���ͻ�����дָ��
	__IO uint16_t TxRead;		// ���ͻ�������ָ��
	__IO uint16_t TxCount;	// �ȴ����͵����ݸ���

	__IO uint16_t RxWrite;	// ���ջ�����дָ��
	__IO uint16_t RxRead;		// ���ջ�������ָ��
	__IO uint16_t RxCount;	// ��δ��ȡ�������ݸ���

	uint8_t Sending;				// ���ڷ�����
}UART_T;

#define	UART1_FIFO_EN	1
#define	UART3_FIFO_EN	1
#define	UART4_FIFO_EN	1
#define	UART5_FIFO_EN	1
#define	UART6_FIFO_EN	0


// ���崮�ڲ����ʺ�FIFO��������С����Ϊ���ͻ������ͽ��ջ�����, ֧��ȫ˫��
#if UART1_FIFO_EN == 1
	#define UART1_BAUD			115200
	#define UART1_TX_BUF_SIZE	1*1024
	#define UART1_RX_BUF_SIZE	1*1024
#endif

#if UART3_FIFO_EN == 1
	#define UART3_BAUD			115200
	#define UART3_TX_BUF_SIZE	1*1024
	#define UART3_RX_BUF_SIZE	1*1024
#endif

#if UART4_FIFO_EN == 1
	#define UART4_BAUD			115200
	#define UART4_TX_BUF_SIZE	1*1024
	#define UART4_RX_BUF_SIZE	1*1024
#endif

#if UART5_FIFO_EN == 1
	#define UART5_BAUD			115200
	#define UART5_TX_BUF_SIZE	1*1024
	#define UART5_RX_BUF_SIZE	1*1024
#endif

#if UART6_FIFO_EN == 1
	#define UART6_BAUD			115200
	#define UART6_TX_BUF_SIZE	1*1024
	#define UART6_RX_BUF_SIZE	1*1024
#endif


// ����ÿ�����ڽṹ�����
#if UART1_FIFO_EN == 1
	static UART_T UART1_T;
	static uint8_t UART1_TxBuf[UART1_TX_BUF_SIZE];		// ���ͻ�����
	static uint8_t UART1_RxBuf[UART1_RX_BUF_SIZE];		// ���ջ�����
#endif

#if UART3_FIFO_EN == 1
	static UART_T UART3_T;
	static uint8_t UART3_TxBuf[UART3_TX_BUF_SIZE];		// ���ͻ�����
	static uint8_t UART3_RxBuf[UART3_RX_BUF_SIZE];		// ���ջ�����
#endif

#if UART4_FIFO_EN == 1
	static UART_T UART4_T;
	static uint8_t UART4_TxBuf[UART4_TX_BUF_SIZE];		// ���ͻ�����
	static uint8_t UART4_RxBuf[UART4_RX_BUF_SIZE];		// ���ջ�����
#endif

#if UART5_FIFO_EN == 1
	static UART_T UART5_T;
	static uint8_t UART5_TxBuf[UART5_TX_BUF_SIZE];		// ���ͻ�����
	static uint8_t UART5_RxBuf[UART5_RX_BUF_SIZE];		// ���ջ�����
#endif

#if UART6_FIFO_EN == 1
	static UART_T UART6_T;
	static uint8_t UART6_TxBuf6[UART6_TX_BUF_SIZE];		// ���ͻ�����
	static uint8_t UART6_RxBuf6[UART6_RX_BUF_SIZE];		// ���ջ�����
#endif

// ����ȫ���жϵĺ�
#define ENABLE_INT()	__set_PRIMASK(0)					// ʹ��ȫ���ж�
#define DISABLE_INT()	__set_PRIMASK(1)					// ��ֹȫ���ж�
//-----------------------------------------------------------------
// �ⲿ��������
//-----------------------------------------------------------------
extern void uart_init(void);
extern UART_T *ComToUart(COM_PORT_E Port);
extern USART_TypeDef *ComToUSARTx(COM_PORT_E Port);
extern void SetUartParam(USART_TypeDef *Instance,  uint32_t BaudRate, uint32_t Parity, uint32_t Mode);
extern void comSetBaud(COM_PORT_E Port, uint32_t BaudRate);
extern void comSendBuf(COM_PORT_E Port, uint8_t *TxBuf, uint16_t Len);
extern void comSendChar(COM_PORT_E Port, uint8_t Byte);
extern uint8_t comGetChar(COM_PORT_E Port, uint8_t *Byte);
extern void comClearTxFifo(COM_PORT_E Port);
extern void comClearRxFifo(COM_PORT_E Port);
static void UartSend(UART_T *pUart, uint8_t *Buf, uint16_t Len);
static uint8_t UartGetChar(UART_T *pUart, uint8_t *Byte);
extern uint8_t UartTxEmpty(COM_PORT_E Port);
//-----------------------------------------------------------------
#endif
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
