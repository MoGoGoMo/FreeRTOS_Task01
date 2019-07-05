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
*	函 数 名: bsp_InitLed
*	功能说明: 配置LED指示灯相关的GPIO,  该函数被 bsp_Init() 调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitLed(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 打开GPIO时钟 */
	RCC_AHB1PeriphClockCmd(RCC_ALL_LED, ENABLE);

	/*
		配置所有的LED指示灯GPIO为推挽输出模式
		由于将GPIO设置为输出时，GPIO输出寄存器的值缺省是0，因此会驱动LED点亮.
		这是我不希望的，因此在改变GPIO为输出前，先关闭LED指示灯
	*/
	//bsp_LedOff(1);
	bsp_LedOff(2);
	//bsp_LedOff(3);
	//bsp_LedOff(4);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* 设为输出口 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* 设为推挽模式 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* 上下拉电阻不使能 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO口最大速度 */
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
*	函 数 名: bsp_LedOn
*	功能说明: 点亮指定的LED指示灯。
*	形    参:  _no : 指示灯序号，范围 1 - 4
*	返 回 值: 无
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
*	函 数 名: bsp_LedOff
*	功能说明: 熄灭指定的LED指示灯。
*	形    参:  _no : 指示灯序号，范围 1 - 4
*	返 回 值: 无
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
*	函 数 名: bsp_LedToggle
*	功能说明: 翻转指定的LED指示灯。
*	形    参:  _no : 指示灯序号，范围 1 - 4
*	返 回 值: 按键代码
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
*	函 数 名: bsp_IsLedOn
*	功能说明: 判断LED指示灯是否已经点亮。
*	形    参:  _no : 指示灯序号，范围 1 - 4
*	返 回 值: 1表示已经点亮，0表示未点亮
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

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
