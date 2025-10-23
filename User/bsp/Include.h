#ifndef INCLUDE_H
#define INCLUDE_H



/* ������Ҫ���Զ��壬����ᱨ�� */
typedef unsigned char    uint8;                   /* �޷���8λ���ͱ���  */
typedef signed   char    int8;                   	/* �޷���8λ���ͱ���  */
typedef unsigned short   uint16;                  /* �޷���16λ���ͱ��� */
typedef signed   short   int16;                  	/* �з���16λ���ͱ��� */
typedef unsigned int     uint32;                  /* �޷���32λ���ͱ��� */ 
typedef signed   int     int32;                  	/* �з���32λ���ͱ��� */



#include "stm32f4xx.h" 

//��׼��
#include <stdio.h>
#include <string.h>

//bsp
#include "bsp_gpio.h"
#include "bsp_usart.h"
#include "bsp_delay.h"
#include "main.h"

//app
#include "App_Led.h"
#include "App_Key.h"
#include "App_Test.h"


//RTOS
//#define	FreeRTOS
#define	RT_Thread

#ifdef FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

#else
#include <rtthread.h>


#endif





#endif

