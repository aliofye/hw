/**
 * @file uartRead.c
 * @provides uartRead
 *
 * $Id: uartRead.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <uart.h>
#include <device.h>

/**
 * Read into a buffer from the UART.
 * @param pdev UART device table entry
 * @param buf buffer to read bytes into
 * @param len size of the buffer
 * @return count of bytes read
 */
devcall uartRead(device *pdev, unsigned char *buf, int len)
{
	irqmask ps;
	int count = 0;
	char c;
	struct uart *puart;

	/* Setup and error check pointers to structures */
	ASSERT(NULL != pdev);
	puart = (struct uart *)pdev->controlblk;
	ASSERT(puart != NULL);

	ps = disable();

	/* If in non-blocking mode, ensure there is */
    /* enough input for the entire read request */
	if(puart->iflags & UART_IFLAG_NOBLOCK)
	{
		if (scount(puart->isema) < len)
			{  restore(ps); return SYSERR;  }
	}

	/* Put each character into the buffer from the input buffer */
	while (count < len)
	{
		/* If in non-blocking mode, ensure there is another byte of input */
		if(puart->iflags & UART_IFLAG_NOBLOCK)
		{
			if (scount(puart->isema) < 1)
				{  break;  }
		}

		/* Wait for input and read character from the  */
		/* input buffer; Preserve the circular buffer  */
		wait(puart->isema);
		c = puart->in[puart->istart];
		*buf++ = c;
		puart->icount--;
		puart->istart = (puart->istart + 1) % UART_IBLEN;
		count++;

		/* If echo is enabled, echo the character */
		if (puart->iflags & UART_IFLAG_ECHO)
			{ uartPutChar(puart->dev,c); }
	}

	restore(ps);
	return count;
}
