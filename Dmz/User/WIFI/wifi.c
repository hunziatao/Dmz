

//-----------------------------------------------------------------
// ͷ�ļ�����
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
// ��������: WIFI GPIO��ʼ��
// ��ڲ���: �� 
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void WIFI_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;	// ����
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				// �������
  GPIO_InitStruct.Pull = GPIO_PULLUP;								// ����
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;// ����
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);						// ��ʼ��
	
	WIFI_CH_L;	// ����ģ��
	WIFI_RST_H;
}

//-----------------------------------------------------------------
// void ESP8266_Reset(void)
//-----------------------------------------------------------------
// 
// ��������: WIFIģ�鸴λ
// ��ڲ���: �� 
// �� �� ֵ: ��
// ע������: ��
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
// ��������: ��WIFIģ��ػ�
// ��ڲ���: �� 
// �� �� ֵ: ��
// ע������: ��
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
// ��������: ��WIFIģ���ϵ�
// ��ڲ���: �� 
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_PowerOn(void)
{
	WIFI_CH_L;

	delay_ms(20);
	WIFI_CH_H;

	ESP8266_Reset();

	// �ȴ�ģ������ϵ磬��ʱ500ms �Զ��˳�
	ESP8266_WaitResponse("csum", 0, 1000);	// �ȵȴ� csum
	ESP8266_WaitResponse("\n", 0, 1000);		// �ٵȴ��س������ַ�����

	// �ȴ�ģ������ϵ磬�ж��Ƿ���յ� ready
	ESP8266_WaitResponse("ready", 0, 5000);
}

//-----------------------------------------------------------------
// void ESP8266_SendAT(char *_Cmd)
//-----------------------------------------------------------------
// 
// ��������: ��ģ�鷢��AT��� �������Զ���AT�ַ���������<CR>�ַ�
// ��ڲ���: Cmd : AT�����ַ�����������ĩβ�Ļس�<CR>. ���ַ�0����
// �� �� ֵ: ��
// ע������: ��
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
// ��������: �ȴ�ESP8266����ָ����Ӧ���ַ���, ���԰��������ַ���ֻҪ������ȫ���ɷ��ء�
// ��ڲ���: AckStr : Ӧ����ַ����� ���Ȳ��ó���255
//					 uint8_t usart_en��0������ӡ��Ӧ��Ϣ  1����ӡ��Ӧ��Ϣ
//		 			 TimeOut : ����ִ�г�ʱ
// �� �� ֵ: 1 ��ʾ�ɹ�  0 ��ʾʧ��
// ע������: ��
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
			ret = 0;	// ��ʱ
			break;
		}

		if (comGetChar(COM_ESP8266, &ucData))
		{
			if(usart_en == 1)
				comSendChar(COM1, ucData);		// �����յ����ݴ�ӡ�����Դ���1
			if (ucData == AckStr[pos])
			{
				pos++;
				
				if (pos == len)
				{
					ret = 1;	/* �յ�ָ����Ӧ�����ݣ����سɹ� */
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
//----------------------------����ATָ��---------------------------
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void ESP8266_AT(void)
//-----------------------------------------------------------------
// 
// ��������: ATӦ��
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_AT(void)
{
	printf("\r\n����ATӦ�� -> ");
	do{
		ESP8266_SendAT("AT");
		delay_ms(1);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("ģ��Ӧ��AT�ɹ�\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_AT_RST(void)
//-----------------------------------------------------------------
// 
// ��������: WIFIģ������
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_AT_RST(void)
{
	printf("\r\nWIFIģ������ -> ");
	do{
		ESP8266_SendAT("AT+RST");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("WIFIģ�������ɹ�\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_AT_GMR(void)
//-----------------------------------------------------------------
// 
// ��������: �鿴�汾��Ϣ
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_AT_GMR(void)
{
	printf("\r\n�鿴�汾��Ϣ -> ");
	do{
		ESP8266_SendAT("AT+GMR");
	}while(ESP8266_WaitResponse("OK", 1, 2000) == 0);
	printf("\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_EchoOff(void)
//-----------------------------------------------------------------
// 
// ��������: �رջ���
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_EchoOff(void)
{
	printf("\r\n�رջ��� -> ");
	do{
		ESP8266_SendAT("ATE0");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�رջ��Գɹ�\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_EchoOn(void)
//-----------------------------------------------------------------
// 
// ��������: ��������
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_EchoOn(void)
{
	printf("\r\n�������� -> ");
	do{
		ESP8266_SendAT("ATE1");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�������Գɹ�\r\n");
}

//-----------------------------------------------------------------
//--------------------------WIFI����ATָ��-------------------------
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void ESP8266_SetWiFiMode(uint8_t mode)
//-----------------------------------------------------------------
// 
// ��������: ����WiFiģ�鹤��ģʽ
// ��ڲ���: mode : 1 = Stationģʽ,  2 = APģʽ,  3 = AP��Stationģʽ
// �� �� ֵ: ��
// ע������: ��ָ����Ҫ����������Ч�����������Ҫ����ESP8266_AT_RST()��������Ч
//
//-----------------------------------------------------------------
void ESP8266_SetWiFiMode(uint8_t mode)
{
	char cmd_buf[30];
	
	if (mode == 0 || mode > 3)
	{
		mode = 3;
	}
	printf("\r\n����WIFIģ�鹤��ģʽ -> ");
	do{
		sprintf(cmd_buf, "AT+CWMODE=%d", mode);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	if(mode == 1)
		printf("WIFIģ�鹤����Stationģʽ\r\n");
	else if(mode == 2)
		printf("WIFIģ�鹤����APģʽ\r\n");
	else if(mode == 3)
		printf("WIFIģ�鹤����Station��APģʽ\r\n");
	else
		printf("WIFIģ�鹤������Чģʽ\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_ConnectAP(char * ssid, char * pwd)
//-----------------------------------------------------------------
// 
// ��������: ����AP
// ��ڲ���: ssid :AP�����֣��ַ�������������� 64 �ֽ� ASCII
//		 			 pwd : AP�����룬�ַ�������������� 64 �ֽ� ASCII
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_ConnectAP(char * ssid, char * pwd)
{
	char cmd_buf[40];

	printf("\r\n����AP -> ");
	// �Ͽ����ӣ���ֹ���ӵ�����AP������
	do{
		ESP8266_SendAT("AT+CWQAP");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	delay_ms(500);
	do{
		// AT+CWJAP=��ssid��,��password��
		sprintf(cmd_buf, "AT+CWJAP=\"%s\",\"%s\"", ssid, pwd);
		ESP8266_SendAT(cmd_buf);
		delay_ms(500);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("AP���ӳɹ�\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_DisconnectAP(void)
//-----------------------------------------------------------------
// 
// ��������: �Ͽ�AP
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_DisconnectAP(void)
{
	printf("\r\n�Ͽ�AP -> ");
	do{
		ESP8266_SendAT("AT+CWQAP");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("AP�Ͽ��ɹ�\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_GetAP(void)
//-----------------------------------------------------------------
// 
// ��������: �г���ǰ����AP
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_GetAP(void)
{
	printf("\r\n��ǰ����AP -> ");
	do{
		ESP8266_SendAT("AT+CWLAP");
	}while(ESP8266_WaitResponse("OK", 1, 2000) == 0);
	printf("\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_Set_AP_NamePass(char * ssid, char * pwd, uint8_t ch, uint8_t ecn)
//-----------------------------------------------------------------
// 
// ��������: ����APģʽ�µĲ��������ܷ�ʽ������. 
// ��ڲ���: ssid :AP�����֣��ַ�������������� 64 �ֽ� ASCII
//		 			 pwd : AP�����룬�ַ�������������� 64 �ֽ� ASCII
//		 			 ch : ͨ����
//		 			 ecn�����ܷ�ʽ��0��OPEN��1��WEP��2��WPA_PSK��3��WPA2_PSK��4��WPA_WPA2_PSK��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_Set_AP_NamePass(char * ssid, char * pwd, uint8_t ch, uint8_t ecn)
{
	char cmd_buf[40];

	printf("\r\n����SoftAP�����֣����ܷ�ʽ������ -> ");
	do{
		// AT+CWSAP="B512","B512B512",6,4
		sprintf(cmd_buf, "AT+CWSAP=\"%s\",\"%s\",%d,%d", ssid, pwd, ch, ecn);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("����AP�����ɹ�\r\n");
	printf("AP����Ϊ��%s\r\n",ssid);
	printf("AP����Ϊ��%s\r\n",pwd);
	printf("ͨ����Ϊ��%d\r\n",ch);
	switch(ecn)
	{
		case 0 : printf("���ܷ�ʽΪ��OPEN\r\n");break;
		case 1 : printf("���ܷ�ʽΪ��WEP\r\n");break;
		case 2 : printf("���ܷ�ʽΪ��WPA_PSK\r\n");break;
		case 3 : printf("���ܷ�ʽΪ��WPA2_PSK\r\n");break;
		case 4 : printf("���ܷ�ʽΪ��WPA_WPA2_PSK\r\n");break;
	}
}

//-----------------------------------------------------------------
// void ESP8266_Set_AP_IP(char * ip)
//-----------------------------------------------------------------
// 
// ��������: ����AP��IP��ַ
// ��ڲ���: ip :AP��IP��ַ����׼�ַ���
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_Set_AP_IP(char * ip)
{
	char cmd_buf[30];
	
	printf("\r\n����AP��IP��ַ -> ");
	do{
		sprintf(cmd_buf, "AT+CIPAP=\"%s\"", ip);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("AP��IP��ַ��%s \r\n",ip);
}

//-----------------------------------------------------------------
//------------------------TCP/IP������ATָ��-----------------------
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void ESP8266_GetLocalIP(void)
//-----------------------------------------------------------------
// 
// ��������: ��ѯWIFIģ���IP��ַ��MAC
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_GetLocalIP(void)
{
	printf("\r\n��ȡWIFIģ���IP��ַ��MAC -> ");
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
// ��������: ������/������ģʽ
// ��ڲ���: mode : 0,��ʾ�رգ� 1��ʾ����
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_CIPMUX(uint8_t mode)
{
	char cmd_buf[30];
	
	if (mode > 0)
	{
		mode = 1;
	}
	printf("\r\n����ģʽ -> ");
	do{
		sprintf(cmd_buf, "AT+CIPMUX=%d", mode);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	if(mode == 1)
		printf("����������ģʽ\r\n");
	else if(mode == 0)
		printf("����������ģʽ\r\n");
	else
		printf("����ģʽ��Ч\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_CreateTCPServer(uint16_t TcpPort)
//-----------------------------------------------------------------
// 
// ��������: ����һ��TCP�����
// ��ڲ���: TcpPort : TCP �˿ں�
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_CreateTCPServer(uint16_t TcpPort)
{
	char cmd_buf[30];

	printf("\r\n����һ��TCP����� -> ");
	do{
		sprintf(cmd_buf, "AT+CIPSERVER=1,%d", TcpPort);
		ESP8266_SendAT(cmd_buf);	
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�˿ںţ�%d \r\n",TcpPort);
}

//-----------------------------------------------------------------
// void ESP8266_ConnectionTCPServer(char * server_ip, uint16_t TcpPort)
//-----------------------------------------------------------------
// 
// ��������: ���ӵ�һ��TCP�����
// ��ڲ���: server_ip : Զ�̷�������IP��ַ
//					 TcpPort : Զ�̷������Ķ˿ں�
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_ConnectionTCPServer(char * server_ip, uint16_t TcpPort)
{
	char cmd_buf[64];

	printf("\r\n����һ��TCP����� -> ");
	do{
		sprintf(cmd_buf, "AT+CIPSTART=\"TCP\",\"%s\",%d",server_ip, TcpPort);
		ESP8266_SendAT(cmd_buf);	
	}while(ESP8266_WaitResponse("OK", 0, 20000) == 0);
	printf("TCP��������ӳɹ�\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_SetCIPMODE(uint8_t mode)
//-----------------------------------------------------------------
// 
// ��������: ����͸��ģʽ
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_SetCIPMODE(uint8_t mode)
{
	char cmd_buf[64];
	printf("\r\nWIFIģ�鿪��͸�� -> ");
	do{
		sprintf(cmd_buf, "AT+CIPMODE=%d",mode);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("WIFIģ�鿪��͸���ɹ�\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_WaitConnection(void)
//-----------------------------------------------------------------
// 
// ��������: �ȴ�����
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_WaitConnection(void)
{
	printf("\r\n�ȴ����� -> ");
	do{
			delay_ms(200);
	}while(ESP8266_WaitResponse("CONNECT", 0, 2000) == 0);
	printf("���ӳɹ�\r\n");
}

//-----------------------------------------------------------------
// void ESP8266_SendTcpUdp(uint8_t id, uint8_t * databuf, uint16_t len)
//-----------------------------------------------------------------
// 
// ��������: ����TCP��UDP���ݰ���������ģʽ��
// ��ڲ���: id : ������ʱ������ID ��0-4��
//			  	 databuf ����
//			  	 len ���ݳ���
// �� �� ֵ: ��
// ע������: ��
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
// ��������: ����TCP��UDP���ݰ���������ģʽ��
// ��ڲ���: databuf ����
//			  	 len ���ݳ���
// �� �� ֵ: ��
// ע������: ��
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
// ��������: ����͸������
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ESP8266_IN_CIPMODE(void)
{
	printf("\r\n����͸������ -> ");
	do{
		ESP8266_SendAT("AT+CIPSEND"); 
		delay_ms(200);
  }while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�ɹ�����͸������\r\n");
}

//-----------------------------------------------------------------
// uint16_t ESP8266_RxNew(uint8_t * pRxBuf, uint8_t * link_id)
//-----------------------------------------------------------------
// 
// ��������: ����������֡ +IPD
// ��ڲ���: _pRxBuf : ���յ������ݴ���ڴ˻�����
//			  	 _link_id : TCP���ӵ�id�� ʶ���Ǿ������ֻ������������ڷ�����
// �� �� ֵ: ���յ������ݳ���. 0 ��ʾ������
// ע������: ��
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
		comSendChar(COM1,ucData);		// �����յ����ݴ�ӡ�����Դ���1

		if (s_flag == 0)
		{
			if (s_len < sizeof(s_buf))
			{
				s_buf[s_len++] = ucData;	// ������յ�������
			}			
			if (ucData == '+')
			{
				s_len = 1;
				s_data_len = 0;
				s_buf[0] = 0;
			}
			if (s_len > 7 && ucData == ':')
			{
				*link_id =(uint8_t)((char)s_buf[5] - '0');		// ����������id
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
				s_buf[s_len++] = ucData;		// ������յ�������
				
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