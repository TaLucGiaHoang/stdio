/*
 * printf.c
 *
 *  Created on: Oct 6, 2020
 *      Author:
 */
#include <stdarg.h>	/* va_list, va_arg() */
#include <stdint.h>

static int outbyte(int c)
{
// SiFive HiFive1 Revb1 uart0 registers
#define uart0_txdata    (*(volatile uint32_t*)(0x10013000))
#define UART_TXFULL             (1 << 31)
    while ((uart0_txdata & UART_TXFULL) != 0) { }
    uart0_txdata = c;
    return 0;
}

/*
	putchar is the only external dependency for this file,
	if you have a working putchar, leave it commented out.
	If not, uncomment the define below and
	replace outbyte(c) by your own function call.
*/

#define putchar(c) outbyte(c)

#include <stdarg.h>	/* va_list, va_arg() */

#include "do_printf.h"

/*****************************************************************************
 * PRINTF You must write your own putchar()
 *****************************************************************************/
static int vprintf_help(unsigned c, void **ptr){

	extern int putchar(int c);

//	ptr = ptr; /* to avoid unused varible warning */
	putchar(c);

	return 0;
}

static int vsprintf_help(unsigned int c, void **ptr){

	char *dst = *ptr;
	*dst++ = c;
	*ptr = dst;

	return 0 ;
}

int vsprintf(char *buffer, const char *fmt, va_list args){

	int ret_val = do_printf(fmt, args, vsprintf_help, (void *)buffer);
	buffer[ret_val] = '\0';

	return ret_val;
}

int sprintf(char *buffer, const char *fmt, ...){

	va_list args;
	int ret_val;

	va_start(args, fmt);
	ret_val = vsprintf(buffer, fmt, args);
	va_end(args);

	return ret_val;
}

int vprintf(const char *fmt, va_list args){

	return do_printf(fmt, args, vprintf_help, (void *)0);
}

int _printf(const char *fmt, ...){

	va_list args;
	int ret_val;

	va_start(args, fmt);
	ret_val = vprintf(fmt, args);
	va_end(args);

	return ret_val;
}

#if 0
#define printf _printf
#else
/*
 * Retarget functions for printf()
 */
#include <errno.h>
#include <sys/stat.h>
//#include <sys/types.h>
#include <unistd.h>

int _fstat (int file, struct stat * st) {
	errno = -ENOSYS;
	return -1;
}

int _write (int file, char * ptr, int len) {
	extern int putchar(int c);
	int i;

	if (file != STDOUT_FILENO) {
		errno = ENOSYS;
		return -1;
	}
	/* Turn character to capital letter and output to UART port */
	for (i = 0; i < len; i++) putchar((int)*ptr++);
	return 0;
}
#endif
