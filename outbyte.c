/*
 * outbyte.c
 *
 *  Created on: Oct 6, 2020
 *      Author:
 *
 *  Change outbyte to your own function call
 */

#include <stdint.h>

int outbyte(int c)
{
// SiFive HiFive1 Revb1 uart0 registers
#define uart0_txdata    (*(volatile uint32_t*)(0x10013000))
#define UART_TXFULL             (1 << 31)
    while ((uart0_txdata & UART_TXFULL) != 0) { }
    uart0_txdata = c;
    return 0;
}
