#include "../Inc/DJ_Motor.h"
#include "retarget.h"
#include <stdio.h>
#include  "DM_Motor.h"

CAN_TxHeaderTypeDef tx_message;
uint8_t send_data[8];
uint8_t rx_data[8];

void can_cmd_send(can_type_e can_type, can_id_e can_id, int16_t left_motor, int16_t right_motor)
{
    uint32_t tx_mail_box;

    tx_message.StdId = can_id;
    tx_message.IDE = CAN_ID_STD;
    tx_message.RTR = CAN_RTR_DATA;
    tx_message.DLC = 0x08;
    tx_message.TransmitGlobalTime = DISABLE;

    send_data[0] = left_motor >> 8;
    send_data[1] = left_motor;
    send_data[2] = right_motor >> 8;
    send_data[3] = right_motor;
    send_data[4] = 0;
    send_data[5] = 0;
    send_data[6] = 0;
    send_data[7] = 0;

    if (can_type == CAN_1) {
        HAL_CAN_AddTxMessage(&hcan1, &tx_message, send_data, &tx_mail_box);
    }
}

