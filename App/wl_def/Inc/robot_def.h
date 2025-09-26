//
// Created by zw200 on 2025/9/26.
//

#include "pid.h"

#ifndef WL_INFANTRY_ROBOT_DEF_H
#define WL_INFANTRY_ROBOT_DEF_H

/** 变量约束 **/
#define MIN_L0 0.10f

#define MAX_CHASSIS_VX_SPEED 2.1f
#define MAX_WHEEL_TORQUE 10.f
#define MIN_WHEEL_TORQUE (-10.f)
#define MAX_JOINT_TORQUE 40.f
#define MIN_JOINT_TORQUE (-40.f)

/** 遥控器值映射 **/
#define RC_TO_VX  (MAX_CHASSIS_VX_SPEED/660)
#define MAX_CHASSIS_YAW_INCREMENT 0.01f
#define RC_TO_YAW_INCREMENT (MAX_CHASSIS_YAW_INCREMENT/660)


/****** PID参数 ******/

/** Wheel **/

// 转向PID
#define CHASSIS_TURN_POS_PID_P 5.0f
#define CHASSIS_TURN_POS_PID_I 0.0f
#define CHASSIS_TURN_POS_PID_D 0.0f
#define CHASSIS_TURN_POS_PID_IOUT_LIMIT 0.0f
#define CHASSIS_TURN_POS_PID_OUT_LIMIT 3.0f

#define CHASSIS_TURN_SPEED_PID_P 10.0f
#define CHASSIS_TURN_SPEED_PID_I 0.0f
#define CHASSIS_TURN_SPEED_PID_D 0.0f
#define CHASSIS_TURN_SPEED_PID_IOUT_LIMIT 0.0f
#define CHASSIS_TURN_SPEED_PID_OUT_LIMIT 4.0f

/** 底盘模式结构体 **/
typedef enum{
    CHASSIS_DISABLE = 1, // 失能模式
    CHASSIS_INIT, // 初始化模式
    CHASSIS_ENABLE, // 使能模式
    CHASSIS_SPIN, // 小陀螺
    CHASSIS_JUMP, // 跳跃模式
} ChassisCtrlMode;

/** 底盘结构体 **/
typedef struct {

    /** 遥控器信息 **/
    ChassisCtrlMode chassis_ctrl_mode;
    ChassisCtrlMode chassis_last_ctrl_mode;

    /****** PID ******/
    /** Wheel **/

    // 转向PID
    Pid chassis_turn_pos_pid;
    Pid chassis_turn_speed_pid;

    float wheel_turn_torque;          // 转向力矩

}Chassis_t;

extern Chassis_t chassis;

#endif //WL_INFANTRY_ROBOT_DEF_H