#include "USART.h"      

/*   
 * 函数名：USART_GPIO_Config   
 * 描述  ：配置USART用到的I/O口   
 * 输入  ：无   
 * 输出  ：无   
 */   
void USART_GPIO_Config(void)    
{           
    /*定义一个GPIO_InitTypeDef类型的结构体*/   
    GPIO_InitTypeDef GPIO_InitStructure;       
    /*开启GPIOA和USART1的外设时钟*/   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
    /*选择要控制的GPIOA引脚*/                                                                  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;        
    /*USARTx_TX引脚要设置为推挽复用输出*/   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         
    /*设置引脚速率为50MHz */       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
    /*调用库函数，初始化GPIOA*/
		GPIO_Init(GPIOA,&GPIO_InitStructure);  

	 /*选择要控制的GPIOA引脚*/                                                                  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        
    /*USARTx_RX引脚要设置为浮空输入或带上拉输入*/   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;         
    /*设置引脚速率为50MHz */       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
    /*调用库函数，初始化GPIOA*/
		GPIO_Init(GPIOA,&GPIO_InitStructure);  
} 

/*   
 * 函数名：USART_Config()   
 * 描述  ：配置USART的各项参数并初始化   
 * 输入  ：无   
 * 输出  ：无   
 */   
void USART_Config(void) 
{
	USART_InitTypeDef USART_InitStructure;
	//USART_ClockInitTypeDef USART_ClockInitStructure;
  
	/*波特率设置为19200bps*/
	USART_InitStructure.USART_BaudRate = 19200;
	/*数据长度为8，包含奇偶校验位*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/*一个停止位*/	
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	/*无奇偶校验位*/	
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	/*无硬件流控制*/	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/*发送和接收使能*/		
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	
	/*同步模式用，这里使用异步模式*/	
	//USART_ClockInitStructure.USART_Clock = USART_Clock_Disable; 
	//USART_ClockInitStructure.USART_CPOL = USART_CPOL_High; 
	//USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge; 
	//USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable; 
	
	USART_Init(USART1, &USART_InitStructure); 
	//USART_ClockInit(USART1, &USART_ClockInitStructure);
	
	/*使能USART1 */ 
	USART_Cmd(USART1, ENABLE); 
}

/*   
 * 函数名：fputc   
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无   
 * 输出  ：无   
 * 调用  ：由printf调用   
 */   
int fputc(int ch, FILE *f)    
{    
	USART_ClearFlag(USART1, USART_FLAG_TC); //清除传输完成标志位,否则可能会丢失第1个字节的数据
    /* 将Printf内容发往串口 */   
	USART_SendData(USART1, (unsigned char) ch);    
//  while (!(USART1->SR & USART_FLAG_TXE));    
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);     
    return (ch);    
} 

/*   
 * 函数名：USART_Get_Data   
 * 描述  ：从串口中接收若干个数据
 * 输入  ：待获取数据个数，存放获取数据的地址   
 * 输出  ：无   
 * 返回  ：成功返回1，失败返回0   
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
			/*超时控制*/
			if(++Timeout1==0xFFFFFFFF)
			{
					return 0;
			}
		}
		*(s+tempn) = (uint8_t)USART_ReceiveData(USART1);
	}
	return 1;
} 













