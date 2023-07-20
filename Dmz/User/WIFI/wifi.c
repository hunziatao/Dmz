

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "wifi.h"
#include "delay.h"
#include "usart_fifo.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void WIFI_GPIO_Init(void)
//-----------------------------------------------------------------
// 
// 函数功能: WIFI GPIO初始化
// 入口参数: 无 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void WIFI_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;	// 配置
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				// 推挽输出
  GPIO_InitStruct.Pull = GPIO_PULLUP;								// 上拉
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;// 高速
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);						// 初始化
	
	WIFI_CH_L;	// 禁用模块
	WIFI_RST_H;
}

//-----------------------------------------------------------------
// void ESP8266_Reset(void)
//-----------------------------------------------------------------
// 
// 函数功能: WIFI模块复位
// 入口参数: 无 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_Reset(void)
{
	WIFI_RST_L;
	delay_ms(20);
	WIFI_RST_H;
	delay_ms(10);
}

//-----------------------------------------------------------------
// void ESP8266_PowerOn(void)
//-----------------------------------------------------------------
// 
// 函数功能: 给WIFI模块关机
// 入口参数: 无 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_PowerOff(void)
{
	WIFI_CH_L;
}

//-----------------------------------------------------------------
// void ESP8266_PowerOn(void)
//-----------------------------------------------------------------
// 
// 函数功能: 给WIFI模块上电
// 入口参数: 无 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_PowerOn(void)
{
	WIFI_CH_L;

	delay_ms(20);
	WIFI_CH_H;

	ESP8266_Reset();

	// 等待模块完成上电，超时500ms 自动退出
	ESP8266_WaitResponse("csum", 0, 1000);	// 先等待 csum
	ESP8266_WaitResponse("\n", 0, 1000);		// 再等待回车换行字符结束

	// 等待模块完成上电，判断是否接收到 ready
	ESP8266_WaitResponse("ready", 0, 5000);
}

//-----------------------------------------------------------------
// void ESP8266_SendAT(char *_Cmd)
//-----------------------------------------------------------------
// 
// 函数功能: 向模块发送AT命令。 本函数自动在AT字符串口增加<CR>字符
// 入口参数: Cmd : AT命令字符串，不包括末尾的回车<CR>. 以字符0结束
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_SendAT(char * Cmd)
{
	comSendBuf(COM_ESP8266, (uint8_t *)Cmd, strlen(Cmd));
	comSendBuf(COM_ESP8266, (uint8_t *)"\r\n", 2);
}

//-----------------------------------------------------------------
// u8 ESP8266_WaitResponse(char * AckStr, uint8_t usart_en,uint16_t TimeOut)
//-----------------------------------------------------------------
// 
// 函数功能: 等待ESP8266返回指定的应答字符串, 可以包含任意字符。只要接收齐全即可返回。
// 入口参数: AckStr : 应答的字符串， 长度不得超过255
//					 uint8_t usart_en：0：不打印响应信息  1：打印响应信息
//		 			 TimeOut : 命令执行超时
// 返 回 值: 1 表示成功  0 表示失败
// 注意事项: 无
//
//-----------------------------------------------------------------
u8 ESP8266_WaitResponse(char * AckStr, uint8_t usart_en,uint16_t TimeOut)
{
	uint32_t TIME=0;
	uint8_t ucData;
	uint16_t pos = 0;
	uint32_t len;
	uint8_t ret;

	len = strlen(AckStr);
	if (len > 255)
	{
		return 0;
	}

	while (1)
	{
		if (TIME > TimeOut*100)
		{
			ret = 0;	// 超时
			break;
		}

		if (comGetChar(COM_ESP8266, &ucData))
		{
			if(usart_en == 1)
				comSendChar(COM1, ucData);		// 将接收到数据打印到调试串口1
			if (ucData == AckStr[pos])
			{
				pos++;
				
				if (pos == len)
				{
					ret = 1;	/* 收到指定的应答数据，返回成功 */
					break;
				}
			}
			else
			{
				pos = 0;
			}
		}
		TIME++;
	}
	return ret;
}

//-----------------------------------------------------------------
//----------------------------基础AT指令---------------------------
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void ESP8266_AT(void)
//-----------------------------------------------------------------
// 
// 函数功能: AT应答
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_AT(void)
{
	printf("\r\n设置AT应答 -> ");
	do{
		ESP8266_SendAT("AT");
		delay_ms(1);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("模块应答AT成功\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_AT_RST(void)
//-----------------------------------------------------------------
// 
// 函数功能: WIFI模块重启
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_AT_RST(void)
{
	printf("\r\nWIFI模块重启 -> ");
	do{
		ESP8266_SendAT("AT+RST");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("WIFI模块重启成功\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_AT_GMR(void)
//-----------------------------------------------------------------
// 
// 函数功能: 查看版本信息
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_AT_GMR(void)
{
	printf("\r\n查看版本信息 -> ");
	do{
		ESP8266_SendAT("AT+GMR");
	}while(ESP8266_WaitResponse("OK", 1, 2000) == 0);
	printf("\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_EchoOff(void)
//-----------------------------------------------------------------
// 
// 函数功能: 关闭回显
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_EchoOff(void)
{
	printf("\r\n关闭回显 -> ");
	do{
		ESP8266_SendAT("ATE0");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("关闭回显成功\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_EchoOn(void)
//-----------------------------------------------------------------
// 
// 函数功能: 开启回显
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_EchoOn(void)
{
	printf("\r\n开启回显 -> ");
	do{
		ESP8266_SendAT("ATE1");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("开启回显成功\r\n");
}

//-----------------------------------------------------------------
//--------------------------WIFI功能AT指令-------------------------
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void ESP8266_SetWiFiMode(uint8_t mode)
//-----------------------------------------------------------------
// 
// 函数功能: 设置WiFi模块工作模式
// 入口参数: mode : 1 = Station模式,  2 = AP模式,  3 = AP兼Station模式
// 返 回 值: 无
// 注意事项: 该指令需要重启才能生效，设置完后需要调用ESP8266_AT_RST()函数后生效
//
//-----------------------------------------------------------------
void ESP8266_SetWiFiMode(uint8_t mode)
{
	char cmd_buf[30];
	
	if (mode == 0 || mode > 3)
	{
		mode = 3;
	}
	printf("\r\n设置WIFI模块工作模式 -> ");
	do{
		sprintf(cmd_buf, "AT+CWMODE=%d", mode);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	if(mode == 1)
		printf("WIFI模块工作在Station模式\r\n");
	else if(mode == 2)
		printf("WIFI模块工作在AP模式\r\n");
	else if(mode == 3)
		printf("WIFI模块工作在Station兼AP模式\r\n");
	else
		printf("WIFI模块工作在无效模式\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_ConnectAP(char * ssid, char * pwd)
//-----------------------------------------------------------------
// 
// 函数功能: 连接AP
// 入口参数: ssid :AP的名字，字符串参数，密码最长 64 字节 ASCII
//		 			 pwd : AP的密码，字符串参数，密码最长 64 字节 ASCII
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_ConnectAP(char * ssid, char * pwd)
{
	char cmd_buf[40];

	printf("\r\n连接AP -> ");
	// 断开连接，防止连接到其他AP而出错
	do{
		ESP8266_SendAT("AT+CWQAP");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	delay_ms(500);
	do{
		// AT+CWJAP=”ssid”,”password”
		sprintf(cmd_buf, "AT+CWJAP=\"%s\",\"%s\"", ssid, pwd);
		ESP8266_SendAT(cmd_buf);
		delay_ms(500);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("AP连接成功\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_DisconnectAP(void)
//-----------------------------------------------------------------
// 
// 函数功能: 断开AP
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_DisconnectAP(void)
{
	printf("\r\n断开AP -> ");
	do{
		ESP8266_SendAT("AT+CWQAP");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("AP断开成功\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_GetAP(void)
//-----------------------------------------------------------------
// 
// 函数功能: 列出当前可用AP
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_GetAP(void)
{
	printf("\r\n当前可用AP -> ");
	do{
		ESP8266_SendAT("AT+CWLAP");
	}while(ESP8266_WaitResponse("OK", 1, 2000) == 0);
	printf("\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_Set_AP_NamePass(char * ssid, char * pwd, uint8_t ch, uint8_t ecn)
//-----------------------------------------------------------------
// 
// 函数功能: 设置AP模式下的参数，加密方式和密码. 
// 入口参数: ssid :AP的名字，字符串参数，密码最长 64 字节 ASCII
//		 			 pwd : AP的密码，字符串参数，密码最长 64 字节 ASCII
//		 			 ch : 通道号
//		 			 ecn：加密方式，0：OPEN；1：WEP；2：WPA_PSK；3：WPA2_PSK；4：WPA_WPA2_PSK；
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_Set_AP_NamePass(char * ssid, char * pwd, uint8_t ch, uint8_t ecn)
{
	char cmd_buf[40];

	printf("\r\n设置SoftAP的名字，加密方式和密码 -> ");
	do{
		// AT+CWSAP="B512","B512B512",6,4
		sprintf(cmd_buf, "AT+CWSAP=\"%s\",\"%s\",%d,%d", ssid, pwd, ch, ecn);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("设置AP参数成功\r\n");
	printf("AP名称为：%s\r\n",ssid);
	printf("AP密码为：%s\r\n",pwd);
	printf("通道号为：%d\r\n",ch);
	switch(ecn)
	{
		case 0 : printf("加密方式为：OPEN\r\n");break;
		case 1 : printf("加密方式为：WEP\r\n");break;
		case 2 : printf("加密方式为：WPA_PSK\r\n");break;
		case 3 : printf("加密方式为：WPA2_PSK\r\n");break;
		case 4 : printf("加密方式为：WPA_WPA2_PSK\r\n");break;
	}
}

//-----------------------------------------------------------------
// void ESP8266_Set_AP_IP(char * ip)
//-----------------------------------------------------------------
// 
// 函数功能: 设置AP的IP地址
// 入口参数: ip :AP的IP地址，标准字符串
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_Set_AP_IP(char * ip)
{
	char cmd_buf[30];
	
	printf("\r\n设置AP的IP地址 -> ");
	do{
		sprintf(cmd_buf, "AT+CIPAP=\"%s\"", ip);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("AP的IP地址：%s \r\n",ip);
}

//-----------------------------------------------------------------
//------------------------TCP/IP工具箱AT指令-----------------------
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void ESP8266_GetLocalIP(void)
//-----------------------------------------------------------------
// 
// 函数功能: 查询WIFI模块的IP地址和MAC
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_GetLocalIP(void)
{
	printf("\r\n获取WIFI模块的IP地址和MAC -> ");
	do
	{
		ESP8266_SendAT("AT+CIFSR");
	}while(ESP8266_WaitResponse("OK", 1, 2000) == 0);
	printf("\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_CIPMUX(uint8_t mode)
//-----------------------------------------------------------------
// 
// 函数功能: 单连接/多连接模式
// 入口参数: mode : 0,表示关闭， 1表示启动
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_CIPMUX(uint8_t mode)
{
	char cmd_buf[30];
	
	if (mode > 0)
	{
		mode = 1;
	}
	printf("\r\n连接模式 -> ");
	do{
		sprintf(cmd_buf, "AT+CIPMUX=%d", mode);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	if(mode == 1)
		printf("启动多连接模式\r\n");
	else if(mode == 0)
		printf("启动单连接模式\r\n");
	else
		printf("连接模式无效\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_CreateTCPServer(uint16_t TcpPort)
//-----------------------------------------------------------------
// 
// 函数功能: 创建一个TCP服务端
// 入口参数: TcpPort : TCP 端口号
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_CreateTCPServer(uint16_t TcpPort)
{
	char cmd_buf[30];

	printf("\r\n创建一个TCP服务端 -> ");
	do{
		sprintf(cmd_buf, "AT+CIPSERVER=1,%d", TcpPort);
		ESP8266_SendAT(cmd_buf);	
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("端口号：%d \r\n",TcpPort);
}

//-----------------------------------------------------------------
// void ESP8266_ConnectionTCPServer(char * server_ip, uint16_t TcpPort)
//-----------------------------------------------------------------
// 
// 函数功能: 连接到一个TCP服务端
// 入口参数: server_ip : 远程服务器的IP地址
//					 TcpPort : 远程服务器的端口号
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_ConnectionTCPServer(char * server_ip, uint16_t TcpPort)
{
	char cmd_buf[64];

	printf("\r\n连接一个TCP服务端 -> ");
	do{
		sprintf(cmd_buf, "AT+CIPSTART=\"TCP\",\"%s\",%d",server_ip, TcpPort);
		ESP8266_SendAT(cmd_buf);	
	}while(ESP8266_WaitResponse("OK", 0, 20000) == 0);
	printf("TCP服务端连接成功\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_SetCIPMODE(uint8_t mode)
//-----------------------------------------------------------------
// 
// 函数功能: 设置透传模式
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_SetCIPMODE(uint8_t mode)
{
	char cmd_buf[64];
	printf("\r\nWIFI模块开启透传 -> ");
	do{
		sprintf(cmd_buf, "AT+CIPMODE=%d",mode);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("WIFI模块开启透传成功\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_WaitConnection(void)
//-----------------------------------------------------------------
// 
// 函数功能: 等待连接
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_WaitConnection(void)
{
	printf("\r\n等待连接 -> ");
	do{
			delay_ms(200);
	}while(ESP8266_WaitResponse("CONNECT", 0, 2000) == 0);
	printf("连接成功\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_SendTcpUdp(uint8_t id, uint8_t * databuf, uint16_t len)
//-----------------------------------------------------------------
// 
// 函数功能: 发送TCP或UDP数据包（多连接模式）
// 入口参数: id : 多连接时，连接ID （0-4）
//			  	 databuf 数据
//			  	 len 数据长度
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_SendTcpUdp(uint8_t id, uint8_t * databuf, uint16_t len)
{
	char cmd_buf[32];

	if (len > 2048)
	{
		len = 2048;
	}
	
	do{
		sprintf(cmd_buf, "AT+CIPSEND=%d,%d", id, len);
		ESP8266_SendAT(cmd_buf);	
	}while(ESP8266_WaitResponse(">", 0, 2000) == 0);
	
	comSendBuf(COM3,(uint8_t *)databuf,len);
	while(ESP8266_WaitResponse("SEND OK", 0, 8000) == 0);
}

//-----------------------------------------------------------------
// void ESP8266_SendOneTcpUdp(uint8_t * databuf, uint16_t len)
//-----------------------------------------------------------------
// 
// 函数功能: 发送TCP或UDP数据包（单连接模式）
// 入口参数: databuf 数据
//			  	 len 数据长度
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_SendOneTcpUdp(uint8_t * databuf, uint16_t len)
{
	char cmd_buf[32];

	if (len > 2048)
	{
		len = 2048;
	}
	
	do{
		sprintf(cmd_buf, "AT+CIPSEND=%d", len);
		ESP8266_SendAT(cmd_buf);	
	}while(ESP8266_WaitResponse(">", 0, 2000) == 0);
	
	comSendBuf(COM3,(uint8_t *)databuf,len);
	while(ESP8266_WaitResponse("SEND OK", 0, 8000) == 0);
}

//-----------------------------------------------------------------
// void ESP8266_IN_CIPMODE(void)
//-----------------------------------------------------------------
// 
// 函数功能: 进入透传数据
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ESP8266_IN_CIPMODE(void)
{
	printf("\r\n进入透传数据 -> ");
	do{
		ESP8266_SendAT("AT+CIPSEND"); 
		delay_ms(200);
  }while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("成功进入透传数据\r\n");
}

//-----------------------------------------------------------------
// uint16_t ESP8266_RxNew(uint8_t * pRxBuf, uint8_t * link_id)
//-----------------------------------------------------------------
// 
// 函数功能: 接收新数据帧 +IPD
// 入口参数: _pRxBuf : 接收到的数据存放在此缓冲区
//			  	 _link_id : TCP连接的id， 识别是局域网手机，还是来自于服务器
// 返 回 值: 接收到的数据长度. 0 表示无数据
// 注意事项: 无
//
//-----------------------------------------------------------------
uint16_t ESP8266_RxNew(uint8_t * pRxBuf, uint8_t * link_id)
{
	uint8_t ucData;
	static uint8_t s_buf[2048];
	static uint16_t s_len = 0;
	static uint8_t s_flag = 0;
	static uint16_t s_data_len = 0;
	
	while (comGetChar(COM_ESP8266, &ucData))
	{
		comSendChar(COM1,ucData);		// 将接收到数据打印到调试串口1

		if (s_flag == 0)
		{
			if (s_len < sizeof(s_buf))
			{
				s_buf[s_len++] = ucData;	// 保存接收到的数据
			}			
			if (ucData == '+')
			{
				s_len = 1;
				s_data_len = 0;
				s_buf[0] = 0;
			}
			if (s_len > 7 && ucData == ':')
			{
				*link_id =(uint8_t)((char)s_buf[5] - '0');		// 解析出连接id
				if(s_len == 9)
					s_data_len = (uint16_t)((char)s_buf[7] - '0');
				else if(s_len == 10)
					s_data_len = (uint16_t)((char)s_buf[7] - '0')*10 + (uint16_t)((char)s_buf[8] - '0');
				else if(s_len == 11)
					s_data_len = (uint16_t)((char)s_buf[7] - '0')*100 + (uint16_t)((char)s_buf[8] - '0')*10 + (uint16_t)((char)s_buf[9] - '0');
				else if(s_len == 12)
					s_data_len = (uint16_t)((char)s_buf[7] - '0')*1000 + (uint16_t)((char)s_buf[8] - '0')*100 + (uint16_t)((char)s_buf[9] - '0')*10 + (uint16_t)((char)s_buf[10] - '0');
				else
					s_data_len = 0;
				s_flag = 1;	
				s_len = 0;
			}
		}
		else
		{
			if (s_len < sizeof(s_buf))
			{
				s_buf[s_len++] = ucData;		// 保存接收到的数据
				
				if (s_len == s_data_len)
				{
					s_flag = 0;
					s_len = 0;
					
					memcpy(pRxBuf, s_buf, s_data_len);
					
					return s_data_len;
				}
			}	
			else
			{
				s_flag = 0;
			}
		}

	}
	return 0;
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
