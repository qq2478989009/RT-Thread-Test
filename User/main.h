#ifndef	MAIN_H
#define	MAIN_H

#include <rtdef.h>

/**
	* @brief 
	* @param 
	* @retval 
*/
void McuDrive_Init(void);

/*
 * 使用HSE时，设置系统时钟的步骤
 * 1、开启HSE ，并等待 HSE 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源
 *    设置VCO输入时钟 分频因子        m
 *    设置VCO输出时钟 倍频因子        n
 *    设置PLLCLK时钟分频因子          p
 *    设置OTG FS,SDIO,RNG时钟分频因子 q
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟

 * ulPLLM: VCO输入时钟 分频因子，取值2~63
 * ulPLLN: VCO输出时钟 倍频因子，取值192~432
 * ulPLLP: PLLCLK时钟分频因子  ，取值2，4，6，8
 * ulPLLQ: OTG FS,SDIO,RNG时钟分频因子，取值4~15
 */
void SystemClock_Config(unsigned int ulPLLM, unsigned int ulPLLN, unsigned int ulPLLP, unsigned int ulPLLQ);

/**
	* @brief 
	* @param 
	* @retval 
*/
static rt_err_t Task_Creat(void);


#endif
