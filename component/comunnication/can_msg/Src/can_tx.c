//
// Created by zw200 on 2025/9/21.
//

#include "../Inc/can_tx.h"

#include <stdio.h>

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


