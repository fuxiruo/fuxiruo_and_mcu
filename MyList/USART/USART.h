#ifndef __USART_H    
#define __USART_H    

#include "stdio.h"
#include "stm32f10x.h" 
/*   
 * 函数名：USART_GPIO_Config   
 * 描述  ：配置USART用到的I/O口   
 * 输入  ：无   
 * 输出  ：无   
 */   
void USART_GPIO_Config(void) ;

/*   
 * 函数名：USART_Config()   
 * 描述  ：配置USART的各项参数并初始化   
 * 输入  ：无   
 * 输出  ：无   
 */   
void USART_Config(void);

/*   
 * 函数名：fputc   
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无   
 * 输出  ：无   
 * 调用  ：由printf调用   
 */   
int fputc(int ch, FILE *f) ;


/*   
 * 函数名：USART_Get_Data   
 * 描述  ：从串口中接收若干个数据
 * 输入  ：待获取数据个数，存放获取数据的地址   
 * 输出  ：无   
 * 返回  ：成功返回1，失败返回0   
 */   
int USART_Get_Data(const uint16_t n,uint8_t * s);
#endif /* __USART_H */

