#include "Include.h" 




/***************************************************************************************************
* 函数名称:void bsp_usart1_init(uint32 bounds)
* 入口参数:bounds:串口波特率
* 返 回 值:None
* 功能描述:	  					
*	  Note:		
* 修改记录:	  
***************************************************************************************************/
void bsp_usart1_init(uint32 bounds)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); 
	
	//USART1端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    //USART1 初始化设置
	//波特率设置
	USART_InitStructure.USART_BaudRate = bounds;
	//字长为8位数据格式
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	//一个停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	//无奇偶校验位
	USART_InitStructure.USART_Parity = USART_Parity_No;
	//无硬件数据流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//收发模式
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	USART_Cmd(USART1,  ENABLE); 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);			//清除中断标志位
	USART_ITConfig(USART1,  USART_IT_RXNE, DISABLE);
	
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/***************************************************************************************************
* 函数名称:void bsp_usart1_SendDt(uint8_t* ucpbuff, uint8_t uclen)
* 入口参数:ucpbuff:待发送的数据
			uclen:发送的数据长度
* 返 回 值:None
* 功能描述:	  					
*	  Note:		
* 修改记录:	  
***************************************************************************************************/
void bsp_usart1_SendDt(uint8_t* ucpbuff, uint8_t uclen)
{
	uint8_t i;
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET)
	{}
		
	for(i=0; i<uclen; i++)
	{
		USART_SendData(USART1, (uint8_t)( * (ucpbuff+i) ) );
		
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
	}
}

void USART1_IRQHandler(void)
{
	
}

#if 0
//重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	
	/* 发送一个字节数据到串口 */
	USART_SendData(USART1, (uint8_t) ch);

	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return (ch);
}

//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
	/* 等待串口输入数据 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(USART1);
}
#endif



