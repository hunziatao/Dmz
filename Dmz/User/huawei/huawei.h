#ifndef _HUAWEI_H
#define _HUAWEI_H

#include "stdio.h"       
#include "stdarg.h"		
#include "string.h"  
#include "wifi.h"
#include "usart_fifo.h"
#include "delay.h"


//��Ϊ���������������豸��Ϣ
#define MQTT_ClientID "6485b83fec46a256bca613cf_esp8266_iot_0_0_2023061308"
#define MQTT_UserName "6485b83fec46a256bca613cf_esp8266_iot"
#define MQTT_PassWord "b940aefd241cc2d0234b02a74e6a75e6c9b7dd7a7ed75d28bae61b711664bd3b"

//�����뷢��������
#define SET_TOPIC  "$oc/devices/6485b83fec46a256bca613cf_esp8266_iot_0_0_2023061308/sys/messages/down"  //����
#define POST_TOPIC "$oc/devices/6485b83fec46a256bca613cf_esp8266_iot_0_0_2023061308/sys/properties/report"  //����



extern char *CONNECT_SERVER_IP;       
extern int  CONNECT_SERVER_PORT;       
extern char RXbuff[2048];     
extern char TXbuff[2048];     
void huawei_init(void);
void huawei_CWMODE(void);
void huawei_login(void);
void huawei_clientid(void);
void huawei_address(void);
void huawei_token(void);
void huawei_UpNumber(int num);
void huawei_UpNav_flag(int num);
void huawei_Up_next_position(int num);

void huawei_UpFloat(float gps);

void huawei_UpDestination(char * destination);
void huawei_UpPosition(char * position);


void huawei_repose(char * request_id);
char* fand_content(char * str,char * str_begin,char * str_end);

char* uint8_to_hex(uint8_t value);
#endif

