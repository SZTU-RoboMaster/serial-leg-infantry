//
// Created by zw200 on 2025/9/25.
//

#ifndef WL_INFANTRY_BSP_RC_H
#define WL_INFANTRY_BSP_RC_H

#include "main.h"
#include "usart.h"

extern DMA_HandleTypeDef hdma_usart3_rx;

void RC_Init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num);
void RC_unable(void);
void RC_restart(uint16_t dma_buf_num);

#endif //WL_INFANTRY_BSP_RC_H