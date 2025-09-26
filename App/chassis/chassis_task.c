//
// Created by zw200 on 2025/9/26.
//

#include "chassis_task.h"

void ChassisTask(void *argument) {

    wheel_pid_init();

    while (1) {
        // can_cmd_send(CAN_1, CAN_MOTOR_0x200, 400, 400);
        osDelay(1);
    }
}
