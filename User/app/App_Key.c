#include "Include.h" 

#if 0
//静态
/* 定义线程控制块 */
ALIGN(RT_ALIGN_SIZE)	//RT_ALIGN_SIZE字节对齐
static	rt_uint8_t	rt_appkey_thread_stack[512];
static	struct rt_thread key_thread;

/**
	* @brief 
	* @param 
	* @retval 
*/
rt_err_t task_appkey_creat(rt_uint8_t priority, rt_uint32_t timeslice)
{
	rt_err_t result;
	
	result = rt_thread_init(	&key_thread,
									"key_scanf",
									AppKey_Scanf,
									RT_NULL,
									rt_appkey_thread_stack,
									sizeof(rt_appkey_thread_stack),
									priority,
									timeslice);
									
	if(result == RT_EOK)
	{
		rt_kprintf("Task AppKey Init Success\r\n");
	}
	else
	{
		rt_kprintf("Task AppKey Init Fail\r\n");
	}
	
	result = rt_thread_startup(&key_thread);
	
	if(result == RT_EOK)
	{
		rt_kprintf("Task AppKey Start Success\r\n");
	}
	else
	{
		rt_kprintf("Task AppKey Start Fail\r\n");
	}
	
	return result;
}
#else
//动态
static rt_thread_t key_thread = RT_NULL;
rt_err_t task_appkey_creat(rt_uint8_t priority, rt_uint32_t timeslice)
{
	rt_err_t result = RT_EOK;
	
	key_thread = rt_thread_create(	"key_scanf",
									AppKey_Scanf,
									RT_NULL,
									512,
									priority,
									timeslice);
									
	if(key_thread != RT_NULL)
	{
		rt_kprintf("Task AppKey Init Success\r\n");
		
		result = rt_thread_startup(key_thread);
		
		if(result == RT_EOK)
		{
			rt_kprintf("Task AppKey Start Success\r\n");
		}
		else
		{
			rt_kprintf("Task AppKey Start Fail\r\n");
		}
	}
	else
	{
		rt_kprintf("Task AppKey Init Fail\r\n");
	}
	
	return result;
}
#endif

/**
	* @brief 
	* @param 
	* @retval 
*/
void AppKey_Scanf(void* parameter)
{
	static rt_uint8_t key0val = 0;
	
	while(1)
	{
		if( (!KEY0()) || (!KEY1()) || (!KEY2()) || (!KEY3()) )
		{
			if((++key0val) >= 3)
			{
				key0val = 0;
				
				rt_kprintf("Key Task Run\r\n");
			}
		}
		else
		{
			key0val = 0;
		}
		
		rt_thread_delay(100);
	}
}

