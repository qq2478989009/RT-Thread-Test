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
 * ʹ��HSEʱ������ϵͳʱ�ӵĲ���
 * 1������HSE �����ȴ� HSE �ȶ�
 * 2������ AHB��APB2��APB1��Ԥ��Ƶ����
 * 3������PLL��ʱ����Դ
 *    ����VCO����ʱ�� ��Ƶ����        m
 *    ����VCO���ʱ�� ��Ƶ����        n
 *    ����PLLCLKʱ�ӷ�Ƶ����          p
 *    ����OTG FS,SDIO,RNGʱ�ӷ�Ƶ���� q
 * 4������PLL�����ȴ�PLL�ȶ�
 * 5����PLLCK�л�Ϊϵͳʱ��SYSCLK
 * 6����ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��

 * ulPLLM: VCO����ʱ�� ��Ƶ���ӣ�ȡֵ2~63
 * ulPLLN: VCO���ʱ�� ��Ƶ���ӣ�ȡֵ192~432
 * ulPLLP: PLLCLKʱ�ӷ�Ƶ����  ��ȡֵ2��4��6��8
 * ulPLLQ: OTG FS,SDIO,RNGʱ�ӷ�Ƶ���ӣ�ȡֵ4~15
 */
void SystemClock_Config(unsigned int ulPLLM, unsigned int ulPLLN, unsigned int ulPLLP, unsigned int ulPLLQ);

/**
	* @brief 
	* @param 
	* @retval 
*/
static rt_err_t Task_Creat(void);


#endif
