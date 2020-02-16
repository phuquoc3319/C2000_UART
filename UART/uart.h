/*
 * uart.h
 *
 *  Created on: Jan 26, 2020
 *      Author: RICHARD
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include "device.h"
#include "driverlib.h"
#include "string.h"

void UART1_Init(uint32_t Baudrate);

__interrupt void UART1_RX(void);
__interrupt void UART1_TX(void);

#endif /* UART_UART_H_ */
