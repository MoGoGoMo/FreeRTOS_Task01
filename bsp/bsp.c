/*
  ****************************************************************** 
  * @file    Project/bsp/bsp.c
  * @author  Gordon Tao
  * @version V1.0.0
  * @date    04-June-2019
  * @brief   BSP INITIALIZATION
  * ****************************************************************
*/

#include "bsp.h"

void bsp_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	bsp_InitUart(); 	/* 初始化串口 */
	bsp_InitKey();		/* 初始化按键变量 */
	// bsp_InitLed(); 		/* 初始LED指示灯端口 */
}