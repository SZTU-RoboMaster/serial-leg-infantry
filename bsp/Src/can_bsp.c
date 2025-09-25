#include "can_bsp.h"

void can_filter_init(void)
{
    // printf("2222222\r\n");
    CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    can_filter_st.FilterBank = 0;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    if (HAL_CAN_ConfigFilter(&hcan1, &can_filter_st) == HAL_OK) {
       printf("Filter Config OK!\r\n");
    }
    HAL_CAN_Start(&hcan1);
    if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) == HAL_OK) {
        printf("Active successfully!\r\n");
    }
}

