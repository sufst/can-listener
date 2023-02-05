/******************************************************************************
 * @file    test_rig.c
 * @author  Tim Brewis (@t-bre)
 *****************************************************************************/

#include "test_rig.h"

/**
 * @brief       Initialise test rig(s)
 * 
 *              TODO: lots of code duplication here, can possibly be neatened!
 * 
 * @param[in]   test_rig_ptr    Test rig instance
 * @param[in]   can_c_h         CAN-C handle
 * @param[in]   can_s_h         CAN-S handle
 * @param[in]   app_mem_pool    Application memory pool
 */
void test_rig_init(test_rig_context_t* test_rig_ptr,
                   CAN_HandleTypeDef* can1_h,
                   CAN_HandleTypeDef* can2_h,
                   CAN_HandleTypeDef* can3_h,
                   TX_BYTE_POOL* app_mem_pool)
{
#if RTCAN1
    rtcan_init(&test_rig_ptr->rtcan1, 
               can1_h, 
               CONFIG_RTCAN1_PRIORITY, 
               app_mem_pool);
#endif
#if RTCAN2
    rtcan_init(&test_rig_ptr->rtcan2, 
               can2_h, 
               CONFIG_RTCAN2_PRIORITY, 
               app_mem_pool);
#endif
#if RTCAN3
    rtcan_init(&test_rig_ptr->rtcan3, 
               can3_h, 
               CONFIG_RTCAN3_PRIORITY, 
               app_mem_pool);
#endif

    // setup printf mutex
    tx_mutex_create(&test_rig_ptr->printf_mutex,
                    "printf() mutex",
                    TX_INHERIT);

#if CONFIG_ENABLE_CAN_LISTENER
#if CONFIG_LISTEN_TO_CAN1
    {
        uint32_t listen_ids[] = CONFIG_CAN1_LISTEN_IDS;
        uint32_t num_listen_ids = sizeof(listen_ids) / sizeof(listen_ids[0]);

        canl_init(&test_rig_ptr->canl1,
                &test_rig_ptr->rtcan1,
                CONFIG_CAN1_NAME,
                listen_ids,
                num_listen_ids,
                app_mem_pool,
                &test_rig_ptr->printf_mutex);
    }
#endif
#if CONFIG_LISTEN_TO_CAN2
    {
        uint32_t listen_ids[] = CONFIG_CAN2_LISTEN_IDS;
        uint32_t num_listen_ids = sizeof(listen_ids) / sizeof(listen_ids[0]);

        canl_init(&test_rig_ptr->canl2,
                &test_rig_ptr->rtcan2,
                CONFIG_CAN2_NAME,
                listen_ids,
                num_listen_ids,
                app_mem_pool,
                &test_rig_ptr->printf_mutex);
    }
#endif
#if CONFIG_LISTEN_TO_CAN3
    {
        uint32_t listen_ids[] = CONFIG_CAN3_LISTEN_IDS;
        uint32_t num_listen_ids = sizeof(listen_ids) / sizeof(listen_ids[0]);

        canl_init(&test_rig_ptr->canl3,
                &test_rig_ptr->rtcan3,
                CONFIG_CAN3_NAME,
                listen_ids,
                num_listen_ids,
                app_mem_pool,
                &test_rig_ptr->printf_mutex);
    }
#endif
#endif

#if RTCAN1
    rtcan_start(&test_rig_ptr->rtcan1);
#endif
#if RTCAN2
    rtcan_start(&test_rig_ptr->rtcan1);
#endif
#if RTCAN3
    rtcan_start(&test_rig_ptr->rtcan1);
#endif
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
#if RTCAN1
    rtcan_handle_tx_mailbox_callback(&test_rig_ptr->rtcan1, can_h);
#endif
#if RTCAN2
    rtcan_handle_tx_mailbox_callback(&test_rig_ptr->rtcan2, can_h);
#endif
#if RTCAN3
    rtcan_handle_tx_mailbox_callback(&test_rig_ptr->rtcan3, can_h);
#endif
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
#if RTCAN1
    rtcan_handle_rx_it(&test_rig_ptr->rtcan1, can_h, rx_fifo);
#endif
#if RTCAN2
    rtcan_handle_rx_it(&test_rig_ptr->rtcan2, can_h, rx_fifo);
#endif
#if RTCAN3
    rtcan_handle_rx_it(&test_rig_ptr->rtcan3, can_h, rx_fifo);
#endif
}
