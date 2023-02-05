/******************************************************************************
 * @file    test_rig.c
 * @author  Tim Brewis (@t-bre)
 *****************************************************************************/

#include "test_rig.h"

/**
 * @brief       Initialise test rig(s)
 * 
 * @param[in]   test_rig_ptr    Test rig instance
 * @param[in]   can_c_h         CAN-C handle
 * @param[in]   can_s_h         CAN-S handle
 * @param[in]   app_mem_pool    Application memory pool
 */
void test_rig_init(test_rig_context_t* test_rig_ptr,
                   CAN_HandleTypeDef* can_c_h,
                   CAN_HandleTypeDef* can_s_h,
                   TX_BYTE_POOL* app_mem_pool)
{
    rtcan_init(&test_rig_ptr->rtcan_c, 
               can_c_h, 
               CONFIG_RTCAN_C_PRIORITY, 
               app_mem_pool);


#if CONFIG_ENABLE_CAN_LISTENER
    uint32_t listen_ids[] = CONFIG_CANC_LISTEN_IDS;
    uint32_t num_listen_ids = sizeof(listen_ids) / sizeof(listen_ids[0]);

    canl_init(&test_rig_ptr->canl,
              &test_rig_ptr->rtcan_c,
              listen_ids,
              num_listen_ids,
              app_mem_pool);
#endif

    rtcan_start(&test_rig_ptr->rtcan_c);
}

/**
 * @brief       Handles CAN transmit mailbox callback, passing on to RTCAN
 * 
 * @param[in]   test_rig_ptr    Test rig instance
 * @param[in]   can_h           CAN handle
 */
void test_rig_handle_can_tx_mailbox_callback(test_rig_context_t* test_rig_ptr,
                                             CAN_HandleTypeDef* can_h)
{
    rtcan_handle_tx_mailbox_callback(&test_rig_ptr->rtcan_c, can_h);
}

/**
 * @brief       Handles CAN receive interrupt 
 * 
 * @param[in]   test_rig_ptr    Test rig instance
 * @param[in]   can_h           CAN handle
 * @param[in]   rx_fifo         Rx FIFO number
 */
void test_rig_handle_can_rx_it(test_rig_context_t* test_rig_ptr,
                               CAN_HandleTypeDef* can_h,
                               uint32_t rx_fifo)
{
    rtcan_handle_rx_it(&test_rig_ptr->rtcan_c, can_h, rx_fifo);
}
