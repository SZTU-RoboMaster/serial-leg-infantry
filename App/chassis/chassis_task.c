//
// Created by zw200 on 2025/9/26.
//

#include "chassis_task.h"

static void chassis_pid_init() {
    /** Wheel **/

    // 转向PID
    pid_init(&chassis.chassis_turn_pos_pid,
             CHASSIS_TURN_POS_PID_OUT_LIMIT,
             CHASSIS_TURN_POS_PID_IOUT_LIMIT,
             CHASSIS_TURN_POS_PID_P,
             CHASSIS_TURN_POS_PID_I,
             CHASSIS_TURN_POS_PID_D);

    pid_init(&chassis.chassis_turn_speed_pid,
             CHASSIS_TURN_SPEED_PID_OUT_LIMIT,
             CHASSIS_TURN_SPEED_PID_IOUT_LIMIT,
             CHASSIS_TURN_SPEED_PID_P,
             CHASSIS_TURN_SPEED_PID_I,
             CHASSIS_TURN_SPEED_PID_D);
}

void ChassisTask(void *argument) {

    chassis_pid_init();

    while (1) {
        // can_cmd_send(CAN_1, CAN_MOTOR_0x200, 400, 400);
        osDelay(1);
    }
}
