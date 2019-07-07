/*
*********************************************************************************************************
*
*  
* @file    Project/bsp/bsp_led.h
* @author  Gordon Tao
* @version V1.0.0
* @date    04-June-2019
* @brief   BSP LED FUNCTION HEADER
*
*	Copyright (C), 2019-2020, Gordon Tao
*
*********************************************************************************************************
*/

#ifndef __BSP_LED_H
#define __BSP_LED_H

void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no);
uint8_t bsp_IsLedOn(uint8_t _no);

#endif

/***************************** (END OF FILE) *********************************/
