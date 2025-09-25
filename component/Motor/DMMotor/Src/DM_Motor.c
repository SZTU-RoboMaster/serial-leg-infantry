#include "DM_Motor.h"

// 存储电机信息
DM_Motor_t dm8009;
DM_Motor_t dm4310;

// 更新每个达妙电机的模式信息, 用调试助手查看
dm_motor_mode_e DM8009_mode = DM_SPEED_MODE;
dm_motor_mode_e DM4310_mode = DM_SPEED_MODE;

uint8_t DM_Enable_CMD[CMD_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC};
uint8_t DM_Disable_CMD[CMD_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD};
uint8_t DM_Save_ZeroPoint_CMD[CMD_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE};
uint8_t DM_Clear_Error_CMD[CMD_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB};

static int fp32_to_uint(fp32 x, fp32 x_min, fp32 x_max, int bits);
static fp32 uint_to_fp32(int x_int, fp32 x_min, fp32 x_max, int bits);


void DM_Save_Zero(uint16_t id) {
    CANx_SendStdData(&hcan1, id, DM_Save_ZeroPoint_CMD, CMD_LEN);
}

void DM_Enable(uint16_t id) {
    CANx_SendStdData(&hcan1, id, DM_Enable_CMD, CMD_LEN);
}

void DM_Disable(uint16_t id) {
    CANx_SendStdData(&hcan1, id, DM_Disable_CMD, CMD_LEN);
}

void DM_Clear_err(uint16_t id) {
    CANx_SendStdData(&hcan1, id, DM_Disable_CMD, CMD_LEN);
}

void DM_motor_init(void) {
    dm8009.dm_motor_mode = DM8009_mode;
    dm8009.DM_Motor_id = MOTOR_8009_ID + DM8009_mode;
    dm8009.DM_Motor_rec_id = MOTOR_8009_REC_ID;

    dm4310.dm_motor_mode = DM4310_mode;
    dm4310.DM_Motor_id = MOTOR_4310_ID + DM4310_mode;
    dm4310.DM_Motor_rec_id = MOTOR_4310_REC_ID;

    DM_Enable(dm8009.DM_Motor_id);
    DM_Enable(dm4310.DM_Motor_id);
    // printf("%x\r\n", dm8009.DM_Motor_id);
}

void DM_mit_ctrl(can_type_e can_type, uint16_t motor_id, float pos, float vel,float KP, float KD, float torq)
{
    static uint8_t data[8];
    uint16_t pos_tmp, vel_tmp, torq_tmp, kp_tmp, kd_tmp;

    pos_tmp = fp32_to_uint(pos, P_MIN, P_MAX, 16);
    vel_tmp = fp32_to_uint(vel, V_MIN, V_MAX, 12);
    torq_tmp = fp32_to_uint(torq, T_MIN, T_MAX, 12);
    kp_tmp = fp32_to_uint(KP, KP_MIN, KP_MAX, 12);
    kd_tmp = fp32_to_uint(KD, KD_MIN, KD_MAX, 12);

    data[0] = (pos_tmp >> 8);
    data[1] = pos_tmp;
    data[2] = (vel_tmp >> 4);
    data[3] = ((vel_tmp&0x0F)<<4)|(kp_tmp>>8);
    data[4] = kp_tmp;
    data[5] = (kd_tmp >> 4);
    data[6] = ((kd_tmp & 0xF) << 4) | (torq_tmp >> 8);
    data[7] = torq_tmp;

    if (can_type == CAN_1) {
        CANx_SendStdData(&hcan1, motor_id, data, CMD_LEN);
    }

}

void DM_spd_ctrl(can_type_e can_type,uint16_t id, float vel)
{
    uint8_t *vbuf;
    uint8_t data[4];
    vbuf = (uint8_t*)&vel;

    data[0] = *vbuf;
    data[1] = *(vbuf+1);
    data[2] = *(vbuf+2);
    data[3] = *(vbuf+3);

    if (can_type == CAN_1) {
        CANx_SendStdData(&hcan1, id, data, 4);
        // printf("id : %x data : %x %x %x %x\r\n", id, data[0], data[1], data[2], data[3]);
    } else {
        // CANx_SendStdData(&hcan2, motor_id, data, 4);
    }
}


int fp32_to_uint(fp32 x, fp32 x_min, fp32 x_max, int bits) {
    fp32 span = x_max - x_min;
    fp32 offset = x_min;
    return (int)((x - offset)*((fp32)((1 << bits) - 1)) / span);
}

fp32 uint_to_fp32(int x_int, fp32 x_min, fp32 x_max, int bits) {
    fp32 span = x_max - x_min;
    fp32 offset = x_min;
    return ((fp32)x_int) * span / ((fp32)((1 << bits) - 1)) + offset;
}


void DM_Motor_Decode(DM_Motor_t *motor, const uint8_t *data)
{
    // if (hcan == &hcan1) {
    //     if (HAL_CAN_GetRxMessage(&hcan1, CAN_FILTER_FIFO0, &motor->Rx_pHeader, motor->RxData) == HAL_OK)//获取数据
    //     {
            if (motor->Rx_pHeader.StdId == MOTOR_8009_REC_ID) {
                motor->isInit = data[0] & 0xF0;

               // 如果对应ID下的电机处于失能状态，发送使能命令
               //  if(motor->isInit == 0) {
               //      CANx_SendStdData(&hcan1, MOTOR_8009_REC_ID, DM_Enable_CMD, DM_DATA_LENGTH);
               // }
                motor->p_int = (data[1] << 8) | data[2];
                motor->v_int = (data[3] << 4) | (data[4] >> 4);
                motor->t_int = ((data[4] & 0xF) << 8) | data[5];

                motor->position = uint_to_fp32(motor->p_int, P_MIN, P_MAX, 16);
                motor->velocity = uint_to_fp32(motor->v_int, V_MIN, V_MAX, 12);
                motor->torque = uint_to_fp32(motor->t_int, T_MIN, T_MAX, 12);

//                detect_handle(DETECT_LEFT_GIMBAL_PITCH);
                // HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);    //激活CAN中断通知
            }
    //     }
    // }
}