/*
 * threadx.c
 *
 *  Created on: Apr 20, 2024
 *      Author: Steven
 */
#include "app_threadx.h"


TX_THREAD txMainThread;
TX_THREAD txAnalogThread;
TX_THREAD txAeroThread;
TX_THREAD txCAN500HZThread;

TX_SEMAPHORE analogSemaphore;
TX_SEMAPHORE aeroSemaphore;


UINT ThreadX_Init(VOID *memory_ptr){
    UINT ret = TX_SUCCESS;
      /* USER CODE BEGIN App_ThreadX_MEM_POOL */
      TX_BYTE_POOL *bytePool = (TX_BYTE_POOL*)memory_ptr;
      CHAR *pointer;
      /* USER CODE END App_ThreadX_MEM_POOL */

      /* USER CODE BEGIN App_ThreadX_Init */
      if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
          return TX_POOL_ERROR;
      }

      if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
          return TX_POOL_ERROR;
      }

      if(tx_thread_create(&txMainThread, "txMainThread", txMainThreadEntry, 0, pointer,
                             TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                             TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
          return TX_THREAD_ERROR;
      }

      if(tx_thread_create(&txMainThread, "txAnalogThread", txAnalogThreadEntry, 0, pointer,
                             TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                             TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
          return TX_THREAD_ERROR;
      }

      if(tx_thread_create(&txMainThread, "txAeroThread", txAeroThreadEntry, 0, pointer,
                           TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                           TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
            return TX_THREAD_ERROR;
        }
      if(tx_thread_create(&txMainThread, "txCAN500HZ", txCAN500HZThreadEntry, 0, pointer,
                           TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                           TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
            return TX_THREAD_ERROR;
        }

      tx_semaphore_create(&analogSemaphore, "analogSemaphore", 0);
      tx_semaphore_create(&aeroSemaphore, "aeroSemaphore", 0);
      /* USER CODE END App_ThreadX_Init */

      return ret;
}
