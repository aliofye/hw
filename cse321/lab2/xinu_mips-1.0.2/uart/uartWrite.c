/**
 * @file uartWrite.c
 * @provides uartWrite
 *
 * $Id: uartWrite.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <uart.h>
#include <device.h>

/**
 * Write a buffer to the UART.
 *
 * @param pdev  pointer to UART device
 * @param buf   buffer of characters to write
 * @param len   number of characters to write from the buffer
 */
devcall uartWrite(device *pdev, unsigned char *buf, int len)
{
	irqmask ps;
	int count = 0;
	struct uart *puart;
	volatile struct uart_csreg *pucsr;

	/* Setup and error check pointers to structures */
	if (NULL == pdev)  {   return SYSERR;   }

	puart = (struct uart *)pdev->controlblk;
	if (NULL == puart) {   return SYSERR;   } 

	pucsr = puart->csr;
	if (NULL == pucsr) {   return SYSERR;   }

	ps = disable();

	/* If in non-blocking mode, ensure there is enough space for the entire
	 * write request */
	if (puart->oflags & UART_OFLAG_NOBLOCK)
	{
		if (scount(puart->osema) < len) {   restore(ps); return SYSERR;   }
	}

	/* Put each character from the buffer into the output buffer for the
	 * lower half */
	while (count < len)
	{
		/* If in non-blocking mode, ensure there is another byte of space
		 * for output */
		if (puart->oflags & UART_OFLAG_NOBLOCK)
		{
			if (scount(puart->osema) < 1) {   break;   }
		}

		/* If the UART transmitter hardware is idle, write directly to the
		 * hardware */
		if (puart->oidle)
		{
			puart->oidle = 0;
			pucsr->thr = *buf++;
			count++;
			puart->cout++;
		}
		/* Wait for space and place character in the output buffer for the
		 * lower half; Preserve the circular buffer */
		else
		{
			wait(puart->osema);
			puart->out[(puart->ostart + puart->ocount) % UART_OBLEN] = *buf++;
			count++;
			puart->ocount++;
		}
	}

	restore(ps);
	return count;
}
