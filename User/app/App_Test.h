#ifndef APP_TEST_H
#define	APP_TEST_H

#include <rtdef.h>

//#define THREAD_TEST
#define	MQ_TEST

#ifdef THREAD_TEST
/**
	* @brief 
	* @param 
	* @retval 
*/
void AppTest_KeyFunc(void* parameter);

/**
	* @brief 
	* @param 
	* @retval 
*/
rt_err_t AppTest_CreateTestTask(rt_uint8_t priority, rt_uint32_t timeslice);

/**
	* @brief 
	* @param 
	* @retval 
*/
void Led_Test(void* parameter);


#endif

#ifdef MQ_TEST

/**
	* @brief 
	* @param 
	* @retval 
*/
rt_err_t AppTest_CreateTestTask(rt_uint8_t priority, rt_uint32_t timeslice);

/**
	* @brief 
	* @param 
	* @retval 
*/
void AppTest_MqSend(void* parameter);

/**
	* @brief 
	* @param 
	* @retval 
*/
void AppTest_MqRec(void* parameter);

#endif



#endif
