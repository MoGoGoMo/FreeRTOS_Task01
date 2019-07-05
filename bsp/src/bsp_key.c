/*
  ******************************************************************************
  * @file    Project/bsp/bsp_key.c
  * @author  Gordon Tao
  * @version V1.0.0
  * @date    05-June-2019
  * @brief   Button Function module, scan the independent keys, including software filter
  * and FIFO for keys.
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

#include "bsp.h"

/*
	If it will be used for other hardware, definitions of GPIO and 
	IsKeyDown1 to IsKeyDown8 needed to be modified.

	If you don't have 8 keys, you could define other 7 keys the same as Key1
	
	#define KEY_COUNT    8	  //Define in bsp_key.h
*/

#ifdef STM32_X3		
	/*
			K1键       : PC13 (low level: pressed)
			K2键       : PC0  (low level: pressed)
			K3键       : PC1  (low level: pressed)
			摇杆UP键   : PC2  (low level: pressed)
			摇杆DOWN键 : PC3  (low level: pressed)
			摇杆LEFT键 : PC4  (low level: pressed)
			摇杆RIGHT键: PA0  (low level: pressed)
			摇杆OK键   : PA1  (low level: pressed)
	*/
	#define RCC_ALL_KEY 	(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC)	/* 按键口对应的RCC时钟 */

	#define GPIO_PORT_K1    GPIOC
	#define GPIO_PIN_K1	    GPIO_Pin_13

	#define GPIO_PORT_K2    GPIOC
	#define GPIO_PIN_K2	    GPIO_Pin_0

	#define GPIO_PORT_K3    GPIOC
	#define GPIO_PIN_K3	    GPIO_Pin_1

	#define GPIO_PORT_K4    GPIOC
	#define GPIO_PIN_K4	    GPIO_Pin_3

	#define GPIO_PORT_K5    GPIOC
	#define GPIO_PIN_K5	    GPIO_Pin_4

	#define GPIO_PORT_K6    GPIOC
	#define GPIO_PIN_K6	    GPIO_Pin_2

	#define GPIO_PORT_K7    GPIOA
	#define GPIO_PIN_K7	    GPIO_Pin_1

	#define GPIO_PORT_K8    GPIOA
	#define GPIO_PIN_K8	    GPIO_Pin_0

#elif defined STM32_F446 /* Nucleo-F446 board */
/* User Key    :    B1 (PC13)    (low level = press down)  */
    #define RCC_ALL_KEY     (RCC_AHB1Periph_GPIOC)

    #define GPIO_PORT_K1    GPIOC
    #define GPIO_PIN_K1     GPIO_Pin_13

/*    #define GPIO_PORT_K2    GPIOC
    #define GPIO_PIN_K2     GPIO_Pin_13

    #define GPIO_PORT_K3    GPIOC
    #define GPIO_PIN_K3     GPIO_Pin_13

    #define GPIO_PORT_K4    GPIOC
    #define GPIO_PIN_K4     GPIO_Pin_13

    #define GPIO_PORT_K5    GPIOC
    #define GPIO_PIN_K5     GPIO_Pin_13

    #define GPIO_PORT_K6    GPIOC
    #define GPIO_PIN_K6     GPIO_Pin_13

    #define GPIO_PORT_K7    GPIOC
    #define GPIO_PIN_K7     GPIO_Pin_13

    #define GPIO_PORT_K8    GPIOC
    #define GPIO_PIN_K8     GPIO_Pin_13*/

#else	/* STM32_V5 */
	/*
			K1 Key      : PI8   (low level: pressed)
			K2 Key      : PC13  (low level: pressed)
			K3 Key      : PI11  (low level: pressed)
			UP Key      : PH2   (low level: pressed)
			DOWN Key    : PH3   (low level: pressed)
			LEFT Key    : PF11  (low level: pressed)
			RIGHT Key   : PG7   (low level: pressed)
			OK Key      : PH15  (low level: pressed)
	*/

	/* Keys GPIO and RCC Port */
	#define RCC_ALL_KEY 	(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI | RCC_AHB1Periph_GPIOG)

	#define GPIO_PORT_K1    GPIOI
	#define GPIO_PIN_K1	    GPIO_Pin_8

	#define GPIO_PORT_K2    GPIOC
	#define GPIO_PIN_K2	    GPIO_Pin_13

	#define GPIO_PORT_K3    GPIOI
	#define GPIO_PIN_K3	    GPIO_Pin_11

	#define GPIO_PORT_K4    GPIOH
	#define GPIO_PIN_K4	    GPIO_Pin_2

	#define GPIO_PORT_K5    GPIOH
	#define GPIO_PIN_K5	    GPIO_Pin_3

	#define GPIO_PORT_K6    GPIOF
	#define GPIO_PIN_K6	    GPIO_Pin_11

	#define GPIO_PORT_K7    GPIOG
	#define GPIO_PIN_K7	    GPIO_Pin_7

	#define GPIO_PORT_K8    GPIOH
	#define GPIO_PIN_K8	    GPIO_Pin_15
#endif

static KeyStruct_TypeDef s_tBtn[KEY_COUNT];
static KeyFIFO_TypeDef s_tKey;		/* Key FIFO variable, Structure */

static void bsp_InitKeyVar(void);
static void bsp_InitKeyHard(void);
static void bsp_DetectKey(uint8_t i);

/*
*********************************************************************************************************
*	Function Name: IsKeyDownX
*	Function Description: If Key is pressed
*	Parameters: NONE
*	Return: 1=pressed, 0=released
*********************************************************************************************************
*/
#ifdef STM32_X3		
	static uint8_t IsKeyDown1(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown2(void) {if ((GPIO_PORT_K2->IDR & GPIO_PIN_K2) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown3(void) {if ((GPIO_PORT_K3->IDR & GPIO_PIN_K3) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown4(void) {if ((GPIO_PORT_K4->IDR & GPIO_PIN_K4) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown5(void) {if ((GPIO_PORT_K5->IDR & GPIO_PIN_K5) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown6(void) {if ((GPIO_PORT_K6->IDR & GPIO_PIN_K6) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown7(void) {if ((GPIO_PORT_K7->IDR & GPIO_PIN_K7) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown8(void) {if ((GPIO_PORT_K8->IDR & GPIO_PIN_K8) == 0) return 1;else return 0;}
#elif defined STM32_F446
    static uint8_t IsKeyDown1(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1; else return 0;}
/*    static uint8_t IsKeyDown2(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1; else return 0;}
    static uint8_t IsKeyDown3(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1; else return 0;}
    static uint8_t IsKeyDown4(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1; else return 0;}
    static uint8_t IsKeyDown5(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1; else return 0;}
    static uint8_t IsKeyDown6(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1; else return 0;}
    static uint8_t IsKeyDown7(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1; else return 0;}
    static uint8_t IsKeyDown8(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1; else return 0;}*/
#else				
	static uint8_t IsKeyDown1(void) {if ((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown2(void) {if ((GPIO_PORT_K2->IDR & GPIO_PIN_K2) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown3(void) {if ((GPIO_PORT_K3->IDR & GPIO_PIN_K3) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown4(void) {if ((GPIO_PORT_K4->IDR & GPIO_PIN_K4) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown5(void) {if ((GPIO_PORT_K5->IDR & GPIO_PIN_K5) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown6(void) {if ((GPIO_PORT_K6->IDR & GPIO_PIN_K6) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown7(void) {if ((GPIO_PORT_K7->IDR & GPIO_PIN_K7) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown8(void) {if ((GPIO_PORT_K8->IDR & GPIO_PIN_K8) == 0) return 1;else return 0;}
	static uint8_t IsKeyDown9(void) {if (IsKeyDown1() && IsKeyDown2()) return 1;else return 0;}
	static uint8_t IsKeyDown10(void) {if (IsKeyDown1() && IsKeyDown2()) return 1;else return 0;}
#endif

/*
*********************************************************************************************************
*	Function Name: bsp_InitKey
*	Function Description: Initialize variable of Keys. 
*	Parameters:  NONE
*	Return: NONE
*********************************************************************************************************
*/
void bsp_InitKey(void)
{
	bsp_InitKeyVar();		/* Initialize Key variable */
	bsp_InitKeyHard();		/* Initialize Key hardware */
}

/*
*********************************************************************************************************
*	Function Name: bsp_PutKey
*	Function Description: put one Key ID to the FIFO buffer. It can simulate a virtual key
*	Parameters:  _KeyCode : Key ID
*	Return: NONE
*********************************************************************************************************
*/
void bsp_PutKey(uint8_t _KeyCode)
{
	s_tKey.Buf[s_tKey.Write] = _KeyCode;

	if (++s_tKey.Write  >= KEY_FIFO_SIZE)
	{
		s_tKey.Write = 0;
	}
}

/*
*********************************************************************************************************
*	Function Name: bsp_GetKey
*	Function Description: read a key ID from FIFO buffer
*	Parameters:  NONE
*	Return: Key ID
*********************************************************************************************************
*/
uint8_t bsp_GetKey(void)
{
	uint8_t ret;

	if (s_tKey.Read == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read];

		if (++s_tKey.Read >= KEY_FIFO_SIZE)
		{
			s_tKey.Read = 0;
		}
		return ret;
	}
}

/*
*********************************************************************************************************
*	Function Name: bsp_GetKey2
*	Function Description: read a Key ID from FIFO buffer with a pointer.
*	Parameters:  NONE
*	Return: Key ID
*********************************************************************************************************
*/
uint8_t bsp_GetKey2(void)
{
	uint8_t ret;

	if (s_tKey.Read2 == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read2];

		if (++s_tKey.Read2 >= KEY_FIFO_SIZE)
		{
			s_tKey.Read2 = 0;
		}
		return ret;
	}
}

/*
*********************************************************************************************************
*	Function Name: bsp_GetKeyState
*	Function Description: get the key state
*	Parameters:  _ucKeyID : Key ID，From 0
*	Return: 1=pressed， 0 = released
*********************************************************************************************************
*/
uint8_t bsp_GetKeyState(KEYID_E _ucKeyID)
{
	return s_tBtn[_ucKeyID].State;
}

/*
*********************************************************************************************************
*	Function Name: bsp_SetKeyParam
*	Function Description: set key parameters
*	Parameters：_ucKeyID : Key ID，From 0
*			_LongTime : long pressed time
*			 _RepeatSpeed : 
*	Return: NONE
*********************************************************************************************************
*/
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t  _RepeatSpeed)
{
	s_tBtn[_ucKeyID].LongTime = _LongTime;			/* 0 = no long pressed key event */
	s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed;			/* 0 = no repeat key event */
	s_tBtn[_ucKeyID].RepeatCount = 0;						
}


/*
*********************************************************************************************************
*	Function Name: bsp_ClearKey
*	Function Description: Empty FIFO buffer
*	Parameters：NONE
*	Return: NONE
*********************************************************************************************************
*/
void bsp_ClearKey(void)
{
	s_tKey.Read = s_tKey.Write;
}

/*
*********************************************************************************************************
*	Function Name: bsp_InitKeyHard
*	Function Description: Cofigure GPIO for Keys
*	Parameters:  NONE
*	Return: NONE
*********************************************************************************************************
*/
static void bsp_InitKeyHard(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 第1步：打开GPIO时钟 */
	RCC_AHB1PeriphClockCmd(RCC_ALL_KEY, ENABLE);

	/* 第2步：配置所有的按键GPIO为浮动输入模式(实际上CPU复位后就是输入状态) */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		/* 设为输入口 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* 设为推挽模式 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* NONE需上下拉电阻 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* IO口最大速度 */

    #if defined(STM32_V5) || defined(STM32_X3)
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K1;
	GPIO_Init(GPIO_PORT_K1, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K2;
	GPIO_Init(GPIO_PORT_K2, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K3;
	GPIO_Init(GPIO_PORT_K3, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K4;
	GPIO_Init(GPIO_PORT_K4, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K5;
	GPIO_Init(GPIO_PORT_K5, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K6;
	GPIO_Init(GPIO_PORT_K6, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K7;
	GPIO_Init(GPIO_PORT_K7, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K8;
	GPIO_Init(GPIO_PORT_K8, &GPIO_InitStructure);
    #elif defined STM32_F446
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K1;
	GPIO_Init(GPIO_PORT_K1, &GPIO_InitStructure);

    #endif

}

/*
*********************************************************************************************************
*	Function Name: bsp_InitKeyVar
*	Function Description: Initialize Keys Variable
*	Parameters:  NONE
*	Return: NONE
*********************************************************************************************************
*/
static void bsp_InitKeyVar(void)
{
	uint8_t i;

	s_tKey.Read = 0;
	s_tKey.Write = 0;
	s_tKey.Read2 = 0;

	for (i = 0; i < KEY_COUNT; i++)
	{
		s_tBtn[i].LongTime = KEY_LONG_TIME;			
		s_tBtn[i].Count = KEY_FILTER_TIME / 2;		/* 计数器设置为滤波时间的一半 */
		s_tBtn[i].State = 0;							/* 按键缺省状态，0为未按下 */
		s_tBtn[i].RepeatSpeed = 0;						/* 按键连发的速度，0表示不支持连发 */
		s_tBtn[i].RepeatCount = 0;						/* 连发计数器 */
	}

    #if defined(STM32_V5) || defined(STM32_X3)
	/* 如果需要单独更改某个按键的参数，可以在此单独重新赋值 */
	/* 比如，我们希望按键1按下超过1秒后，自动重发相同键值 */
	s_tBtn[KID_JOY_U].LongTime = 100;
	s_tBtn[KID_JOY_U].RepeatSpeed = 5;	/* 每隔50ms自动发送键值 */

	s_tBtn[KID_JOY_D].LongTime = 100;
	s_tBtn[KID_JOY_D].RepeatSpeed = 5;	/* 每隔50ms自动发送键值 */

	s_tBtn[KID_JOY_L].LongTime = 100;
	s_tBtn[KID_JOY_L].RepeatSpeed = 5;	/* 每隔50ms自动发送键值 */

	s_tBtn[KID_JOY_R].LongTime = 100;
	s_tBtn[KID_JOY_R].RepeatSpeed = 5;	/* 每隔50ms自动发送键值 */

	s_tBtn[0].IsKeyDownFunc = IsKeyDown1;
	s_tBtn[1].IsKeyDownFunc = IsKeyDown2;
	s_tBtn[2].IsKeyDownFunc = IsKeyDown3;
	s_tBtn[3].IsKeyDownFunc = IsKeyDown4;
	s_tBtn[4].IsKeyDownFunc = IsKeyDown5;
	s_tBtn[5].IsKeyDownFunc = IsKeyDown6;
	s_tBtn[6].IsKeyDownFunc = IsKeyDown7;
	s_tBtn[7].IsKeyDownFunc = IsKeyDown8;

	/* Combination Key */
	s_tBtn[8].IsKeyDownFunc = IsKeyDown9;
	s_tBtn[9].IsKeyDownFunc = IsKeyDown10;
    #elif defined STM32_F446
    s_tBtn[0].IsKeyDownFunc = IsKeyDown1;

    #endif
}

/*
*********************************************************************************************************
*	Function Name: bsp_DetectKey
*	Function Description: 检测一个按键。非阻塞状态，必须被周期性的调用。
*	Parameters:  按键结构变量指针
*	Return: NONE
*********************************************************************************************************
*/
static void bsp_DetectKey(uint8_t i)
{
	KeyStruct_TypeDef *pBtn;

	/*
		如果没有初始化按键函数，则报错
		if (s_tBtn[i].IsKeyDownFunc == 0)
		{
			printf("Fault : DetectButton(), s_tBtn[i].IsKeyDownFunc undefine");
		}
	*/

	pBtn = &s_tBtn[i];
	if (pBtn->IsKeyDownFunc())
	{
		if (pBtn->Count < KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count < 2 * KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else
		{
			if (pBtn->State == 0)
			{
				pBtn->State = 1;

				/* 发送按钮按下的消息 */
				bsp_PutKey((uint8_t)(3 * i + 1));
			}

			if (pBtn->LongTime > 0)
			{
				if (pBtn->LongCount < pBtn->LongTime)
				{
					/* 发送按钮持续按下的消息 */
					if (++pBtn->LongCount == pBtn->LongTime)
					{
						/* 键值放入按键FIFO */
						bsp_PutKey((uint8_t)(3 * i + 3));
					}
				}
				else
				{
					if (pBtn->RepeatSpeed > 0)
					{
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
						{
							pBtn->RepeatCount = 0;
							/* 常按键后，每隔10ms发送1个按键 */
							bsp_PutKey((uint8_t)(3 * i + 1));
						}
					}
				}
			}
		}
	}
	else
	{
		if(pBtn->Count > KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count != 0)
		{
			pBtn->Count--;
		}
		else
		{
			if (pBtn->State == 1)
			{
				pBtn->State = 0;

				/* 发送按钮弹起的消息 */
				bsp_PutKey((uint8_t)(3 * i + 2));
			}
		}

		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

/*
*********************************************************************************************************
*	Function Name: bsp_KeyScan
*	Function Description: 扫描所有按键。非阻塞，被systick中断周期性的调用
*	Parameters:  NONE
*	Return: NONE
*********************************************************************************************************
*/
void bsp_KeyScan(void)
{
	uint8_t i;

	for (i = 0; i < KEY_COUNT; i++)
	{
		bsp_DetectKey(i);
	}
}

/*****************************  (END OF FILE) *********************************/
