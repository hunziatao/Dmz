#include "huawei.h"
char RXbuff[2048];                         //�������ݻ�����
char TXbuff[2048];                         //�������ݻ�����
char userData[256];    
int  CONNECT_SERVER_PORT = 1883; 
char *MQTT_IP = "f1558ba58d.st1.iotda-device.cn-north-4.myhuaweicloud.com";

void huawei_init(){
	
	huawei_CWMODE();
	ESP8266_ConnectAP("ad","12345678");	// ����AP
	huawei_login();
	huawei_clientid();
	huawei_address();
	huawei_token();
//	huawei_UpValue();
}




void huawei_CWMODE(void)
{
	printf("\r\n����͸�� -> ");
	do{
		ESP8266_SendAT("AT+CWMODE=1");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("����͸��\r\n");
}
void huawei_login(void)
{
	char cmd_buf[256];
	
	printf("\r\n���ڵ�¼mqtt�˺����� -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"",MQTT_UserName,MQTT_PassWord);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�˺ţ�%s\r\n���룺%s \r\n",MQTT_UserName,MQTT_PassWord);
}

void huawei_clientid(void)
{
	char cmd_buf[256];
	
	printf("\r\n��¼mqtt��ClientID -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTCLIENTID=0,\"%s\"",MQTT_ClientID);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("ClientID->%s \r\n",MQTT_ClientID);
}

void huawei_address(void)
{
	char cmd_buf[256];
	
	printf("\r\n���ӵ�ַ -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTCONN=0,\"%s\",1883,1",MQTT_IP);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("��ַ->%s \r\n",MQTT_IP);
}

void huawei_token(void)
{
	char cmd_buf[256];
	
	printf("\r\n���ڶ������� -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTSUB=0,\"$oc/devices/%s/sys/properties/report\",1",MQTT_UserName);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("��������->%s \r\n",MQTT_ClientID);
}
void huawei_UpNumber(int num)
{
	char cmd_buf[256];
	
	printf("\r\n�����ϱ��������� -> %d\r\n",num);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"direction\\\":%d}}]}\",0,0",MQTT_UserName,num);
//			sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"position\\\":9.666666}}]}\",0,0",MQTT_UserName);
		  ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�豸��->%s \r\n",MQTT_UserName);
}

void huawei_UpNav_flag(int num)
{
	char cmd_buf[256];
	
	printf("\r\n�����ϱ��������� -> %d\r\n",num);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"nav_flag\\\":%d}}]}\",0,0",MQTT_UserName,num);
		  ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�豸��->%s \r\n",MQTT_UserName);
}

void huawei_Up_next_position(int num)
{
	char cmd_buf[256];
	
	printf("\r\n�����ϱ��������� -> %d\r\n",num);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"next_position\\\":%d}}]}\",0,0",MQTT_UserName,num);
//			sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"position\\\":9.666666}}]}\",0,0",MQTT_UserName);
		  ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�豸��->%s \r\n",MQTT_UserName);
}





void huawei_UpFloat(float gps)
{
	char cmd_buf[256];
	
	printf("\r\n�����ϱ��������� -> %f\r\n",gps);
	do{

//			sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"position\\\":%f}}]}\",0,0",MQTT_UserName,gps);
		  ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�豸��->%s \r\n",MQTT_UserName);
}
void huawei_UpDestination(char * destination)//�ϴ�Ŀ�ĵ�
{
	char cmd_buf[256];
	
	printf("\r\n�����ϱ��ַ������� -> %s\r\n",destination);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"destination\\\":\\\"%s\\\"\\}}]}\",0,0",MQTT_UserName,destination);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�豸��->%s \r\n",MQTT_UserName);
}

void huawei_UpPosition(char * position)//�ϴ���ǰλ��
{
	char cmd_buf[256];
	
	printf("\r\n�����ϱ��ַ������� -> %s\r\n",position);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"position\\\":\\\"%s\\\"}}]}\",0,0",MQTT_UserName,position);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("�豸��->%s \r\n",MQTT_UserName);
}


void huawei_repose(char * request_id)
{
	char cmd_buf[256];
	
	printf("\r\n���ڻ�Ӧ -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/commands/response/request_id=%s\",\"{\\\"response\\\":0}\",0,0",MQTT_UserName,request_id);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("��Ӧ��->%s \r\n",request_id);
}

char * fand_content(char * str,char * str_begin,char * str_end)
{
	char *str1 = NULL;							//AT commnd string pointer
	char *str2 = NULL;  
//	static char userData[256];							//��������
	char *pcBegin = NULL;
	char *pcEnd = NULL;
	memset(userData,0,256);
	str1 = str;			//ȡ����������
	str2 = strstr(str1,str_begin);							//ȡ����filename=���Ժ���ַ���
	if(str2 != NULL)															//�Աȴ�����Ҫ������							
	{
		pcBegin = strstr(str2, str_begin);				//str2����ȡ��Ҫ�Ժ������
		pcEnd = strstr(str2,str_end);							//�ҵ���������ʵ�ʲ��Բ����û��з���ֱ�Ӳ鿴Ӣ���ַ���
		pcBegin += strlen(str_begin);																//������filename=�����ȵĵ�ַλ
		
		if((pcBegin != NULL) && (pcEnd != NULL))		//��ʼ�ͽ������ж�Ӧ���ַ�
		{
			memcpy(userData, pcBegin, (pcEnd-pcBegin));	//��pcBegin��ַ��ʼ�����Ƴ�(pcEnd-pcBegin)������
		}			
		
		return userData;							//��ӡ�ַ���
	}
	return 0;		
}

char* uint8_to_hex(uint8_t value) 
{
	static char buf[3];
	static const char* hex_chars = "0123456789ABCDEF";
    buf[0] = hex_chars[(value >> 4) & 0x0F];
    buf[1] = hex_chars[value & 0x0F];
    buf[2] = '\0';
	return buf;
}








