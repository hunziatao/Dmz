#ifndef _WIFI_H
#define _WIFI_H
#include "system.h"
//-----------------------------------------------------------------
// WIFI引脚定义
//-----------------------------------------------------------------
#define WIFI_RST_L		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define WIFI_RST_H		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)
#define WIFI_CH_L			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)
#define WIFI_CH_H			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)

#define COM_ESP8266	COM3		// 选择串口

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
extern void WIFI_GPIO_Init(void);
extern void ESP8266_Reset(void);
extern void ESP8266_PowerOff(void);
extern void ESP8266_PowerOn(void);
extern u8 ESP8266_WaitResponse(char * AckStr, uint8_t usart_en,uint16_t TimeOut);
extern void ESP8266_SendAT(char *_Cmd);
// AT指令
extern void ESP8266_AT(void);
extern void ESP8266_AT_RST(void);
extern void ESP8266_AT_GMR(void);
extern void ESP8266_EchoOff(void);
extern void ESP8266_EchoOn(void);
extern void ESP8266_SetWiFiMode(uint8_t mode);
extern void ESP8266_ConnectAP(char * ssid, char * pwd);
extern void ESP8266_GetAP(void);
extern void ESP8266_GetLocalIP(void);
extern void ESP8266_Set_AP_NamePass(char * ssid, char * pwd, uint8_t ch, uint8_t ecn);
extern void ESP8266_DisconnectAP(void);
extern void ESP8266_CIPMUX(uint8_t mode);
extern void ESP8266_Set_AP_IP(char * ip);
extern void ESP8266_CreateTCPServer(uint16_t TcpPort);
extern void ESP8266_ConnectionTCPServer(char * server_ip, uint16_t TcpPort);
extern void ESP8266_SetCIPMODE(uint8_t mode);
extern void ESP8266_WaitConnection(void);
extern void ESP8266_SendTcpUdp(uint8_t id, uint8_t * databuf, uint16_t len);
extern void ESP8266_SendOneTcpUdp(uint8_t * databuf, uint16_t len);
extern void ESP8266_IN_CIPMODE(void);
extern uint16_t ESP8266_RxNew(uint8_t * pRxBuf, uint8_t * link_id);


#endif
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
