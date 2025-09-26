//
// Created by zw200 on 2025/9/21.
//

#ifndef M3508_CAN_TX_H
#define M3508_CAN_TX_H

#include "stm32f4xx_hal.h"
#include "can.h"
#include "stm32f4xx_hal_can.h"
#include "retarget.h"
#include "DJ_Motor.h"
#include "DM_Motor.h"
#include <stdio.h>
#include "wheel_config.h"


typedef enum {
    CAN_1 = 0,
    CAN_2 = 1
}can_type_e;

typedef enum {
    // 发送标志位
    CAN_MOTOR_0x200 = 0x200,
    CAN_MOTOR_0x1FF = 0x1FF,

    // 接收标志位
    CAN_REC_MOTOR_0x201 = 0X201,
    CAN_REC_MOTOR_0x202 = 0X202,
}can_id_e;

void CANx_SendStdData(CAN_HandleTypeDef *hcan,uint16_t ID,uint8_t *pData,uint16_t Len);

#endif //M3508_CAN_TX_H