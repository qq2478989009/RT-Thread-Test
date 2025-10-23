#include "Include.h" 



/**
 * @brief soft delay N * 1ms
 * @param u16 ms
 * @return NONE
 * @note System Clock: 72MHz
 */
void delay_nms(uint16 ms)
{
    uint16 i = 0;
	
    while(ms--)
    {
        i = 8000;
        while(i--) ;
    }
}









