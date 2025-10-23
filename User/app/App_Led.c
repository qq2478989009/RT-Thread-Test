#include "Include.h" 


/* 定义线程控制块 */
ALIGN(RT_ALIGN_SIZE)	//RT_ALIGN_SIZE字节对齐
static	rt_uint8_t	rt_appled_thread_stack[512];
static	struct rt_thread ledfunc_thread;

/**
	* @brief 
	* @param 
	* @retval 
*/
void AppLed_Blokelight(void* parameter)
{
	unsigned int count = 0;
	static	rt_uint8_t direct = 0;
	static	rt_uint8_t	value;
	
	while(1)
	{
		#if 0
		LED0(ON);
		rt_thread_delay(500);
		LED0(OFF);
		rt_thread_delay(500);
		
		LED1(ON);
		rt_thread_delay(500);
		LED1(OFF);
		rt_thread_delay(500);
		
		LED2(ON);
		rt_thread_delay(500);
		LED2(OFF);
		rt_thread_delay(500);
		#else
		if(value & 0x01)				LED0(ON);
		else if((value & 0x01) == 0)	LED0(OFF);
		
		if(value & 0x02)				LED1(ON);
		else if((value & 0x02) == 0)	LED1(OFF);
		
		if(value & 0x04)				LED2(ON);
		else if((value & 0x04) == 0)	LED2(OFF);
		
		if (!direct)
			value = value<<1 | 1; 
		else
			value = value>>1; 

		if (value >= 0x07 || value == 0)
		{
			direct = !direct;
		}

		rt_thread_delay(500);
		#endif
		
		rt_kprintf("Led Task Run Count = %d \r\n", ++count);
	}
}

/**
	* @brief 
	* @param 
	* @retval 
*/
rt_err_t task_appled_creat(rt_uint8_t priority, rt_uint32_t timeslice)
{
	rt_err_t result;
	
	result = rt_thread_init(	&ledfunc_thread,
									"led1",
									AppLed_Blokelight,
									RT_NULL,
									rt_appled_thread_stack,
									sizeof(rt_appled_thread_stack),
									priority,
									timeslice);
									
	if(result == RT_EOK)
	{
		rt_kprintf("Task AppLed Init Success\r\n");
	}
	else
	{
		rt_kprintf("Task AppLed Init Fail\r\n");
	}
	
	result = rt_thread_startup(&ledfunc_thread);
	
	if(result == RT_EOK)
	{
		rt_kprintf("Task AppLed Start Success\r\n");
	}
	else
	{
		rt_kprintf("Task AppLed Start Fail\r\n");
	}
	
	return result;
}


