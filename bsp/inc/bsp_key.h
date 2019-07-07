/*
*********************************************************************************************************
*
*  
* @file    Project/bsp/bsp_key.h
* @author  Gordon Tao
* @version V1.0.0
* @date    04-June-2019
* @brief   BSP KEY FUNCTION HEADER
*
*	Copyright (C), 2019-2020, Gordon Tao
*
*********************************************************************************************************
*/

#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "bsp.h"

#define KEY_COUNT    1	   					/* Key Numbers, 8 Independent keys + 2 key combinations */


#define KEY_DOWN_K1		KEY_1_DOWN
#define KEY_UP_K1		KEY_1_UP
#define KEY_LONG_K1		KEY_1_LONG

#define KEY_DOWN_K2		KEY_2_DOWN
#define KEY_UP_K2		KEY_2_UP
#define KEY_LONG_K2		KEY_2_LONG

#define KEY_DOWN_K3		KEY_3_DOWN
#define KEY_UP_K3		KEY_3_UP
#define KEY_LONG_K3		KEY_3_LONG

#define JOY_DOWN_U		KEY_4_DOWN		/* UP */
#define JOY_UP_U		KEY_4_UP
#define JOY_LONG_U		KEY_4_LONG

#define JOY_DOWN_D		KEY_5_DOWN		/* DOWN */
#define JOY_UP_D		KEY_5_UP
#define JOY_LONG_D		KEY_5_LONG

#define JOY_DOWN_L		KEY_6_DOWN		/* LEFT */
#define JOY_UP_L		KEY_6_UP
#define JOY_LONG_L		KEY_6_LONG

#define JOY_DOWN_R		KEY_7_DOWN		/* RIGHT */
#define JOY_UP_R		KEY_7_UP
#define JOY_LONG_R		KEY_7_LONG

#define JOY_DOWN_OK		KEY_8_DOWN		/* OK */
#define JOY_UP_OK		KEY_8_UP
#define JOY_LONG_OK		KEY_8_LONG

#define SYS_DOWN_K1K2	KEY_9_DOWN		/* K1 K2 Combination Key */
#define SYS_UP_K1K2	    KEY_9_UP
#define SYS_LONG_K1K2	KEY_9_LONG

#define SYS_DOWN_K2K3	KEY_10_DOWN		/* K2 K3 Combination Key */
#define SYS_UP_K2K3  	KEY_10_UP
#define SYS_LONG_K2K3	KEY_10_LONG

/* KEY ID, used by function bsp_KeyState() */
typedef enum
{
	KID_K1 = 0,
	KID_K2,
	KID_K3,
	KID_JOY_U,
	KID_JOY_D,
	KID_JOY_L,
	KID_JOY_R,
	KID_JOY_OK
}KEYID_E;

/*
	Timer is 50ms, Uint:10ms
	When detects 50ms Key events, it will be available. Including Pressed and release button
	Even if there is no hardware filter, it will be effective in this way.
*/
#define KEY_FILTER_TIME   5
#define KEY_LONG_TIME     100			/* 10ms， 1s= long pressed */

/*
	Each button will use a whole global Key structure
*/
typedef struct
{
	/* this is a function pointer, indicate if pressed the button */
	uint8_t (*IsKeyDownFunc)(void); /* if the button is pressed, 1 means pressed */

	uint8_t  Count;			/* filter counter */
	uint16_t LongCount;		/* long pressed counter */
	uint16_t LongTime;		/* time period pessed button, 0=No long time button pressed */
	uint8_t  State;			/* button stats */
	uint8_t  RepeatSpeed;	/* repeat press button period */
	uint8_t  RepeatCount;	/* repeat press button counter */
}KeyStruct_TypeDef;

/*
	Define Key ID for each button, include pressed, released, long pressed events
	recommend to use enum not #define, because:
	1. It will be easier to add new Key ID and adjust the sequence
	2. complier will help us to avoid the repeat key ID
*/
typedef enum
{
	KEY_NONE = 0,			/* 0 = No button event */

	KEY_1_DOWN,				/* Key 1 pressed */
	KEY_1_UP,				/* Key 1 released */
	KEY_1_LONG,				/* Key 1 long pressed */

	KEY_2_DOWN,				/* Key 2 pressed */
	KEY_2_UP,				/* Key 2 released */
	KEY_2_LONG,				/* Key 2 long pressed */

	KEY_3_DOWN,				/* Key 3 pressed */
	KEY_3_UP,				/* Key 3 released */
	KEY_3_LONG,				/* Key 3 long pressed */

	KEY_4_DOWN,				/* Key 4 pressed */
	KEY_4_UP,				/* Key 4 released */
	KEY_4_LONG,				/* Key 4 long pressed */

	KEY_5_DOWN,				/* Key 5 pressed */
	KEY_5_UP,				/* Key 5 released */
	KEY_5_LONG,				/* Key 5 long pressed */

	KEY_6_DOWN,				/* Key 6 pressed */
	KEY_6_UP,				/* Key 6Key  released */
	KEY_6_LONG,				/* Key 6 long pressed */

	KEY_7_DOWN,				/* Key 7 pressed */
	KEY_7_UP,				/* Key 7 released */
	KEY_7_LONG,				/* Key 7 long pressed */

	KEY_8_DOWN,				/* Key 8 pressed */
	KEY_8_UP,				/* Key 8 released */
	KEY_8_LONG,				/* Key 8 long pressed */

	/* Combination Key */
	KEY_9_DOWN,				/* Key 9 pressed */
	KEY_9_UP,				/* Key 9 released */
	KEY_9_LONG,				/* Key 9 long pressed */

	KEY_10_DOWN,			/* Key 10 pressed */
	KEY_10_UP,				/* Key 10 released */
	KEY_10_LONG,			/* Key 10 long pressed */
}KEY_ENUM;

/* FIFO Variables */
#define KEY_FIFO_SIZE	10
typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];		/* Key value buffer */
	uint8_t Read;					/* buffer read pointer 1 */
	uint8_t Write;					/* buffer write pointer */
	uint8_t Read2;					/* buffer read pointer 2 */
}KeyFIFO_TypeDef;

/* Function Declarations */
void bsp_InitKey(void);
void bsp_KeyScan(void);
void bsp_PutKey(uint8_t _KeyCode);
uint8_t bsp_GetKey(void);
uint8_t bsp_GetKey2(void);
uint8_t bsp_GetKeyState(KEYID_E _ucKeyID);
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t  _RepeatSpeed);
void bsp_ClearKey(void);

#endif

/*****************************  (END OF FILE) *********************************/
