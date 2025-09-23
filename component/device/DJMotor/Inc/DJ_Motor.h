//
// Created by zw200 on 2025/9/19.
//

#ifndef M3508_MOTOR_CAN_TX_RX_H
#define M3508_MOTOR_CAN_TX_RX_H

#include "can_bsp.h"
#include "retarget.h"
#include "can.h"
#include <stdio.h>

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
    CAN_REC_MOTOR_0x203 = 0X203,
    CAN_REC_MOTOR_0x204 = 0X204,


}can_id_e;

typedef struct {
    uint16_t ecd;
    uint16_t last_ecd;
    int16_t RPM;
    int16_t give_current;
    uint8_t temperature;
}motor_measure_t;

extern motor_measure_t motor_3508_msg;
extern uint8_t rx_data[8];

void can_cmd_send(can_type_e can_type, can_id_e can_id, int16_t give_current);

#endif //M3508_MOTOR_CAN_TX_RX_H