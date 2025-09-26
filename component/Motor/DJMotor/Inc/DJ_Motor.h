//
// Created by zw200 on 2025/9/19.
//

#ifndef M3508_MOTOR_CAN_TX_RX_H
#define M3508_MOTOR_CAN_TX_RX_H

#include "bsp_can.h"
#include "can_msg.h"

// 轮毂电机反馈信息结构体
typedef struct {
    /* 实际电机反馈数据 */
    int16_t last_ecd;       //上一次的电机编码器计数值
    uint16_t ecd;           //转子机械角度, 电机编码器计数值
    int16_t speed_rpm;      //转子转速, 电机转速（每分钟转数，RPM）
    int16_t given_current;  //实际扭矩电流
    uint8_t temperate;      //电机温度
}DJ_Motor_measure_t;

extern DJ_Motor_measure_t motor_3508_msg[2];
extern uint8_t rx_data[8];

void can_cmd_send(can_type_e can_type, can_id_e can_id, int16_t give_current1, int16_t give_current2);

#endif //M3508_MOTOR_CAN_TX_RX_H