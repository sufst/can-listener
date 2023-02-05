/******************************************************************************
 * @file   canl.c
 * @author Tim Brewis (@t-bre)
 * @brief  CAN listener
 ******************************************************************************/

#include "can_listener.h"

#include <stdio.h>
#include <stdbool.h>

#define CANL_THREAD_STACK_SIZE  1024

#define ADD_ERROR_IF(cond, err, inst) if(cond) { add_error(inst, err); }

static void canl_thread_entry(ULONG input);
static void print_msg(canl_handle_t* canl_h, rtcan_msg_t* msg_ptr);

//==============================================================================

/**
 * @brief       Initialises CANL instance
 * 
 * @param[in]   canl_h              CANL handle
 * @param[in]   rtcan_h             RTCAN handle to listen to
 * @param[in]   bus_name            Name of CAN bus
 * @param[in]   can_ids             Array of CAN IDs to listen to
 * @param[in]   num_can_ids         Number of CAN IDs in array
 * @param[in]   app_mem_pool        Application memory pool
 * @param[in]   printf_mutex_ptr    Mutex for printf() access
 */
void canl_init(canl_handle_t* canl_h, 
               rtcan_handle_t* rtcan_h,
               const char* bus_name,
               const uint32_t* can_ids,
               const uint32_t num_can_ids,
               TX_BYTE_POOL* app_mem_pool,
               TX_MUTEX* printf_mutex_ptr)
{
    canl_h->rtcan_h = rtcan_h;
    canl_h->bus_name = bus_name;
    canl_h->printf_mutex_ptr = printf_mutex_ptr;

    // setup receive queue and RTCAN subscriptions
    UINT tx_status = tx_queue_create(&canl_h->can_rx_queue,
                                     "CAN Listener Rx Queue",
                                     TX_1_ULONG,
                                     &canl_h->can_rx_queue_mem,
                                     CANL_RX_QUEUE_LENGTH * sizeof(rtcan_msg_t));

    if (tx_status == TX_SUCCESS)
    {
        for (uint32_t i = 0; i < num_can_ids; i++)
        {
            rtcan_subscribe(canl_h->rtcan_h, can_ids[i], &canl_h->can_rx_queue);
        }
    }

    // create and launch thread
    void* stack_ptr = NULL;

    if (tx_status == TX_SUCCESS)
    {
        tx_status = tx_byte_allocate(app_mem_pool,
                                     (void**) &stack_ptr,
                                     CANL_THREAD_STACK_SIZE,
                                     TX_NO_WAIT);
    }

    if (tx_status == TX_SUCCESS)
    {
        tx_status = tx_thread_create(&canl_h->thread,
                                     "CAN Listener Thread",
                                     canl_thread_entry,
                                     (ULONG) canl_h,
                                     stack_ptr,
                                     CANL_THREAD_STACK_SIZE,
                                     CONFIG_CANL_PRIORITY,
                                     CONFIG_CANL_PRIORITY,
                                     TX_NO_TIME_SLICE,
                                     TX_AUTO_START);
    }

}

//==============================================================================

/**
 * @brief       CAN listener thread entry
 * 
 * @param[in]   input   CANL handle
 */
static void canl_thread_entry(ULONG input)
{
    canl_handle_t* canl_h = (canl_handle_t*) input;

    while (1)
    {
        rtcan_msg_t* msg_ptr;

        UINT tx_status = tx_queue_receive(&canl_h->can_rx_queue, 
                                          (void*) &msg_ptr,
                                          TX_WAIT_FOREVER);

        if (tx_status == TX_SUCCESS)
        {
            print_msg(canl_h, msg_ptr);
            rtcan_msg_consumed(canl_h->rtcan_h, msg_ptr);
        }
    }
}

/**
 * @brief       Print received message
 * 
 * @param[in]   canl_h      CANL handle
 * @param[in]   msg_ptr     Pointer to received message
 */
static void print_msg(canl_handle_t* canl_h, rtcan_msg_t* msg_ptr)
{
    UINT tx_status = tx_mutex_get(canl_h->printf_mutex_ptr, TX_WAIT_FOREVER);

    if (tx_status == TX_SUCCESS)
    {
        if (canl_h->bus_name != NULL)
        {
            printf("Bus:     %s\r\n", canl_h->bus_name);
        }

        printf("Tick:    %lu\r\n", tx_time_get());
        printf("ID:      0x%lx\r\n", msg_ptr->identifier);
        printf("Length:  %lu\r\n", msg_ptr->length);
        printf("Data:    0x");

        for (uint32_t i = 0; i < msg_ptr->length; i++)
        {
            printf("%02x", msg_ptr->data[i]);
        }

        printf("\r\n\n");

        tx_mutex_put(canl_h->printf_mutex_ptr);
    }
}