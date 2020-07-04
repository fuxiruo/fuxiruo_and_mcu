#ifndef __DELAYER_H
#define __DELAYER_H 

#include "stm32f4xx_hal.h"

typedef enum
{
    E_DELAYER_SINGLE        = 0,        //single
    E_DELAYER_LOOP,                     //loop
}E_DELAYER_TYPE;

typedef enum{
    E_DELAYER_NOT_START     = 0,
    E_DELAYER_NOT_TIMEOUT,
    E_DELAYER_TIMEOUT,
}E_DELAYER_STATUS;

typedef struct{
    uint32_t bEnable;
    uint32_t nTimeout;  
    uint32_t nTimeoutTick;
    E_DELAYER_TYPE eType;
}ST_DELAYER;

void SetDelayer(ST_DELAYER *delayer, uint32_t nTimeout, E_DELAYER_TYPE eType);
E_DELAYER_STATUS CheckTimeout(ST_DELAYER *delayer);//1-not start��0-not timeout��1-timeout

#endif /* __DELAYER_H */


