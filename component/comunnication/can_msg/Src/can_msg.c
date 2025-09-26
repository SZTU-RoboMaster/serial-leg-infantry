//
// Created by zw200 on 2025/9/21.
//

#include "../Inc/can_msg.h"


#define GET_DJ_MOTOR_MSG(ptr, handle)\
do {                                                                \
    (ptr)->last_ecd = (ptr)->ecd;                                   \
    (ptr)->ecd = (uint16_t)handle[0] << 8 | handle[1];              \
    (ptr)->RPM = (uint16_t)handle[2] << 8 | handle[3];              \
    (ptr)->give_current = (uint16_t)handle[4] << 8 | handle[5];     \
    (ptr)->temperature = handle[6];                                  \
    } while (0)

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
    printf("%x\r\n", ID);
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

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    // printf("7888888888888888888\r\n");
    uint8_t rec_msg[8] = {0};

    CAN_RxHeaderTypeDef rx_header;

    HAL_CAN_GetRxMessage(hcan, CAN_FILTER_FIFO0, &rx_header, rec_msg);

    if (hcan == &hcan1) {
        switch (rx_header.StdId) {
            case CAN_REC_MOTOR_0x201: {
                GET_DJ_MOTOR_MSG(&motor_3508_msg[LEFT_W], rec_msg);
                break;
            }
            case CAN_REC_MOTOR_0x202: {
                GET_DJ_MOTOR_MSG(&motor_3508_msg[RIGHT_W], rec_msg);
                break;
            }
            case MOTOR_8009_REC_ID: {

                break;
            }
        }
    }
}


