#include "Include.h" 


//线程测试
#ifdef THREAD_TEST
/* 定义线程控制块 */
ALIGN(RT_ALIGN_SIZE)	//字节对齐
static	rt_uint8_t KeyFunc_Thread_Stack[512];
static	struct rt_thread KeyFunc_Thread;

static	rt_uint8_t	rt_ledtest_thread_stack[512];
static	struct rt_thread ledtest_thread;

/**
	* @brief 
	* @param 
	* @retval 
*/
void AppTest_KeyFunc(void* parameter)
{
	static rt_uint8_t key0val = 0, flag = 0;
	
	while(1)
	{
		if( (!KEY0()) || (!KEY1()) || (!KEY2()) || (!KEY3()) )
		{
			if((++key0val) > 0)
			{
				key0val = 0;
				
				flag ^= 0;
				
				if(0)
				{
					if(rt_thread_suspend(&ledtest_thread) == RT_EOK)
					{
						rt_kprintf("Suspend Led Task Success\r\n");
					}
					else
					{
						rt_kprintf("Suspend Led Task Fail\r\n");
					}
				}
				else
				{
					if(rt_thread_resume(&ledtest_thread) == RT_EOK)
					{
						rt_kprintf("Resume Led Task Success\r\n");
					}
					else
					{
						rt_kprintf("Resume Led Task Fail\r\n");
					}
				}
			}
		}
		else
		{
			key0val = 0;
		}
		
		rt_thread_delay(50);
	}
}

/**
	* @brief 
	* @param 
	* @retval 
*/
rt_err_t AppTest_CreateTestTask(rt_uint8_t priority, rt_uint32_t timeslice)
{
	rt_err_t result;
	
	result = rt_thread_init(&KeyFunc_Thread,
							"TestKeyFunc",
							AppTest_KeyFunc,
							RT_NULL,
							KeyFunc_Thread_Stack,
							sizeof(KeyFunc_Thread_Stack),
							priority,
							timeslice
							);
							
	if(result == RT_EOK)
	{
		rt_kprintf("TestKeyFunc Task Creat Success\r\n");
	}
	else
	{
		rt_kprintf("TestKeyFunc Task Creat Fail\r\n");
	}
	
	result = rt_thread_startup(&KeyFunc_Thread);
	
	if(result == RT_EOK)
	{
		rt_kprintf("TestKeyFunc Task Start Success\r\n");
	}
	else
	{
		rt_kprintf("TestKeyFunc Task Start Fail\r\n");
	}
	
	/*---------------------------------------------------------*/
	result = rt_thread_init(	&ledtest_thread,
								"Led_Test",
								Led_Test,
								RT_NULL,
								rt_ledtest_thread_stack,
								sizeof(rt_ledtest_thread_stack),
								priority,
								timeslice);
									
	if(result == RT_EOK)
	{
		rt_kprintf("Task LedTest Init Success\r\n");
	}
	else
	{
		rt_kprintf("Task LedTest Init Fail\r\n");
	}
	
	result = rt_thread_startup(&ledtest_thread);
	
	if(result == RT_EOK)
	{
		rt_kprintf("Task LedTest Start Success\r\n");
	}
	else
	{
		rt_kprintf("Task LedTest Start Fail\r\n");
	}
	
	return result;
}

/**
	* @brief 
	* @param 
	* @retval 
*/
void Led_Test(void* parameter)
{
	unsigned int count = 0;
	
	while(1)
	{
		LED0(ON);
		rt_thread_delay(1000);
		LED0(OFF);
		rt_thread_delay(1000);
		
		rt_kprintf("Led Task Run Count = %d \r\n", ++count);
	}
}

#endif

/* 消息队列 */
#ifdef MQ_TEST
static	rt_mq_t test_mq = RT_NULL;

ALIGN(RT_ALIGN_SIZE)	//字节对齐
static	rt_uint8_t	MqSend_Stack[256];
static	rt_uint8_t	MqRec_Stack[256];
static	struct	rt_thread	MqSend_Thread;
static	struct	rt_thread	MqRec_Thread;

/**
	* @brief 
	* @param 
	* @retval 
*/
rt_err_t AppTest_CreateTestTask(rt_uint8_t priority, rt_uint32_t timeslice)
{
	rt_err_t result;
	
	test_mq = rt_mq_create("test_mq",
							20,
							5,
							RT_IPC_FLAG_FIFO);
	
	if(test_mq == RT_NULL)
	{
		rt_kprintf("队列创建失败\r\n");
	}
	
	
	
	result = rt_thread_init(&MqSend_Thread,
							"MqSend_Thread",
							AppTest_MqSend,
							RT_NULL,
							MqSend_Stack,
							sizeof(MqSend_Stack),
							priority,
							timeslice);
							
	if(result == RT_EOK)
	{
		rt_kprintf("MqSend_Task Create Success\r\n");
	}
	else
	{
		rt_kprintf("MqSend_Task Create Fail\r\n");
	}
	
	result =  rt_thread_startup(&MqSend_Thread);
	
	if(result == RT_EOK)
	{
		rt_kprintf("MqSend_Task Startup Success\r\n");
	}
	else
	{
		rt_kprintf("MqSend_Task Startup Fail\r\n");
	}
	
	result = rt_thread_init(&MqRec_Thread,
							"AppTest_MqRec",
							AppTest_MqRec,
							RT_NULL,
							MqRec_Stack,
							sizeof(MqRec_Stack),
							priority,
							timeslice);
							
	if(result == RT_EOK)
	{
		rt_kprintf("MqRec_Task Create Success\r\n");
	}
	else
	{
		rt_kprintf("MqRec_Task Create Fail\r\n");
	}
	
	result = rt_thread_startup(&MqRec_Thread);
	
	if(result == RT_EOK)
	{
		rt_kprintf("MqRec_Task Startup Success\r\n");
	}
	else
	{
		rt_kprintf("MqRec_Task Startup Fail\r\n");
	}
	
	return result;
}

/**
	* @brief 
	* @param 
	* @retval 
*/
void AppTest_MqSend(void* parameter)
{
	rt_err_t	retval;
	rt_uint8_t	mq_sendbuff[4] = {0};
	static rt_uint32_t mqval = 0;
	
	while(1)
	{
		if( (!KEY0()) || (!KEY1()) || (!KEY2()) || (!KEY3()) )
		{
			mqval++;
			
			*(rt_int32_t*)(mq_sendbuff) = __rev(mqval);
			
			retval = rt_mq_send(test_mq, mq_sendbuff, sizeof(mq_sendbuff));
			
			if(retval == RT_EOK)
			{
				rt_kprintf("消息队列数据发送成功:%d, %d, %d, %d", mq_sendbuff[0], mq_sendbuff[1], mq_sendbuff[2], mq_sendbuff[3]);
			}
			else
			{
				rt_kprintf("消息队列数据发送失败");
			}
		}
		
		rt_thread_delay(1000);
	}
}

/**
	* @brief 
	* @param 
	* @retval 
*/
void AppTest_MqRec(void* parameter)
{
	rt_uint8_t	mq_recbuff[4] = {0};
	rt_err_t	retval;
	
	while(1)
	{
		retval = rt_mq_recv(test_mq,
							mq_recbuff,
							sizeof(mq_recbuff),
							RT_WAITING_FOREVER);
							
		if(RT_EOK == retval)
		{
			rt_kprintf("消息队列数据接收成功:%d, %d, %d, %d", mq_recbuff[0], mq_recbuff[1], mq_recbuff[2], mq_recbuff[3]);
		}
		else
		{
			rt_kprintf("Mq receive data Faile");
		}
		
		rt_thread_delay(1000);
	}
}

#endif



