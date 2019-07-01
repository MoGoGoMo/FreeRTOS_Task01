/**
******************************************************************************
* @file    Project/F446_T1/bsp_uart_fifo.h
* @author  Gordon Tao
* @version V0.1
* @date    27-June-2019
* @brief   Header file of UART  module
******************************************************************************
* @attention
* @Modified_log:
* Versions:            Date              Author            Description
* 0.1              2019-06-27           Gordon         first version of USART function
*
* <h2><center>&copy; COPYRIGHT 2019 MOGO Technology</center></h2>
*
******************************************************************************
*/

#ifndef _BSP_UART_FIFO_H_
#define _BSP_UART_FIFO_H_


/*
 *   If need to change the GPIO of USART, You coulde modify the function: static void initUsartHard(void) in bsp_usart_fifo.c
 */

/* Enable USART, 0=Disable, 1=Enable */
#ifdef STM32_F446RET

  #define UART1_FIFO_EN 0
  #define UART2_FIFO_EN 1
  #define UART3_FIFO_EN 0
  #define UART4_FIFO_EN 0
  #define UART5_FIFO_EN 0
  #define UART6_FIFO_EN 0
#else

#endif


typedef enum
{
 /* USART1 TX=PA9 RX=PA10 or TX=PB6 RX=PB7  */
 COM1 = 0x00,
 /* USART2 TX=PA2 RX=PA3 */
 COM2 = 0x01,
 /* USART3 TX=PB10 RX=PB11 */
 COM3 = 0x02,
 /* UART4 TX=PC10, RX=PC11 */
 COM4 = 0x03,
 /* UART5 TX=PC12 RX=PD2 */
 COM5 = 0x04,
 /* USART6 TX=PC6 RX=PC7 */
 COM6 = 0x05
}UartPort_TypeDef;

/* Define Baudrate && FIFO Buffer Sizes */
#if UART1_FIFO_EN== 1
    #define UART1_BAUD           115200
    #define UART1_TX_BUF_SIZE    1*1024
    #define UART1_RX_BUF_SIZE    1*1024
#endif

#if UART2_FIFO_EN== 1
#define UART1_BAUD           115200
#define UART1_TX_BUF_SIZE    1*1024
#define UART1_RX_BUF_SIZE    1*1024
#endif

#if UART3_FIFO_EN== 1
#define UART1_BAUD           115200
#define UART1_TX_BUF_SIZE    1*1024
#define UART1_RX_BUF_SIZE    1*1024
#endif

#if UART4_FIFO_EN== 1
#define UART1_BAUD           115200
#define UART1_TX_BUF_SIZE    1*1024
#define UART1_RX_BUF_SIZE    1*1024
#endif

#if UART5_FIFO_EN== 1
#define UART1_BAUD           115200
#define UART1_TX_BUF_SIZE    1*1024
#define UART1_RX_BUF_SIZE    1*1024
#endif

#if UART6_FIFO_EN== 1
#define UART1_BAUD           115200
#define UART1_TX_BUF_SIZE    1*1024
#define UART1_RX_BUF_SIZE    1*1024
#endif

/* Uart device instructure definition */
typedef struct
{
   USART_TypeDef *
}
