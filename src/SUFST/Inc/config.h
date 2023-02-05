/******************************************************************************
 * @file    config.h
 * @author  Tim Brewis (@t-bre)
 * @brief   Configuration header
 *****************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

// RTCAN service configuration
#define CONFIG_RTCAN_C_PRIORITY         2

// CAN listener test rig
#define CONFIG_ENABLE_CAN_LISTENER      1
    #define CONFIG_LISTEN_TO_CANC       1
    #define CONFIG_LISTEN_TO_CANS       0
    #define CONFIG_CANC_LISTEN_IDS      {0x100}
    #define CONFIG_CANL_PRIORITY        3


#endif