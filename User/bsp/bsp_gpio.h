#ifndef BSP_GPIO_H
#define BSP_GPIO_H

enum SWITCH_STAT
{
	ON = 0,
	OFF,
};

/* 带参宏，可以像内联函数一样使用 */
//len define
/****************************************************************************************************/
#define	LED0_PIN		GPIO_Pin_3
#define	LED0_PORT		GPIOE
#define	LED0_CLK		RCC_AHB1Periph_GPIOE

#define	LED1_PIN		GPIO_Pin_4
#define	LED1_PORT		GPIOE
#define	LED1_CLK		RCC_AHB1Periph_GPIOE

#define	LED2_PIN		GPIO_Pin_9
#define	LED2_PORT		GPIOG
#define	LED2_CLK		RCC_AHB1Periph_GPIOG

#define LED0(a)	if (a)	\
					GPIO_SetBits(LED0_PORT,LED0_PIN);\
					else		\
					GPIO_ResetBits(LED0_PORT,LED0_PIN)

#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LED1_PORT,LED1_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_PORT,LED2_PIN);\
					else		\
					GPIO_ResetBits(LED2_PORT,LED2_PIN)
/****************************************************************************************************/

//beed define
/****************************************************************************************************/
#define	BEED_PIN		GPIO_Pin_7
#define	BEED_PORT		GPIOG
#define	BEED_CLK		RCC_AHB1Periph_GPIOG

#define	BEED_ON()		do{	GPIO_SetBits(BEED_PORT,BEED_PIN);	}while(0);
#define	BEED_OFF()		do{	GPIO_ResetBits(BEED_PORT,BEED_PIN); }while(0);
/****************************************************************************************************/

//key define
/****************************************************************************************************/
#define	KEY0_PIN		GPIO_Pin_9
#define	KEY0_PORT		GPIOF
#define	KEY0_CLK		RCC_AHB1Periph_GPIOF

#define	KEY1_PIN		GPIO_Pin_8
#define	KEY1_PORT		GPIOF
#define	KEY1_CLK		RCC_AHB1Periph_GPIOF

#define	KEY2_PIN		GPIO_Pin_7
#define	KEY2_PORT		GPIOF
#define	KEY2_CLK		RCC_AHB1Periph_GPIOF

#define	KEY3_PIN		GPIO_Pin_6
#define	KEY3_PORT		GPIOF
#define	KEY3_CLK		RCC_AHB1Periph_GPIOF

#define	KEY0()			GPIO_ReadInputDataBit(KEY0_PORT,KEY0_PIN)
#define	KEY1()			GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN)
#define	KEY2()			GPIO_ReadInputDataBit(KEY2_PORT,KEY2_PIN)
#define	KEY3()			GPIO_ReadInputDataBit(KEY3_PORT,KEY3_PIN)
/****************************************************************************************************/


/**
	* @brief 
	* @param 
	* @retval 
*/
void bsp_led_gpio_init(void);
					
/**
	* @brief 
	* @param 
	* @retval 
*/
void bsp_beed_gpio_init(void);

/**
	* @brief 
	* @param 
	* @retval 
*/
void bsp_key_gpio_init(void);

#endif

