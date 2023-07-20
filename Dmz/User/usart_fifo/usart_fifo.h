//-----------------------------------------------------------------
// 程序描述:
// 		 串口通讯驱动程序头文件
// 作    者: 凌智电子
// 开始日期: 2020-11-11
// 完成日期: 2020-11-11
// 修改日期: 
// 当前版本: V1.0
// 历史版本:
//  - V1.0: (2020-11-11)串口初始化，串口中断
// 调试工具: 凌智STM32H750核心板、LZE_ST_LINK2
// 说    明: 
//    
//-----------------------------------------------------------------
#ifndef _USART_FIFO_H
#define _USART_FIFO_H
#include "system.h"

//-----------------------------------------------------------------
// 定义USART变量
//-----------------------------------------------------------------
// 定义端口号
typedef enum
{
	COM1 = 0,			// USART1
	COM3 = 2,			// USART3
	COM4 = 3,			// UART4
	COM5 = 4,			// UART5
	COM6 = 5,			// USART6	
}COM_PORT_E;

// 串口设备结构体
typedef struct
{
	USART_TypeDef *uart;		// STM32内部串口设备指针
	uint8_t *TxBuf;					// 发送缓冲区
	uint8_t *RxBuf;					// 接收缓冲区
	uint16_t TxBufSize;			// 发送缓冲区大小
	uint16_t RxBufSize;			// 接收缓冲区大小
	__IO uint16_t TxWrite;	// 发送缓冲区写指针
	__IO uint16_t TxRead;		// 发送缓冲区读指针
	__IO uint16_t TxCount;	// 等待发送的数据个数

	__IO uint16_t RxWrite;	// 接收缓冲区写指针
	__IO uint16_t RxRead;		// 接收缓冲区读指针
	__IO uint16_t RxCount;	// 还未读取的新数据个数

	uint8_t Sending;				// 正在发送中
}UART_T;

#define	UART1_FIFO_EN	1
#define	UART3_FIFO_EN	1
#define	UART4_FIFO_EN	1
#define	UART5_FIFO_EN	1
#define	UART6_FIFO_EN	0


// 定义串口波特率和FIFO缓冲区大小，分为发送缓冲区和接收缓冲区, 支持全双工
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


// 定义每个串口结构体变量
#if UART1_FIFO_EN == 1
	static UART_T UART1_T;
	static uint8_t UART1_TxBuf[UART1_TX_BUF_SIZE];		// 发送缓冲区
	static uint8_t UART1_RxBuf[UART1_RX_BUF_SIZE];		// 接收缓冲区
#endif

#if UART3_FIFO_EN == 1
	static UART_T UART3_T;
	static uint8_t UART3_TxBuf[UART3_TX_BUF_SIZE];		// 发送缓冲区
	static uint8_t UART3_RxBuf[UART3_RX_BUF_SIZE];		// 接收缓冲区
#endif

#if UART4_FIFO_EN == 1
	static UART_T UART4_T;
	static uint8_t UART4_TxBuf[UART4_TX_BUF_SIZE];		// 发送缓冲区
	static uint8_t UART4_RxBuf[UART4_RX_BUF_SIZE];		// 接收缓冲区
#endif

#if UART5_FIFO_EN == 1
	static UART_T UART5_T;
	static uint8_t UART5_TxBuf[UART5_TX_BUF_SIZE];		// 发送缓冲区
	static uint8_t UART5_RxBuf[UART5_RX_BUF_SIZE];		// 接收缓冲区
#endif

#if UART6_FIFO_EN == 1
	static UART_T UART6_T;
	static uint8_t UART6_TxBuf6[UART6_TX_BUF_SIZE];		// 发送缓冲区
	static uint8_t UART6_RxBuf6[UART6_RX_BUF_SIZE];		// 接收缓冲区
#endif

// 开关全局中断的宏
#define ENABLE_INT()	__set_PRIMASK(0)					// 使能全局中断
#define DISABLE_INT()	__set_PRIMASK(1)					// 禁止全局中断
//-----------------------------------------------------------------
// 外部函数声明
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
