//
// Created by zw200 on 2025/9/19.
//

#ifndef M3508_DMMOTOR_CAN_TX_RX_H
#define M3508_DMMOTOR_CAN_TX_RX_H

#include "can_msg.h"
#include "DJ_Motor.h"
#include <string.h>
#include "retarget.h"
#include <stdio.h>
#include "struct_typedef.h"
#include "can_msg.h"

#define CMD_LEN  8
#define P_MIN (-12.5)
#define P_MAX 12.5
#define V_MIN (-45)
#define V_MAX 45
#define KP_MIN 0.0f
#define KP_MAX 500.0f
#define KD_MIN 0.0f
#define KD_MAX 5.0f
#define T_MIN (-54)
#define T_MAX 54


//1.MIT 2.位置速度 3.速度
typedef enum {
    DM_MIT_MODE = 0x000,
    DM_POS_SPEED_MODE = 0x100,
    DM_SPEED_MODE = 0x200
}dm_motor_mode_e;

typedef enum {
    // 发送ID
    MOTOR_4310_ID = 0x01,
    MOTOR_8009_ID = 0x03,

    // 接收ID
    MOTOR_4310_REC_ID = 0x11,
    MOTOR_8009_REC_ID = 0x13,

}DM_Motor_id_e;

typedef struct {
    int                  p_int;                             // 整型编码值
    int                  v_int;                             // 整型速度值
    int                  t_int;                             // 整型扭矩值
    fp32                 position;                          // 位置值
    fp32                 velocity;                          // 速度值
    uint8_t              Tx_Data[8];					    // 数据发送存储
    fp32                 torque;                            // 扭矩值
    // uint8_t              RxData[8];						    // 数据接收存储
    uint8_t              isInit;                             // 电机是否初始化
    fp32                 kp;                                // 位置比例系数
    fp32                 kd;                                // 位置微分系数
    CAN_RxHeaderTypeDef Rx_pHeader;
    dm_motor_mode_e     dm_motor_mode;                     // 电机模式,调试助手更改调试
    uint16_t            DM_Motor_id;                           // 电机ID
    uint16_t            DM_Motor_rec_id;                     //接收报文信息
}DM_Motor_t;


extern DM_Motor_t dm8009;
extern DM_Motor_t dm4310;
extern dm_motor_mode_e DM8009_mode;
extern dm_motor_mode_e DM4310_mode;

// 口令: 使能, 使能, 保存零位, 清除错误
extern uint8_t DM_Enable_CMD[CMD_LEN];
extern uint8_t DM_Disable_CMD[CMD_LEN];
extern uint8_t DM_Save_ZeroPoint_CMD[CMD_LEN];
extern uint8_t DM_Clear_Error_CMD[CMD_LEN];

void DM_Save_Zero(uint16_t id);
void DM_Enable(uint16_t id);
void DM_Disable(uint16_t id);
void DM_Clear_err(uint16_t id);

void DM_motor_init(void);
void DM_mit_ctrl(can_type_e can_type, uint16_t motor_id, float pos, float vel,float KP, float KD, float torq);
void DM_spd_ctrl(can_type_e can_type, uint16_t motor_id, float vel);
void DM_Motor_Decode(DM_Motor_t *motor, const uint8_t *data);

#endif //M3508_DMMOTOR_CAN_TX_RX_H