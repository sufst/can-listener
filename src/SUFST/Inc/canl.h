/******************************************************************************
 * @file   canl.h
 * @author Tim Brewis (@t-bre, tab1g19@soton.ac.uk)
 * @brief  CAN listener (CANL)
 ******************************************************************************/

#ifndef CANL_H
#define CANL_H

#include "can.h"
#include <stdbool.h>
#include <stdint.h>

//==============================================================================

#define CANL_ERROR_NONE 0x00000000U // no error
#define CANL_ERROR_HAL  0x00000001U // HAL error

//==============================================================================

/**
 * @brief   CAN listener context
 */
typedef struct {
    
    /**
     * @brief   CAN handle to listen to
     */
    CAN_HandleTypeDef* can_h;
    
    /**
     * @brief   Receive interrupt flag
     */
    volatile bool it_flag;

    /**
     * @brief   
     */

    /**
     * @brief   Memory for received message
     */
    struct {
        CAN_RxHeaderTypeDef header;
        uint8_t data[8];
    } rx_message;

    /**
     * @brief   Error code
     */
    uint32_t err;

} canl_handle_t;

//==============================================================================

void canl_init(canl_handle_t* canl_h, CAN_HandleTypeDef* can_h);
void canl_tick(canl_handle_t* canl_h);


//==============================================================================

/**
 * @brief       Receive interrupt handler
 * 
 * @details     This needs to be called in:
 *              - HAL_CAN_RxFifo0MsgPendingCallback
 *              - HAL_CAN_RxFifo1MsgPendingCallback
 * 
 *              ... only if the callback is passed the same CAN handle as that
 *              of the CANL instance
 * 
 * @param[in]   canl_h      CANL handle
 * @param[in]   rx_fifo     Receive fifo number
 */
static inline void canl_rx_it_handler(canl_handle_t* canl_h, uint32_t rx_fifo)
{
    UNUSED(rx_fifo); // could be useful in future?
    canl_h->it_flag = true;
}

#endif