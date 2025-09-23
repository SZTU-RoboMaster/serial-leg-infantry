#ifndef M3508_CAN_BSP_H
#define M3508_CAN_BSP_H

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "retarget.h"
#include "can.h"

void can_filter_init(void);

#endif //M3508_CAN_BSP_H