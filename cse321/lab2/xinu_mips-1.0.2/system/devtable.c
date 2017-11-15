/**
 * @file devtable.c
 *
 * $Id: devtable.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <interrupt.h>
#include <uart.h>
#include <tty.h>

/* Declarations of I/O routines referenced */
extern devcall ioerr(void);
extern devcall ionull(void);

device devtab[NDEVS] =
{
/**
 * Format of entries is:
 * num, name,
 * init, open, close,
 * read, write, seek,
 * getc, putc, control,
 * csr, inmask, outmask,
 * inintr, outintr, controlblk, minor
 */

/* SERIAL0 is (void *)uart */
	{ 0, "SERIAL0",
	  (void *)uartInit, (void *)ionull, (void *)ionull,
	  (void *)uartRead, (void *)uartWrite, (void *)ioerr,
	  (void *)uartGetChar, (void *)uartPutChar, (void *)uartControl,
	  (void *)0xB8000300, IRQ_UART, IRQ_UART,
	  uartIntr, uartIntr, NULL, 0},

/* SERIAL1 is (void *)uart */
	{ 1, "SERIAL1",
	  (void *)uartInit, (void *)ionull, (void *)ionull,
	  (void *)ionull, (void *)uartWrite, (void *)ioerr,
	  (void *)uartGetChar, (void *)uartPutChar, (void *)uartControl,
	  (void *)0xB8000400, IRQ_UART, IRQ_UART,
	  uartIntr, uartIntr, NULL, 1},

/* CONSOLE is (void *)tty  */

	{ 2, "CONSOLE",
	  (void *)ttyInit, (void *)ttyOpen, (void *)ttyClose,
	  (void *)ttyRead, (void *)ttyWrite, (void *)ioerr,
	  (void *)ttyGetChar, (void *)ttyPutChar, (void *)ttyControl,
	  0000000, 0000, 0000,
	  (void *)ioerr, (void *)ioerr, NULL, 0 },

/* TTY1 is (void *)tty     */

	{ 3, "TTY1",
	  (void *)ttyInit, (void *)ttyOpen, (void *)ttyClose,
	  (void *)ttyRead, (void *)ttyWrite, (void *)ioerr,
	  (void *)ttyGetChar, (void *)ttyPutChar, (void *)ttyControl,
	  0000000, 0000, 0000,
	  (void *)ioerr, (void *)ioerr, NULL, 1 }
};
