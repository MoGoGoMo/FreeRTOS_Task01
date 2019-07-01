#include "bsp.h"

void bsp_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	bsp_InitUart(); 	/* 初始化串口 */
	// bsp_InitKey();		/* 初始化按键变量 */
	// bsp_InitLed(); 		/* 初始LED指示灯端口 */
}