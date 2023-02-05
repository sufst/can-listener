/******************************************************************************
 * @file    test_rig.h
 * @author  Tim Brewis (@t-bre)
 * @brief   Main test rig
 *****************************************************************************/

#ifndef _TEST_RIG_H
#define _TEST_RIG_H

#include <stdint.h>

#include "tx_api.h"
#include "can.h"
#include "rtcan.h"

#include "config.h"
#include "can_listener.h"

#define RTCAN1  (CONFIG_LISTEN_TO_CAN1)
#define RTCAN2  (CONFIG_LISTEN_TO_CAN2)
#define RTCAN3  (CONFIG_LISTEN_TO_CAN3)

/**
 * @brief   Test rig state
 */
typedef struct {

#if RTCAN1
    rtcan_handle_t rtcan1;
#endif

#if RTCAN2
    rtcan_handle_t rtcan2;
#endif

#if RTCAN3
    rtcan_handle_t rtcan3;
#endif

#if CONFIG_ENABLE_CAN_LISTENER
#if CONFIG_LISTEN_TO_CAN1
    canl_handle_t canl1;
#endif
#if CONFIG_LISTEN_TO_CAN2
    canl_handle_t canl1;
#endif
#if CONFIG_LISTEN_TO_CAN3
    canl_handle_t canl1;
#endif
#endif

} test_rig_context_t;

/*
 * public functions
 */
void test_rig_init(test_rig_context_t* test_rig_ptr,
                   CAN_HandleTypeDef* can1_h,
                   CAN_HandleTypeDef* can2_h,
                   CAN_HandleTypeDef* can3_h,
                   TX_BYTE_POOL* app_mem_pool);

void test_rig_handle_can_tx_mailbox_callback(test_rig_context_t* test_rig_ptr,
                                             CAN_HandleTypeDef* can_h);

void test_rig_handle_can_rx_it(test_rig_context_t* test_rig_ptr,
                               CAN_HandleTypeDef* can_h,
                               uint32_t rx_fifo);

#endif