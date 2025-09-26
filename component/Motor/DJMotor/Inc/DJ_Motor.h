//
// Created by zw200 on 2025/9/19.
//

#ifndef M3508_MOTOR_CAN_TX_RX_H
#define M3508_MOTOR_CAN_TX_RX_H

#include "bsp_can.h"
#include "retarget.h"
#include "can.h"
#include <stdio.h>
#include "can_msg.h"

// 轮毂电机反馈信息结构体
typedef struct {
    uint16_t ecd;
    uint16_t last_ecd;
    int16_t RPM;
    int16_t give_current;
    uint8_t temperature;
}motor_measure_t;

extern motor_measure_t motor_3508_msg[2];
extern uint8_t rx_data[8];

void can_cmd_send(can_type_e can_type, can_id_e can_id, int16_t give_current1, int16_t give_current2);

#endif //M3508_MOTOR_CAN_TX_RX_H