#ifndef APP_LED_H
#define APP_LED_H

#include <rtdef.h>

/**
	* @brief 
	* @param 
	* @retval 
*/
void AppLed_Blokelight(void* parameter);

/**
	* @brief 
	* @param 
	* @retval 
*/
rt_err_t task_appled_creat(rt_uint8_t priority, rt_uint32_t timeslice);

#endif
