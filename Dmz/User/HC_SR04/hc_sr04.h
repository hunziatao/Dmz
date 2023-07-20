#ifndef _HC_SR04_H
#define _HC_SR04_H

#include "stdio.h"
#include "system.h"
#include "delay.h"
#include "time.h"
#include "usart_fifo.h"

#define TRIG_GPIO_Port   GPIOC
#define TRIG_Pin_F   GPIO_PIN_0
#define ECHO_Pin_F   GPIO_PIN_1

#define TRIG_Pin_L   GPIO_PIN_2
#define ECHO_Pin_L   GPIO_PIN_3

#define TRIG_Pin_R   GPIO_PIN_4
#define ECHO_Pin_R   GPIO_PIN_5

#define front   1
#define right   2
#define lift    3

 

extern int cont;
void gpio_init(void);
float hc_sr04(int direction);
void hc_sr04_function(void);



#endif

