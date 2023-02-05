/******************************************************************************
 * @file    config.h
 * @author  Tim Brewis (@t-bre)
 * @brief   Configuration header
 *****************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

// thread priorities
#define CONFIG_RTCAN1_PRIORITY          2
#define CONFIG_RTCAN2_PRIORITY          3
#define CONFIG_RTCAN3_PRIORITY          3
#define CONFIG_CANL_PRIORITY            4

// CAN listener test rig
#define CONFIG_ENABLE_CAN_LISTENER      1
    #define CONFIG_LISTEN_TO_CAN1       1
    #define CONFIG_LISTEN_TO_CAN2       0
    #define CONFIG_LISTEN_TO_CAN3       0
    #define CONFIG_CAN1_NAME            "CAN1"
    #define CONFIG_CAN2_NAME            "CAN2"
    #define CONFIG_CAN3_NAME            "CAN3"
    #define CONFIG_CAN1_LISTEN_IDS      {0x100}
    #define CONFIG_CAN2_LISTEN_IDS      {0x000}
    #define CONFIG_CAN3_LISTEN_IDS      {0x000}


#endif