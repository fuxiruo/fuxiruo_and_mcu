#include "USART.h"      

/*   
 * ��������USART_GPIO_Config   
 * ����  ������USART�õ���I/O��   
 * ����  ����   
 * ���  ����   
 */   
void USART_GPIO_Config(void)    
{           
    /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/   
    GPIO_InitTypeDef GPIO_InitStructure;       
    /*����GPIOA��USART1������ʱ��*/   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
    /*ѡ��Ҫ���Ƶ�GPIOA����*/                                                                  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;        
    /*USARTx_TX����Ҫ����Ϊ���츴�����*/   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         
    /*������������Ϊ50MHz */       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
    /*���ÿ⺯������ʼ��GPIOA*/
		GPIO_Init(GPIOA,&GPIO_InitStructure);  

	 /*ѡ��Ҫ���Ƶ�GPIOA����*/                                                                  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        
    /*USARTx_RX����Ҫ����Ϊ������������������*/   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;         
    /*������������Ϊ50MHz */       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
    /*���ÿ⺯������ʼ��GPIOA*/
		GPIO_Init(GPIOA,&GPIO_InitStructure);  
} 

/*   
 * ��������USART_Config()   
 * ����  ������USART�ĸ����������ʼ��   
 * ����  ����   
 * ���  ����   
 */   
void USART_Config(void) 
{
	USART_InitTypeDef USART_InitStructure;
	//USART_ClockInitTypeDef USART_ClockInitStructure;
  
	/*����������Ϊ19200bps*/
	USART_InitStructure.USART_BaudRate = 19200;
	/*���ݳ���Ϊ8��������żУ��λ*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/*һ��ֹͣλ*/	
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	/*����żУ��λ*/	
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	/*��Ӳ��������*/	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/*���ͺͽ���ʹ��*/		
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	
	/*ͬ��ģʽ�ã�����ʹ���첽ģʽ*/	
	//USART_ClockInitStructure.USART_Clock = USART_Clock_Disable; 
	//USART_ClockInitStructure.USART_CPOL = USART_CPOL_High; 
	//USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge; 
	//USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable; 
	
	USART_Init(USART1, &USART_InitStructure); 
	//USART_ClockInit(USART1, &USART_ClockInitStructure);
	
	/*ʹ��USART1 */ 
	USART_Cmd(USART1, ENABLE); 
}

/*   
 * ��������fputc   
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����   
 * ���  ����   
 * ����  ����printf����   
 */   
int fputc(int ch, FILE *f)    
{    
	USART_ClearFlag(USART1, USART_FLAG_TC); //���������ɱ�־λ,������ܻᶪʧ��1���ֽڵ�����
    /* ��Printf���ݷ������� */   
	USART_SendData(USART1, (unsigned char) ch);    
//  while (!(USART1->SR & USART_FLAG_TXE));    
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);     
    return (ch);    
} 

/*   
 * ��������USART_Get_Data   
 * ����  ���Ӵ����н������ɸ�����
 * ����  ������ȡ���ݸ�������Ż�ȡ���ݵĵ�ַ   
 * ���  ����   
 * ����  ���ɹ�����1��ʧ�ܷ���0   
 */   
int USART_Get_Data(const uint16_t n,uint8_t * s)    
{   
	uint32_t	Timeout1;
	uint16_t tempn;
  for(tempn=0;tempn<n;tempn++)
	{
		Timeout1 = 0;
		while(SET!=USART_GetFlagStatus(USART1,USART_FLAG_RXNE)) 
		{
			/*��ʱ����*/
			if(++Timeout1==0xFFFFFFFF)
			{
					return 0;
			}
		}
		*(s+tempn) = (uint8_t)USART_ReceiveData(USART1);
	}
	return 1;
} 













