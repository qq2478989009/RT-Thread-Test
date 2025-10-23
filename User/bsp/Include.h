#ifndef INCLUDE_H
#define INCLUDE_H



/* 这里需要先自定义，否则会报错 */
typedef unsigned char    uint8;                   /* 无符号8位整型变量  */
typedef signed   char    int8;                   	/* 无符号8位整型变量  */
typedef unsigned short   uint16;                  /* 无符号16位整型变量 */
typedef signed   short   int16;                  	/* 有符号16位整型变量 */
typedef unsigned int     uint32;                  /* 无符号32位整型变量 */ 
typedef signed   int     int32;                  	/* 有符号32位整型变量 */



#include "stm32f4xx.h" 

//标准库
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

