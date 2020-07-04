/******************************************************************************
 * Delayer.c - Input the information of file:
 * 
 * Copyright (c) 2014-2099  KO
 * 
 * DESCRIPTION: - 
 *     Input the description of file:
 * Author: FuDongQiang@2020/07/04
 * 
 * modification history
 *   ...
 ******************************************************************************/

#include "Delayer.h"

void SetDelayer(ST_DELAYER *delayer, uint32_t nTimeout, E_DELAYER_TYPE eType){
    delayer->bEnable = 1;
    delayer->nTimeout = nTimeout;
    delayer->nTimeoutTick = HAL_GetTick();
    delayer->nTimeoutTick += nTimeout;
    delayer->eType = eType;
}

/******************************************************************************
 * FUNCTION: CheckTimeout ( )
 * DESCRIPTION: 
 *    Input the description of function: 
 * Input Parameters: 
 * Output Parameters: 
 * Returns Value: 1-not start��0-not timeout��1-timeout
 * 
 * Author: FuDongQiang @ 2020/07/04
 * 
 * modification history
 *   ...
 ******************************************************************************/
E_DELAYER_STATUS CheckTimeout(ST_DELAYER *delayer){
    if(delayer->bEnable < 1){
        return E_DELAYER_NOT_START;
    }

    if(HAL_GetTick() >= delayer->nTimeoutTick){
        if(E_DELAYER_LOOP == delayer->eType){
            SetDelayer(delayer, delayer->nTimeout, delayer->eType);//reset delayer
        }
        
        return E_DELAYER_TIMEOUT;
    }else{
        return E_DELAYER_NOT_TIMEOUT;
    }
}

