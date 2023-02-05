/******************************************************************************
 * @file   canl.c
 * @author Tim Brewis (@t-bre)
 * @brief  CAN listener
 ******************************************************************************/

#include "can_listener.h"

#include <stdio.h>
#include <stdbool.h>

#define ADD_ERROR_IF(cond, err, inst) if(cond) { add_error(inst, err); }

/*
 * internal functions
 */
static bool no_errors(canl_handle_t* canl_h);
static void add_error(canl_handle_t* canl_h, uint32_t err);

//==============================================================================

/**
 * @brief       Initialises CANL instance
 * 
 * @param[in]   canl_h  CANL handle
 * @param[in]   can_h   CAN handle to listen to
 */
void canl_init(canl_handle_t* canl_h, CAN_HandleTypeDef* can_h)
{
    canl_h->can_h = can_h;

    HAL_StatusTypeDef status = HAL_CAN_Start(canl_h->can_h);
    ADD_ERROR_IF(status != HAL_OK, CANL_ERROR_HAL, canl_h);

    if (no_errors(canl_h))
    {
        const uint32_t notifs = CAN_IT_RX_FIFO0_MSG_PENDING
                                | CAN_IT_RX_FIFO1_MSG_PENDING;
        status = HAL_CAN_ActivateNotification(canl_h->can_h, notifs);
        ADD_ERROR_IF(status != HAL_OK, CANL_ERROR_HAL, canl_h);
    }
}

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
void canl_rx_it_handler(canl_handle_t* canl_h, uint32_t rx_fifo)
{
    // get any pending messages and print them
    if (no_errors(canl_h))
    {
        for (uint32_t fifo = 0; fifo < 2; fifo++)
        {
            while(HAL_CAN_GetRxFifoFillLevel(canl_h->can_h, fifo) > 0)
            {
                HAL_StatusTypeDef status;
                status = HAL_CAN_GetRxMessage(canl_h->can_h, 
                                              fifo,
                                              &canl_h->rx_message.header,
                                              canl_h->rx_message.data);

                ADD_ERROR_IF(status != HAL_OK, CANL_ERROR_HAL, canl_h);

                if (no_errors(canl_h))
                {
                    printf("Tick:    %lu\r\n", HAL_GetTick());
                    printf("ID:      0x%lx\r\n", canl_h->rx_message.header.StdId);
                    printf("Length:  %lu\r\n", canl_h->rx_message.header.DLC);
                    printf("Data:    0x");
                    
                    for (uint32_t i = 0; i < canl_h->rx_message.header.DLC; i++)
                    {
                        printf("%02x", canl_h->rx_message.data[i]);
                    }

                    printf("\r\n\n");
                }
            }
        }
    }

    // notify user of error and stop
    if (!no_errors(canl_h))
    {
        printf("Error (%08lx)\r\nStopping.\r\n", canl_h->err);
        while(1);
    }
}

//==============================================================================

/**
 * @brief       Returns true if there have been no errors
 * 
 * @param[in]   canl_h  CANL handle
 */
static bool no_errors(canl_handle_t* canl_h)
{
    return (canl_h->err == CANL_ERROR_NONE);
}

/**
 * @brief       Adds an error
 * 
 * @param[in]   canl_h  CANL handle
 * @param[in]   err     Error to add
 */
static void add_error(canl_handle_t* canl_h, uint32_t err)
{
    canl_h->err |= err;
}