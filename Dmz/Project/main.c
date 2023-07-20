
//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include "system.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "hc_sr04.h"
#include "usart_fifo.h"
#include "wifi.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "huawei.h"
#include "TPaway.h"

//-----------------------------------------------------------------

uint8_t wifi_flag;	//wifi���յ�����
uint8_t gps_flag;	//gps���յ�����
uint8_t Voice_flag;	//�������յ�����

uint8_t start_gps_flag;	//����gps��ȡʵʱλ�õı�־λ
uint8_t start_compare;	//����ʵʱλ�ú���һ��λ�õı�־λ

uint8_t tcpid;	
uint8_t cmd_len;
uint8_t ucData;
char direction[1];

char next_position[256];

char Chinese_hex[256];

char gps_position[40];

char* repose;

float hc_sr04_front;
float hc_sr04_lift;
float hc_sr04_right;

double gps_gete;
double gps_getn;

double gps_gete_next;
double gps_getn_next;

void com4_function()
{
	while(comGetChar(COM4, &ucData))
		{
			char temp[1];
//			comSendChar(COM1,ucData);
			sprintf(temp,"%c",ucData);
			strcat(RXbuff,temp);
			gps_flag=1;
		}
		if(gps_flag)
		{
			if(strstr(RXbuff,"$GNRMC"))
			{
				
				double gps_gete_temp = atof(fand_content((char *)RXbuff,(char *)"N,",(char *)",E"));			//E:114.124637,N:32.156606
				
				double gps_getn_temp = atof(fand_content((char *)RXbuff,(char *)"000,A,",(char *)",N,"));
				
				
				if(100 < gps_getn_temp && gps_getn_temp < 18000){
					int a =  (int)(gps_getn_temp/100.0);            //��ȡ
					double b= (gps_getn_temp - a*100)/60.0;
					gps_getn = a+b;
					printf("overn ====== %f\r\n",gps_getn);
					int c =  (int)(gps_gete_temp/100.0);
					double d= (gps_gete_temp - c*100)/60.0;
					gps_gete = c+d;
					printf("overe ====== %f\r\n",gps_gete);

				}
							
				memset(RXbuff,0,2048);

			}
			gps_flag=0;
		}
}

//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
int main(void)
{
	wifi_flag=0;
	start_gps_flag =0;
	start_compare = 0;
	
	CPU_CACHE_Enable();			// ����CPU����
    HAL_Init();          		// ��ʼ��HAL��
	MPU_Memory_Protection();// ���ñ�������
	SystemClock_Config(); 	// ����ϵͳʱ��,400Mhz  
	
	SysTick_clkconfig(400);	// SysTick��������
	TIM2_Init(1000-1,2000-1);// ��ʱ��3��ʼ������ʱ��ʱ��Ϊ200M����Ƶϵ��Ϊ20000-1��
	
	gpio_init();	
	WIFI_GPIO_Init();				// WIFI���ų�ʼ��
	uart_init();						// ���ڳ�ʼ��
	delay_ms(2000);
	printf("\r\n���ڸ�ESP8266ģ���ϵ�...\r\n");
	ESP8266_PowerOn();
	printf("\r\n�ϵ���ɣ�Ĭ�ϲ�����: 115200bsp\r\n");
	ESP8266_AT();							// ATӦ�����					
	ESP8266_EchoOff();				// �رջ���
	ESP8266_AT_RST();					// ��λ
	delay_ms(1000);	
	ESP8266_EchoOff();				// �رջ���
	huawei_init();
	comSendBuf(COM1,(uint8_t*)"COM3_start\r\n",14);//����1����
	comSendBuf(COM1,(uint8_t*)"COM4_start\r\n",14);
	comSendBuf(COM1,(uint8_t*)"COM5_start\r\n",14);
	delay_ms(1000);
	
	
	huawei_UpNav_flag(0);
	delay_ms(100);
	huawei_Up_next_position(0);


	while(1)
	{
		
		while(comGetChar(COM_ESP8266, &ucData))//+MQTTSUBRECV:0,"$oc/devices/6485b83fec46a256bca613cf_esp8266_iot/sys/commands/request_id=b33394c0-a8e5-4aaf-84fd-534a466a0c60",73,{"paras":{"position":	},"service_id":"gps","command_name":null}
		{
			char temp[1];
//			comSendChar(COM1,ucData);		// �����յ����ݴ�ӡ�����Դ���1
			sprintf(temp,"%c",ucData);
			strcat(RXbuff,temp);
			wifi_flag=1;
		}
		if(wifi_flag)
			
		{
			if(strstr(RXbuff,"request_id"))
				{
					printf("wifi���ڽ��գ�%s",RXbuff);
					if(strstr(RXbuff,"next_position"))
					{
						sprintf(next_position,"%s",fand_content((char *)RXbuff,(char *)"next_position\":",(char *)"}"));
						
						printf("next_position�ص��ģ�%s\r\n",(char *)next_position);
						
						gps_gete_next = atof(fand_content((char *)next_position,(char *)"\"",(char *)","));
						printf("gps_gete_next�ص���E��%lf\r\n",gps_gete_next);
						
						gps_getn_next = atof(fand_content((char *)next_position,(char *)",",(char *)"\""));
						printf("gps_getn_next�ص���N��%lf\r\n",gps_getn_next);
						
						memset(next_position,0,256);
						
						
						
						

					}
					if(strstr(RXbuff,"direction"))
					{
						memset(direction,0,1);
						sprintf(direction,"%s",fand_content((char *)RXbuff,(char *)"\"direction\":",(char *)"},\""));
						printf("direction�ص��ģ�%s\r\n",direction);
						start_compare=1;
						
					}
					repose = fand_content((char *)RXbuff,(char *)"request_id=",(char *)"\",");
					printf("��ȡ���ģ�%s",(char *)repose);
					huawei_repose(repose);
					wifi_flag=0;
					memset(RXbuff,0,2048);
				}
			else
			{
				printf("wifi���ڽ��գ�%s",RXbuff);
				wifi_flag=0;
				memset(RXbuff,0,2048);
			}
		}
		
		delay_ms(100);


		
		
		
		
		
		while(comGetChar(COM5, &ucData))
		{
			char temp[1];
			if(ucData!=13)
			{
				if(ucData!=10)
				{
					sprintf(temp,"%c",ucData);
					strcat(RXbuff,temp);
					
					strcat(Chinese_hex,uint8_to_hex(ucData));
				}
				
			}
			Voice_flag=1;
			
		}
		if(Voice_flag)
		{
			if(strstr(RXbuff,"sleep"))
			{
				printf("%s",RXbuff);
				memset(RXbuff,0,2048);
				Voice_flag=0;
				memset(Chinese_hex,0,256);
			}
			else if(strstr(RXbuff,"��ȥ"))
			{
				printf("����ȥ���գ�%s",RXbuff);
				
				//-------------------------------------
				com4_function();
				char temp1[20];
				memset(gps_position,0,40);
				sprintf(temp1,"%.6f/",gps_gete);
				strcat(gps_position,temp1);               //�ϴ����ڵ�λ��
				
				printf("����λ��gps_gete��%.6f\r\n",gps_gete);
				sprintf(temp1,"%.6f",gps_getn);
				strcat(gps_position,temp1);
				
				printf("����λ��gps_getn��%.6f\r\n",gps_getn);
				printf("����λ�ã�%s\r\n",gps_position);
				
				huawei_UpPosition(gps_position);
				delay_ms(100);
				memset(gps_position,0,40);
				
				//-------------------------------------
				
				printf("Ŀ�ĵض�����%s\r\n",Chinese_hex);
				
				huawei_UpDestination(Chinese_hex);            //�ϴ�Ŀ�ĵ�
				delay_ms(100);
				memset(Chinese_hex,0,256);
				huawei_UpNav_flag(1);
				delay_ms(200);
				huawei_Up_next_position(1);
				delay_ms(100);
				memset(RXbuff,0,2048);
				Voice_flag=0;
			}
			else if(strstr(RXbuff,"ֹͣ"))
			{
				printf("ֹͣ�������գ�%s",RXbuff);
				huawei_UpNav_flag(0);
				delay_ms(100);				
				comSendBuf(COM5,(uint8_t*)"�����Ѿ�����",40);
				memset(RXbuff,0,2048);
				Voice_flag=0;
				memset(Chinese_hex,0,256);
			}
			else
			{
				printf("���գ�%s\r\n",RXbuff);
				memset(RXbuff,0,2048);
				Voice_flag=0;
				memset(Chinese_hex,0,256);
			}
			
		}
		com4_function();
		if(start_compare)
		{
			double distance = haversine(gps_getn, gps_gete, gps_getn_next, gps_gete_next);
			if(distance<5.0)
			{
				printf("\r\n=====%c====\r\n",direction[0]);
				if(direction[0]=='0')
				{
					comSendBuf(COM5,(uint8_t*)"cmd0",8);
					delay_ms(100);
					huawei_UpNav_flag(0);
					delay_ms(100);
					huawei_Up_next_position(0);
					delay_ms(100);
					
//					start_gps_flag=0;
					
					start_compare=0;
					
					
				}
				if(direction[0]=='1')
				{
					comSendBuf(COM5,(uint8_t*)"cmd1",8);
					delay_ms(100);
					huawei_Up_next_position(1);
					delay_ms(100);
					start_compare=0;
				}
				if(direction[0]=='2')
				{
					comSendBuf(COM5,(uint8_t*)"cmd2",8);
					delay_ms(100);
					huawei_Up_next_position(1);
					delay_ms(100);
					start_compare=0;
				}
				if(direction[0]=='3')
				{
					comSendBuf(COM5,(uint8_t*)"cmd3",8);
					delay_ms(100);
					huawei_Up_next_position(1);
					delay_ms(100);
					start_compare=0;
				}
				if(direction[0]=='4')
				{
					comSendBuf(COM5,(uint8_t*)"cmd4",8);
					delay_ms(100);
					huawei_Up_next_position(1);
					delay_ms(100);
					start_compare=0;
				}
				if(direction[0]=='5')
				{
					comSendBuf(COM5,(uint8_t*)"cmd5",8);
					delay_ms(100);
					huawei_Up_next_position(1);
					delay_ms(100);
					start_compare=0;
				}
				
			}
			
			
		}
		
		
//		printf("lengh_frond:%f\r\n",hc_sr04(front));//��ȡ����
		hc_sr04_function();
		
		
	}//while��
}

//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
