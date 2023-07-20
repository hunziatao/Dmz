#include "huawei.h"
char RXbuff[2048];                         //接收数据缓冲区
char TXbuff[2048];                         //发送数据缓冲区
char userData[256];    
int  CONNECT_SERVER_PORT = 1883; 
char *MQTT_IP = "f1558ba58d.st1.iotda-device.cn-north-4.myhuaweicloud.com";

void huawei_init(){
	
	huawei_CWMODE();
	ESP8266_ConnectAP("ad","12345678");	// 连接AP
	huawei_login();
	huawei_clientid();
	huawei_address();
	huawei_token();
//	huawei_UpValue();
}




void huawei_CWMODE(void)
{
	printf("\r\n进入透传 -> ");
	do{
		ESP8266_SendAT("AT+CWMODE=1");
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("进入透传\r\n");
}
void huawei_login(void)
{
	char cmd_buf[256];
	
	printf("\r\n正在登录mqtt账号密码 -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"",MQTT_UserName,MQTT_PassWord);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("账号：%s\r\n密码：%s \r\n",MQTT_UserName,MQTT_PassWord);
}

void huawei_clientid(void)
{
	char cmd_buf[256];
	
	printf("\r\n登录mqtt的ClientID -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTCLIENTID=0,\"%s\"",MQTT_ClientID);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("ClientID->%s \r\n",MQTT_ClientID);
}

void huawei_address(void)
{
	char cmd_buf[256];
	
	printf("\r\n连接地址 -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTCONN=0,\"%s\",1883,1",MQTT_IP);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("地址->%s \r\n",MQTT_IP);
}

void huawei_token(void)
{
	char cmd_buf[256];
	
	printf("\r\n正在订阅主题 -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTSUB=0,\"$oc/devices/%s/sys/properties/report\",1",MQTT_UserName);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("订阅主题->%s \r\n",MQTT_ClientID);
}
void huawei_UpNumber(int num)
{
	char cmd_buf[256];
	
	printf("\r\n正在上报整数数据 -> %d\r\n",num);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"direction\\\":%d}}]}\",0,0",MQTT_UserName,num);
//			sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"position\\\":9.666666}}]}\",0,0",MQTT_UserName);
		  ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("设备名->%s \r\n",MQTT_UserName);
}

void huawei_UpNav_flag(int num)
{
	char cmd_buf[256];
	
	printf("\r\n正在上报整数数据 -> %d\r\n",num);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"nav_flag\\\":%d}}]}\",0,0",MQTT_UserName,num);
		  ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("设备名->%s \r\n",MQTT_UserName);
}

void huawei_Up_next_position(int num)
{
	char cmd_buf[256];
	
	printf("\r\n正在上报整数数据 -> %d\r\n",num);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"next_position\\\":%d}}]}\",0,0",MQTT_UserName,num);
//			sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"position\\\":9.666666}}]}\",0,0",MQTT_UserName);
		  ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("设备名->%s \r\n",MQTT_UserName);
}





void huawei_UpFloat(float gps)
{
	char cmd_buf[256];
	
	printf("\r\n正在上报整数数据 -> %f\r\n",gps);
	do{

//			sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"position\\\":%f}}]}\",0,0",MQTT_UserName,gps);
		  ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("设备名->%s \r\n",MQTT_UserName);
}
void huawei_UpDestination(char * destination)//上传目的地
{
	char cmd_buf[256];
	
	printf("\r\n正在上报字符串数据 -> %s\r\n",destination);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"destination\\\":\\\"%s\\\"\\}}]}\",0,0",MQTT_UserName,destination);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("设备名->%s \r\n",MQTT_UserName);
}

void huawei_UpPosition(char * position)//上传当前位置
{
	char cmd_buf[256];
	
	printf("\r\n正在上报字符串数据 -> %s\r\n",position);
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/properties/report\",\"{\\\"services\\\":[{\\\"service_id\\\":\\\"gps\\\"\\,\\\"properties\\\":{\\\"position\\\":\\\"%s\\\"}}]}\",0,0",MQTT_UserName,position);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("设备名->%s \r\n",MQTT_UserName);
}


void huawei_repose(char * request_id)
{
	char cmd_buf[256];
	
	printf("\r\n正在回应 -> ");
	do{
		sprintf(cmd_buf,"AT+MQTTPUB=0,\"$oc/devices/%s/sys/commands/response/request_id=%s\",\"{\\\"response\\\":0}\",0,0",MQTT_UserName,request_id);
		ESP8266_SendAT(cmd_buf);
	}while(ESP8266_WaitResponse("OK", 0, 2000) == 0);
	printf("回应码->%s \r\n",request_id);
}

char * fand_content(char * str,char * str_begin,char * str_end)
{
	char *str1 = NULL;							//AT commnd string pointer
	char *str2 = NULL;  
//	static char userData[256];							//定义数组
	char *pcBegin = NULL;
	char *pcEnd = NULL;
	memset(userData,0,256);
	str1 = str;			//取出串口数据
	str2 = strstr(str1,str_begin);							//取出”filename=“以后的字符串
	if(str2 != NULL)															//对比存在需要的数据							
	{
		pcBegin = strstr(str2, str_begin);				//str2：获取需要以后的数据
		pcEnd = strstr(str2,str_end);							//找到结束符，实际测试不能用换行符，直接查看英文字符吧
		pcBegin += strlen(str_begin);																//补偿”filename=“长度的地址位
		
		if((pcBegin != NULL) && (pcEnd != NULL))		//开始和结束都有对应的字符
		{
			memcpy(userData, pcBegin, (pcEnd-pcBegin));	//从pcBegin地址开始，复制出(pcEnd-pcBegin)个数据
		}			
		
		return userData;							//打印字符串
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








