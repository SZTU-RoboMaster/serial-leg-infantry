#include "../Inc/DJ_Motor.h"
#include "retarget.h"
#include <stdio.h>
#include  "DM_Motor.h"

#define GET_MOTOR_MSG(ptr, handle)\
    do {                                                                \
        (ptr)->last_ecd = (ptr)->ecd;                                   \
        (ptr)->ecd = (uint16_t)handle[0] << 8 | handle[1];              \
        (ptr)->RPM = (uint16_t)handle[2] << 8 | handle[3];              \
        (ptr)->give_current = (uint16_t)handle[4] << 8 | handle[5];     \
        (ptr)->temperature = handle[6];                                  \
    } while (0)

CAN_TxHeaderTypeDef tx_message;
uint8_t send_data[8];
motor_measure_t motor_3508_msg;
uint8_t rx_data[8];

void can_cmd_send(can_type_e can_type, can_id_e can_id, int16_t give_current1, int16_t give_current2)
{
    uint32_t tx_mail_box;

    tx_message.StdId = can_id;
    tx_message.IDE = CAN_ID_STD;
    tx_message.RTR = CAN_RTR_DATA;
    tx_message.DLC = 0x08;
    tx_message.TransmitGlobalTime = DISABLE;

    send_data[0] = give_current1 >> 8;
    send_data[1] = give_current1;
    send_data[2] = give_current2 >> 8;
    send_data[3] = give_current2;
    send_data[4] = 0;
    send_data[5] = 0;
    send_data[6] = 0;
    send_data[7] = 0;

    if (can_type == CAN_1) {
        HAL_CAN_AddTxMessage(&hcan1, &tx_message, send_data, &tx_mail_box);
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
                GET_MOTOR_MSG(&motor_3508_msg, rec_msg);
                break;
            }
            case CAN_REC_MOTOR_0x202: {

                break;
            }
            case CAN_REC_MOTOR_0x203: {

                break;
            }
            case CAN_REC_MOTOR_0x204: {

                break;
            }
            case MOTOR_8009_REC_ID: {

                break;
            }
        }
    }


}
