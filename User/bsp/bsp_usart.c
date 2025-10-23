#include "Include.h" 




/***************************************************************************************************
* ��������:void bsp_usart1_init(uint32 bounds)
* ��ڲ���:bounds:���ڲ�����
* �� �� ֵ:None
* ��������:	  					
*	  Note:		
* �޸ļ�¼:	  
***************************************************************************************************/
void bsp_usart1_init(uint32 bounds)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); 
	
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    //USART1 ��ʼ������
	//����������
	USART_InitStructure.USART_BaudRate = bounds;
	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	//һ��ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	//����żУ��λ
	USART_InitStructure.USART_Parity = USART_Parity_No;
	//��Ӳ������������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//�շ�ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	USART_Cmd(USART1,  ENABLE); 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);			//����жϱ�־λ
	USART_ITConfig(USART1,  USART_IT_RXNE, DISABLE);
	
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/***************************************************************************************************
* ��������:void bsp_usart1_SendDt(uint8_t* ucpbuff, uint8_t uclen)
* ��ڲ���:ucpbuff:�����͵�����
			uclen:���͵����ݳ���
* �� �� ֵ:None
* ��������:	  					
*	  Note:		
* �޸ļ�¼:	  
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
//�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
	/* �ȴ�������� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	
	/* ����һ���ֽ����ݵ����� */
	USART_SendData(USART1, (uint8_t) ch);

	/* �ȴ�������� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return (ch);
}

//�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
	/* �ȴ������������� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(USART1);
}
#endif



