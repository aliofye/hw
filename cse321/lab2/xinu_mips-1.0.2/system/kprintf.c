/**
 * @file kprintf.c
 * @provides kputc, kprintf
 *
 * $Id: kprintf.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <vararg.h>
#include <device.h>
#include <stdio.h>
#include <uart.h>

/**
 * kputc - perform a synchronous kernel write to the console tty
 * @param *pdev pointer to device on which to write character
 * @param c character to write
 * @return c on success, SYSERR on failure
 */
syscall kputc(device *pdev, unsigned char c)
{
	int status, irmask;
	struct uart *puart;
	volatile struct uart_csreg *pucsr;

	if (NULL == pdev) { return SYSERR; }
	puart  = (struct uart *)pdev->controlblk;
	if (NULL == puart) { puart = &uarttab[0]; }
	pucsr = puart->csr;
	if (NULL == pucsr) { pucsr = (struct uart_csreg *)pdev->csr; }

	irmask = pucsr->ier;        /* Save UART interrupt state.   */
	pucsr->ier = 0;             /* Disable UART interrupts.     */

	do                               /* Wait for transmitter         */
	{
		status = pucsr->lsr;
	}
	while ( (status & UART_LSR_TEMT) !=  UART_LSR_TEMT );

/* Send character. */
	pucsr->thr = c;
	puart->cout++;

	pucsr->ier = irmask;        /* Restore UART interrupts.     */
	return c;
}

/**
 * kprintf - kernel printf: formatted, unbuffered output to CONSOLE
 * @param *fmt pointer to string being printed
 * @return OK on success
 */
syscall kprintf(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	_doprnt(fmt, ap, (int (*)(int, int))kputc, (int)&devtab[SERIAL0]);
	va_end(ap);
	return OK;
}

