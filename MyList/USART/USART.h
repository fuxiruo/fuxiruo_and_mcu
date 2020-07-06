#ifndef __USART_H    
#define __USART_H    

#include "stdio.h"
#include "stm32f10x.h" 
/*   
 * ��������USART_GPIO_Config   
 * ����  ������USART�õ���I/O��   
 * ����  ����   
 * ���  ����   
 */   
void USART_GPIO_Config(void) ;

/*   
 * ��������USART_Config()   
 * ����  ������USART�ĸ����������ʼ��   
 * ����  ����   
 * ���  ����   
 */   
void USART_Config(void);

/*   
 * ��������fputc   
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����   
 * ���  ����   
 * ����  ����printf����   
 */   
int fputc(int ch, FILE *f) ;


/*   
 * ��������USART_Get_Data   
 * ����  ���Ӵ����н������ɸ�����
 * ����  ������ȡ���ݸ�������Ż�ȡ���ݵĵ�ַ   
 * ���  ����   
 * ����  ���ɹ�����1��ʧ�ܷ���0   
 */   
int USART_Get_Data(const uint16_t n,uint8_t * s);
#endif /* __USART_H */

