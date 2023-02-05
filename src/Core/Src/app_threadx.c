/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "test_rig.h"
#include "can.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
test_rig_context_t test_rig;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_ThreadX_MEM_POOL */
  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
  test_rig_init(&test_rig, &hcan1, NULL, byte_pool);
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

/**
  * @brief  MX_ThreadX_Init
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */

/*
 * These callbacks are put here so that all "global" effects are contained
 * within this file, allowing all the SUFST code to be modular.
 */
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef* can_h)
{
    (void) test_rig_handle_can_tx_mailbox_callback(&test_rig, can_h);
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef* can_h)
{
    (void) test_rig_handle_can_tx_mailbox_callback(&test_rig, can_h);
}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef* can_h)
{
    (void) test_rig_handle_can_tx_mailbox_callback(&test_rig, can_h);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* can_h)
{
    (void) test_rig_handle_can_rx_it(&test_rig, can_h, 0);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef* can_h)
{
    (void) test_rig_handle_can_rx_it(&test_rig, can_h, 1);
}

/* USER CODE END 1 */
