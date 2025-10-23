#include "Include.h" 


int main(void)
{ 
	Task_Creat();
}

/**
	* @brief 
	* @param 
	* @retval 
*/
void McuDrive_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 	//����ϵͳ�ж����ȼ�����4
	
	bsp_led_gpio_init();
	
	bsp_beed_gpio_init();
	
	bsp_key_gpio_init();
}

/**
	* @brief 
	* @param 
	* @retval 
*/
static rt_err_t Task_Creat(void)
{
	rt_err_t result;
	
	task_appled_creat(6, 500);
	
	AppTest_CreateTestTask(6, 500);
	
	//task_appkey_creat(6, 200);
	
	
	return result;
}

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
void SystemClock_Config(unsigned int ulPLLM, unsigned int ulPLLN, unsigned int ulPLLP, unsigned int ulPLLQ)
{
	__IO uint32_t HSEStartUpStatus = 0;

	// ʹ��HSE�������ⲿ����
	RCC_HSEConfig(RCC_HSE_ON);

	// �ȴ�HSE�����ȶ�
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus == SUCCESS)
	{
		// ��ѹ����ѹ�����������Ϊ1���Ա�������Ϊ���Ƶ��
		// ����ʱʹ���ܺ͹���ʵ��ƽ��
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_VOS;
		
		// HCLK = SYSCLK / 1
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		
		// PCLK2 = HCLK / 2
		RCC_PCLK2Config(RCC_HCLK_Div2);
		
		// PCLK1 = HCLK / 4
		RCC_PCLK1Config(RCC_HCLK_Div4);
		
		// ���Ҫ��Ƶ�͵�������������
		// ����PLL��Դʱ�ӣ�����VCO��Ƶ����m������VCO��Ƶ����n��
		//  ����ϵͳʱ�ӷ�Ƶ����p������OTG FS,SDIO,RNG��Ƶ����q
		RCC_PLLConfig(RCC_PLLSource_HSE, ulPLLM, ulPLLN, ulPLLP, ulPLLQ);
		
		// ʹ��PLL
		RCC_PLLCmd(ENABLE);

		// �ȴ� PLL�ȶ�
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}   

		/*-----------------------------------------------------*/
		//���� OVER-RIDEģʽ�����ܴﵽ����Ƶ��(F429���иù���)
		//    PWR->CR |= PWR_CR_ODEN;
		//    while((PWR->CSR & PWR_CSR_ODRDY) == 0)
		//    {
		//    }
		//    PWR->CR |= PWR_CR_ODSWEN;
		//    while((PWR->CSR & PWR_CSR_ODSWRDY) == 0)
		//    {
		//    }      
		// ����FLASHԤȡָ,ָ���,���ݻ���͵ȴ�״̬
		FLASH->ACR = FLASH_ACR_PRFTEN 
						| FLASH_ACR_ICEN 
						| FLASH_ACR_DCEN 
						| FLASH_ACR_LATENCY_5WS;
		/*-----------------------------------------------------*/
		
		// ��PLL�ȶ�֮�󣬰�PLLʱ���л�Ϊϵͳʱ��SYSCLK
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		// ��ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
		while (RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
		else
		{
			// HSE����������
			while (1)
			{
			}
		}
}
