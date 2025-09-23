//
// Created by zw200 on 2025/9/21.
//

#ifndef M3508_CAN_TX_H
#define M3508_CAN_TX_H

#include "stm32f4xx_hal.h"
#include "can.h"
#include "stm32f4xx_hal_can.h"
#include <string.h>
#include "retarget.h"

void CANx_SendStdData(CAN_HandleTypeDef *hcan,uint16_t ID,uint8_t *pData,uint16_t Len);

#endif //M3508_CAN_TX_H