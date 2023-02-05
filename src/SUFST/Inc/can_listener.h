/******************************************************************************
 * @file   canl.h
 * @author Tim Brewis (@t-bre)
 * @brief  CAN listener
 ******************************************************************************/

#ifndef _CAN_LISTENER_H
#define _CAN_LISTENER_H

#include "can.h"
#include "tx_api.h"
#include <stdbool.h>
#include <stdint.h>

#include "config.h"
#include "rtcan.h"

#define CANL_RX_QUEUE_LENGTH    20

//==============================================================================

/**
 * @brief   CAN listener context
 */
typedef struct {
    
    /**
     * @brief   Thread
     */
    TX_THREAD thread;

    /**
     * @brief   RTCAN handle
     */
    rtcan_handle_t* rtcan_h;

    /**
     * @brief   RTCAN message queue
     */
    TX_QUEUE can_rx_queue;

    /**
     * @brief   RTCAN message queue memory
     */
    rtcan_msg_t* can_rx_queue_mem[CANL_RX_QUEUE_LENGTH];

} canl_handle_t;

//==============================================================================

void canl_init(canl_handle_t* canl_h,
               rtcan_handle_t* rtcan_h,
               const uint32_t* can_ids,
               const uint32_t num_can_ids,
               TX_BYTE_POOL* app_mem_pool);

#endif