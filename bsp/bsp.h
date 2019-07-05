/**
  ******************************************************************************
  * @file    Project/F446_T1/bsp.h
  * @author  Gordon Tao
  * @version V1.0.0
  * @date    04-June-2019
  * @brief   Header for bsp.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2019 MOGO Technology</center></h2>
  *
  * Licensed under  MOGO FW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H
#define __BSP_H

// #define STM32F446xx
#define USE_FREERTOS    1

#if !defined(STM32F446xx)
    #error "Please define the board model : STM32F446xx or STM32_F407 or STM32_F401"
#endif

/* Define BSP version ---------------------------------------------------------*/
#define BSP_VERSION_NUMBER       "1.0.0"
#define BSP_VERSION_MAJOR           1
#define BSP_VERSION_MINOR           0
#define BSP_VERSION_BUILD           0

#if USE_FREERTOS == 1
    #include "FreeRTOS.h"
    #include "task.h"
    #include "list.h"
    #include "queue.h"
    #include "portable.h"
    #include "timers.h"
    #include "semphr.h"
    #include "portmacro.h"
    #define DISABLE_INT()   taskENTER_CRITICAL()
    #define ENABLE_INT()   taskEXIT_CRITICAL()
#else
    #define ENABLE_INT()   __set_PRIMASK(0)    //Enable Global Interrupt
    #define DISABLE_INT()   __set_PRIMASK(1)   //Disable Global Interrupt
#endif

/* Includes Standard Libraries------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

/* Include OS Libraries ------------------------------------------------------------------------*/


/* Include User App & BSP  ---------------------------------------------------------------------*/
#include "bsp_uart_fifo.h"
// #include "bsp_led.h"
#include "bsp_key.h"

#include "bsp_tim_pwm.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void bsp_Init(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
