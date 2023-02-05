/******************************************************************************
 * @file    test_rig.h
 * @author  Tim Brewis (@t-bre)
 * @brief   Main test rig
 *****************************************************************************/

#ifndef _TEST_RIG_H
#define _TEST_RIG_H

#include "tx_api.h"
#include "can.h"
#include "rtcan.h"

#include "config.h"
#include "can_listener.h"

/**
 * @brief   Test rig state
 */
typedef struct {

    /**
     * @brief   RTCAN instance for CAN-C bus
     */
    rtcan_handle_t rtcan_c;

#if CONFIG_ENABLE_CAN_LISTENER
    /**
     * @brief   CAN listener
     */
    canl_handle_t canl;
#endif

} test_rig_context_t;

/*
 * public functions
 */
void test_rig_init(test_rig_context_t* test_rig_ptr,
                   CAN_HandleTypeDef* can_c_h,
                   CAN_HandleTypeDef* can_s_h,
                   TX_BYTE_POOL* app_mem_pool);

#endif