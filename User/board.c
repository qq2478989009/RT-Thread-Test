/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-24                  the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "Include.h" 

#define	rt_kprintf_init(x)	do{	bsp_usart1_init(x);	}while(0);

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */
#define RT_HEAP_SIZE (15*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];

RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

void rt_os_tick_callback(void)
{
    rt_interrupt_enter();
    
    rt_tick_increase();

    rt_interrupt_leave();
}

/**
 * This function will initial your board.
 */
void rt_hw_board_init(void)
{
//#error "TODO 1: OS Tick Configuration."
    /* 
     * TODO 1: OS Tick Configuration
     * Enable the hardware timer and call the rt_os_tick_callback function
     * periodically with the frequency RT_TICK_PER_SECOND. 
     */

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
	//系统时钟初始化，系统时钟（SYSCLK）168M,HCLK(AHB)=SYSCLK,PCLK2(APB2)=HCLK/2=84,PCLK1(APB1)=HCLK/4=42
	//8 / 8 * 336 / 2 = 168
	SystemClock_Config(8, 336, 2, 7);   
	
	SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );	
	
	rt_kprintf_init(115200);
	
	McuDrive_Init();
	
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

#ifdef RT_USING_CONSOLE

static int uart_init(void)
{
//#error "TODO 2: Enable the hardware uart and config baudrate."
    return 0;
}
INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
//#error "TODO 3: Output the string 'str' through the uart."
	/* 进入临界段 */
    rt_enter_critical();

	/* 直到字符串结束 */
    while (*str!='\0')
	{
		/* 换行 */
        if (*str=='\n')
		{
			USART_SendData(USART1, '\r'); 
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		}

		USART_SendData(USART1, *str++); 				
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
	}	

	/* 退出临界段 */
    rt_exit_critical();
}
#endif

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	rt_os_tick_callback();
}




