/**
 * @file uartIntr.c
 * @provides uartIntr
 *
 * $Id: uartIntr.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <uart.h>
#include <semaphore.h>

/**
 * Decode hardware interrupt request from UART device.
 */
interrupt uartIntr(void)
{
	short u = 0, iir = 0, lsr = 0, count = 0;
	char c;
	struct uart       *puart = NULL;
	struct uart_csreg *pucsr = NULL;

	for (u = 0; u < NUART; u++)
	{
		puart = &uarttab[u];
		if (NULL == puart) { continue; }
		pucsr = puart->csr;
		if (NULL == pucsr) { continue; }

		/* Check interrupt identification register */
		iir = pucsr->iir;      
		if (iir & UART_IIR_IRQ) { continue; }

		/*
		 * Decode interrupt cause based upon the value taken from the
		 * UART interrupt identification register.  Clear interrupt source,
		 * and perform the appropriate handling to coordinate properly
		 * with the upper half of the driver.
		 */

		/* Decode interrupt cause */
		iir &= UART_IIR_IDMASK; 
		switch (iir)
		{
		/* Receiver line status interrupt */
		case UART_IIR_RLSI: 
			lsr = pucsr->lsr;
			puart->lserr++;
			break;

		/* Receiver data available or timed out */
		case UART_IIR_RDA:
		case UART_IIR_RTO:
			puart->iirq++;
			count = 0;
			while (pucsr->lsr & UART_LSR_DR)
			{
				c = pucsr->buffer;
				if (puart->icount < UART_IBLEN)
				{
					puart->in[(puart->istart+puart->icount) % UART_IBLEN] = c;
					puart->icount++;
					count++;
				}
				else
				{
					puart->ovrrn++;
				}
			}
			puart->cin += count;
			signaln(puart->isema, count);
			break;

		/* Transmitter holding register empty */
		case UART_IIR_THRE:
			puart->oirq++;
			lsr = pucsr->lsr;   /*Read from LSR to clear interrupt     */
			count = 0;
			if (puart->ocount > 0)
			{
				do
				{
					count++;
					puart->ocount--;
					pucsr->buffer = puart->out[puart->ostart];
					puart->ostart = (puart->ostart + 1) % UART_OBLEN;
				} while ((count < UART_FIFO_LEN) && (puart->ocount > 0));
			}

			if (count)
			{
				puart->cout += count;
				signaln(puart->osema, count);
			}
			else
			{
				puart->oidle = 1;
			}
			break;

		/* Modem status change */
		case UART_IIR_MSC:                   
			break;
		}
	}
}
