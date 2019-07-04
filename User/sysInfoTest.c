 /*
*********************************************************************************************************
*
*********************************************************************************************************
*/
#include "bsp.h"


/* Timer frequency，per interrupt 50us */
#define  timerINTERRUPT_FREQUENCY	20000

/* Interrupt Priority */
#define  timerHIGHEST_PRIORITY		2

/* called by system */
volatile uint32_t ulHighFrequencyTimerTicks = 0UL;

/*
*********************************************************************************************************
*	Function Name: vSetupTimerTest
*	Description: Create Timer
*	Parameter: None
*	Return Value: None
*********************************************************************************************************
*/
void vSetupSysTimerForTest(void)
{
  bsp_SetTIMforInt(TIM6, timerINTERRUPT_FREQUENCY, timerHIGHEST_PRIORITY, 0);
}

/*
*********************************************************************************************************
*   Function Name: TIM6_DAC_IRQHandler
*	Description: Timer6 Interupt service process
*	Parameter: None
*	Return Value: None
*********************************************************************************************************
*/
void TIM6_DAC_IRQHandler( void )
{
  if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
      ulHighFrequencyTimerTicks++;
      TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	}
}
