//
// Created by zw200 on 2025/9/26.
//

#include "chassis_task.h"

void ChassisTask(void *argument) {

    while (1) {
        can_cmd_send(CAN_1, CAN_MOTOR_0x200, 1000, 1000);
        osDelay(1);
    }
}
