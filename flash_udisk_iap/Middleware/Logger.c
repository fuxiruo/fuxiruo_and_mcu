#include "Logger.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

extern UART_HandleTypeDef huart1;
static uint8_t sPrintBuf[1024];
void CPrintfToLog(char *fmt, ...){
	va_list body;
	va_start(body, fmt);
	vsnprintf(sPrintBuf, sizeof(sPrintBuf), fmt, body);
	va_end(body);

	HAL_UART_Transmit(&huart1, sPrintBuf, strlen(sPrintBuf)+1, 10000);
}

