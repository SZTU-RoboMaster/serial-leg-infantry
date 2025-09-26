//
// Created by zw200 on 2025/9/21.
//

#include "../Inc/can_msg.h"
#include "DM_Motor.h"


/**
 * @brief 将数据通过空的邮箱发送出去
 * @param hcan can接口
 * @param ID 设备ID
 * @param pData 数据指针
 * @param Len 数据长度
 * @return
 */
void CANx_SendStdData(CAN_HandleTypeDef *hcan,uint16_t ID,uint8_t *pData,uint16_t Len)
{
    static CAN_TxHeaderTypeDef Tx_Header;

    Tx_Header.StdId=ID;
    Tx_Header.ExtId=0;
    Tx_Header.IDE=0;
    Tx_Header.RTR=0;
    Tx_Header.DLC=Len;


    /*找到空的发送邮箱，把数据发送出去*/
    if(HAL_CAN_AddTxMessage(hcan, &Tx_Header, pData, (uint32_t*)CAN_TX_MAILBOX0) != HAL_OK) //
    {
        if(HAL_CAN_AddTxMessage(hcan, &Tx_Header, pData, (uint32_t*)CAN_TX_MAILBOX1) != HAL_OK)
        {
            HAL_CAN_AddTxMessage(hcan, &Tx_Header, pData, (uint32_t*)CAN_TX_MAILBOX2);
        }
    }
}

/**
 * @brief DJI电机解码
 * @param[in] motor  电机结构体指针
 * @param[in] data   接收到的数据的指针
 */
void DJI_Motor_Decode(DJ_Motor_measure_t *motor, uint8_t *data) {
    motor->last_ecd = motor->ecd;
    /* 转子机械角度 */
    motor->ecd = (uint16_t)(data[0]<<8 | data[1]);
    /* 转子转速 */
    motor->speed_rpm = (int16_t)(data[2]<<8 | data[3]);
    /* 实际扭矩电流 */
    motor->given_current = (int16_t)(data[4]<<8 | data[5]);
    /* 电机温度 */
    motor->temperate = data[6];
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    // printf("7888888888888888888\r\n");
    uint8_t rec_msg[8] = {0};

    CAN_RxHeaderTypeDef rx_header;

    HAL_CAN_GetRxMessage(hcan, CAN_FILTER_FIFO0, &rx_header, rec_msg);

    if (hcan == &hcan1) {
        switch (rx_header.StdId) {
            case CAN_REC_MOTOR_0x201: {
                DJI_Motor_Decode(&motor_3508_msg[LEFT_W], rec_msg);
                break;
            }
            case CAN_REC_MOTOR_0x202: {
                DJI_Motor_Decode(&motor_3508_msg[RIGHT_W], rec_msg);
                break;
            }
            case MOTOR_8009_REC_ID: {

                break;
            }
        }
    }
}


