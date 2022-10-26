/******************************************************************************
 * @file   canl.c
 * @author Tim Brewis (@t-bre, tab1g19@soton.ac.uk)
 ******************************************************************************/

#include "canl.h"

#include "can.h"
#include <stdio.h>

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
    canl_h->it_flag = false;
}

/**
 * @brief       CANL loop task
 * 
 * @details     Call this repeatedly in main() to run the listener
 * 
 *              This will busy wait until a message is received, so don't try
 *              and run any other tasks
 * 
* @param[in]   canl_h  CANL handle
 */
void canl_tick(canl_handle_t* canl_h)
{
    HAL_StatusTypeDef status;

    // enable CAN interrupt notifications
    static uint32_t notifs [] = {
        CAN_IT_RX_FIFO0_MSG_PENDING, CAN_IT_RX_FIFO1_MSG_PENDING
    };

    static const uint32_t num_rx_fifos = sizeof(notifs) / sizeof(notifs[0]);

    for (uint32_t i = 0; i < num_rx_fifos; i++)
    {
        if (no_errors(canl_h))
        {
            status = HAL_CAN_ActivateNotification(canl_h->can_h, notifs[i]);
            ADD_ERROR_IF(status != HAL_OK, CANL_ERROR_HAL, canl_h);
        }
    }

    // wait for an interrupt
    while (!canl_h->it_flag)
        ;

    // get any pending messages and print them
    if (no_errors(canl_h))
    {
        for (uint32_t fifo = 0; fifo < num_rx_fifos; fifo++)
        {
            while(HAL_CAN_GetRxFifoFillLevel(canl_h->can_h, fifo) > 0)
            {
                status = HAL_CAN_GetRxMessage(canl_h->can_h, 
                                              fifo,
                                              &canl_h->rx_message.header,
                                              canl_h->rx_message.data);

                ADD_ERROR_IF(status != HAL_OK, CANL_ERROR_HAL, canl_h);

                if (no_errors(canl_h))
                {
                    printf("Time:    %lu\n", canl_h->rx_message.header.Timestamp);
                    printf("ID:      %lx\n", canl_h->rx_message.header.StdId);
                    printf("Length:  %lu\n", canl_h->rx_message.header.DLC);
                    printf("Data:    ");
                    
                    for (uint32_t i = 0; i < canl_h->rx_message.header.DLC; i++)
                    {
                        printf("%02x", canl_h->rx_message.data[i]);
                    }

                    printf("\n\n");
                }
            }
        }
    }

    // notify user of error and stop
    if (!no_errors(canl_h))
    {
        printf("Error (%08lx)\nStopping.\n", canl_h->err);
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