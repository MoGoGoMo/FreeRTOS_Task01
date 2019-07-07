/*
*********************************************************************************************************
*
*	Module Name : LED Flash Module
*	File Name   : bsp_led.c
*	Version     : V1.0
*	Desrciption : Control all LEDs
*
*	Log :
*		Version    Date        Author    Description
*		V1.0.0    2019-07-05   Gordon      Released
*
*	Copyright (C), 2019-2020, Gordon Tao
*
*********************************************************************************************************
*/

#include "bsp.h"

/*
	If it will be used for other hardware, definitions of GPIO needed to be modified.

	If there will be less four leds, could use the same settings with NO.1 LED
	
*/

#ifdef STM32_X3		
	/*
			LED1       : PE2 (Low=on, High=off)
			LED2       : PE3 (Low=on, High=off)
			LED3       : PE4 (Low=on, High=off)
			LED4       : PE5 (Low=on, High=off)
	*/
	#define RCC_ALL_LED 	RCC_AHB1Periph_GPIOE	

	#define GPIO_PORT_LED1  GPIOE
	#define GPIO_PIN_LED1	GPIO_Pin_2

	#define GPIO_PORT_LED2  GPIOE
	#define GPIO_PIN_LED2	GPIO_Pin_3

	#define GPIO_PORT_LED3  GPIOE
	#define GPIO_PIN_LED3	GPIO_Pin_4

	#define GPIO_PORT_LED4  GPIOE
	#define GPIO_PIN_LED4	GPIO_Pin_5

#elif defined STM32_F446
    #define RCC_ALL_LED     RCC_AHB1Periph_GPIOA

    #define GPIO_PORT_LED2  GPIOA
    #define GPIO_PIN_LED2   GPIO_Pin_5

#else	/* STM32_F4 */
	/*
			LD1     : PI10/TP_NCS          (Low=on, High=off)
			LD2     : PF7/NRF24L01_CSN     (Low=on, High=off)
			LD3     : PF8/SF_CS            (Low=on, High=off)
			LD4     : PC2/NRF905_CSN/VS1053_XCS  (Low=on, High=off)
	*/

	/* GPIO for LEDs and RCC */
	#define RCC_ALL_LED 	(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOI)

	#define GPIO_PORT_LED1  GPIOI
	#define GPIO_PIN_LED1	GPIO_Pin_10

	#define GPIO_PORT_LED2  GPIOF
	#define GPIO_PIN_LED2	GPIO_Pin_7

	#define GPIO_PORT_LED3  GPIOF
	#define GPIO_PIN_LED3	GPIO_Pin_8

	#define GPIO_PORT_LED4  GPIOC
	#define GPIO_PIN_LED4	GPIO_Pin_2
#endif

/*
*********************************************************************************************************
*	Function Name: bsp_InitLed
*	Description: Config LED GPIO, call by bsp_Init()
*	Parameter:  None
*	Return: None
*********************************************************************************************************
*/
void bsp_InitLed(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Set GPIO Clock */
	RCC_AHB1PeriphClockCmd(RCC_ALL_LED, ENABLE);

	/*
		Config all LED GPIO as pull/push and output mode
		Since Set GPIO as output, the default value of GPIO Output reg is 0, LED is on
		We don't want it. So set GPIO as output, and LED state will be off
	*/
	//bsp_LedOff(1);
	bsp_LedOff(2);
	//bsp_LedOff(3);
	//bsp_LedOff(4);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* Set as output mode */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* Set GPIO as push/pull mode */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* Set not pull up and pull down */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* Set GPIO Max speed */
#ifdef STM32_F446
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED2;
	GPIO_Init(GPIO_PORT_LED2, &GPIO_InitStructure);

#else
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED1;
	GPIO_Init(GPIO_PORT_LED1, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED2;
	GPIO_Init(GPIO_PORT_LED2, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED3;
	GPIO_Init(GPIO_PORT_LED3, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED4;
	GPIO_Init(GPIO_PORT_LED4, &GPIO_InitStructure);
#endif
}

/*
*********************************************************************************************************
*	Function Name: bsp_LedOn
*	Fucntion Description: Light up the specified LED.
*	Parameter:  _no : LED Serial Number:1 to 4
*	Return: None
*********************************************************************************************************
*/
void bsp_LedOn(uint8_t _no)
{
	_no--;

#ifdef STM32_F446
	if (_no == 0)
	{
      //GPIO_PORT_LED1->BSRRH = GPIO_PIN_LED1;
	}
	else if (_no == 1)
	{
      GPIO_PORT_LED2->BSRRH = GPIO_PIN_LED2;
	}
	else if (_no == 2)
	{
      // GPIO_PORT_LED3->BSRRH = GPIO_PIN_LED3;
	}
	else if (_no == 3)
	{
      //GPIO_PORT_LED4->BSRRH = GPIO_PIN_LED4;
	}
#else
    if (_no == 0)
      {
		GPIO_PORT_LED1->BSRRH = GPIO_PIN_LED1;
      }
	else if (_no == 1)
      {
		GPIO_PORT_LED2->BSRRH = GPIO_PIN_LED2;
      }
	else if (_no == 2)
      {
		GPIO_PORT_LED3->BSRRH = GPIO_PIN_LED3;
      }
	else if (_no == 3)
      {
		GPIO_PORT_LED4->BSRRH = GPIO_PIN_LED4;
      }
#endif
}


/*
*********************************************************************************************************
*	Function Name: bsp_LedOff
*	Function Description: Turn off the specific LED
*	Parameter:  _no : LED Serial Number，From 1 to 4
*	return: 无
*********************************************************************************************************
*/
void bsp_LedOff(uint8_t _no)
{
	_no--;

#ifdef STM32_F446
	if (_no == 0)
	{
      //GPIO_PORT_LED1->BSRRL = GPIO_PIN_LED1;
	}
	else if (_no == 1)
	{
      GPIO_PORT_LED2->BSRRL = GPIO_PIN_LED2;
	}
	else if (_no == 2)
	{
      //GPIO_PORT_LED3->BSRRL = GPIO_PIN_LED3;
	}
	else if (_no == 3)
	{
      //GPIO_PORT_LED4->BSRRL = GPIO_PIN_LED4;
	}
#else
    if (_no == 0)
      {
		GPIO_PORT_LED1->BSRRL = GPIO_PIN_LED1;
      }
	else if (_no == 1)
      {
		GPIO_PORT_LED2->BSRRL = GPIO_PIN_LED2;
      }
	else if (_no == 2)
      {
		GPIO_PORT_LED3->BSRRL = GPIO_PIN_LED3;
      }
	else if (_no == 3)
      {
		GPIO_PORT_LED4->BSRRL = GPIO_PIN_LED4;
      }
#endif
}

/*
*********************************************************************************************************
*	Function Name: bsp_LedToggle
*	Function Description: Toggle the specific LED
*	Parameter:  _no : LED serial number，From 1 to 4
*	return: Key ID
*********************************************************************************************************
*/
void bsp_LedToggle(uint8_t _no)
{
#ifdef STM32_F446
	if (_no == 1)
	{
      //GPIO_PORT_LED1->ODR ^= GPIO_PIN_LED1;
	}
	else if (_no == 2)
	{
        GPIO_PORT_LED2->ODR ^= GPIO_PIN_LED2;
	}
	else if (_no == 3)
	{
      //GPIO_PORT_LED3->ODR ^= GPIO_PIN_LED3;
	}
	else if (_no == 4)
	{
      //GPIO_PORT_LED4->ODR ^= GPIO_PIN_LED4;
	}
#else
    if (_no == 1)
      {
		GPIO_PORT_LED1->ODR ^= GPIO_PIN_LED1;
      }
	else if (_no == 2)
      {
		GPIO_PORT_LED2->ODR ^= GPIO_PIN_LED2;
      }
	else if (_no == 3)
      {
		GPIO_PORT_LED3->ODR ^= GPIO_PIN_LED3;
      }
	else if (_no == 4)
      {
		GPIO_PORT_LED4->ODR ^= GPIO_PIN_LED4;
      }
#endif
}

/*
*********************************************************************************************************
*	Function Name: bsp_IsLedOn
*	Function Description: If LED is on or not
*	Parameter:  _no : Indicate LED serial number, from 1 to 4
*	return: 1=LED ON, 0=LED OFF
*********************************************************************************************************
*/
uint8_t bsp_IsLedOn(uint8_t _no)
{
#ifdef STM32_F446
	if (_no == 1)
	{
      /*if ((GPIO_PORT_LED1->ODR & GPIO_PIN_LED1) == 0)
		{
			return 1;
		}
		return 0;*/
	}
	else if (_no == 2)
	{
		if ((GPIO_PORT_LED2->ODR & GPIO_PIN_LED2) == 0)
		{
			return 1;
		}
		return 0;
	}
	else if (_no == 3)
	{
      /*if ((GPIO_PORT_LED3->ODR & GPIO_PIN_LED3) == 0)
		{
			return 1;
		}
		return 0;*/
	}
	else if (_no == 4)
	{
      /*if ((GPIO_PORT_LED4->ODR & GPIO_PIN_LED4) == 0)
		{
			return 1;
		}
		return 0;*/
	}
#else
    if (_no == 1)
      {
		if ((GPIO_PORT_LED1->ODR & GPIO_PIN_LED1) == 0)
          {
			return 1;
          }
		return 0;
      }
	else if (_no == 2)
      {
		if ((GPIO_PORT_LED2->ODR & GPIO_PIN_LED2) == 0)
          {
			return 1;
          }
		return 0;
      }
	else if (_no == 3)
      {
		if ((GPIO_PORT_LED3->ODR & GPIO_PIN_LED3) == 0)
          {
			return 1;
          }
		return 0;
      }
	else if (_no == 4)
      {
		if ((GPIO_PORT_LED4->ODR & GPIO_PIN_LED4) == 0)
          {
			return 1;
          }
		return 0;
      }
#endif
	return 0;
}

/***************************** (END OF FILE) *********************************/
