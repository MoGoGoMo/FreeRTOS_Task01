/**
  ******************************************************************************
  * @file    Project/F446_T1/bsp.h
  * @author  Gordon Tao
  * @version V0.1
  * @date    27-June-2019
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

#define STM32_F446
#define USE_FREERTOS    0

#if !defined(STM32_F446) || !defined(STM32_F407) || !defined(STM32_F401)
    #error "Please define the board model : STM32_F446 or STM32_F407 or STM32_F401"
#endif

/* Define BSP version ---------------------------------------------------------*/
#define __STM32F4_BSP_VERSION       "0.1"

#if USE_FREERTOS == 1
    #include "FreeRTOS.h"
    #include "task.h"
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
    #dfine FALSE 0
#endif

/* Include OS Libraries ------------------------------------------------------------------------*/


/* Include User App & BSP  ---------------------------------------------------------------------*/
#include "bsp_usart_fifo.h"
#include "bsp_led.h"
#include "bsp_key.h"

#include "bsp_tim_pwm.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void bsp_Init(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
