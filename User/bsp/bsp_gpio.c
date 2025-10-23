#include "Include.h"


/**
	* @brief 
	* @param 
	* @retval 
*/
void bsp_led_gpio_init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(LED0_CLK | LED1_CLK | LED2_CLK, ENABLE);

	//PG13、PG14和PG15初始化设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;             //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                   //上拉
	
	GPIO_InitStructure.GPIO_Pin = LED0_PIN;         
	GPIO_Init(LED0_PORT, &GPIO_InitStructure);                     //初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;         
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);                     //初始化GPIO

	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_PORT, &GPIO_InitStructure); 
	
	LED0(OFF);
	LED1(OFF);
	LED2(OFF);
}

/**
	* @brief 
	* @param 
	* @retval 
*/
void bsp_beed_gpio_init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(BEED_CLK, ENABLE);  

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;             //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                   //上拉
	
	GPIO_InitStructure.GPIO_Pin = BEED_PIN;
	GPIO_Init(BEED_PORT, &GPIO_InitStructure);
	
	BEED_OFF();
}

/**
	* @brief 
	* @param 
	* @retval 
*/
void bsp_key_gpio_init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(KEY0_CLK | KEY1_CLK | KEY2_CLK | KEY3_CLK, ENABLE);  

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                  //普通输出模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;              //上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;             //100MHz
	
	GPIO_InitStructure.GPIO_Pin = KEY0_PIN;
	GPIO_Init(KEY0_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY3_PIN;
	GPIO_Init(KEY3_PORT, &GPIO_InitStructure);
}






