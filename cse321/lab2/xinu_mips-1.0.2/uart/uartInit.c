/**
 * @file uartInit.c
 * @provides uartInit
 *
 * $Id: uartInit.c 235 2007-07-12 22:52:09Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <uart.h>
#include <kernel.h>
#include <platform.h>
#include <interrupt.h>
#include <device.h>
#include <mips.h>
#include <stdlib.h>

struct uart uarttab[NUART];
extern void uartIntr(void);
extern long cpuid;

/**
 * Initialize UART control and status registers and buffers.
 * @param pdev pointer to a uart device
 */
devcall uartInit(device *pdev)
{
	struct uart *puart;
	struct uart_csreg *pucsr;

	/* Initialize structure pointers */
	puart = uarttab + pdev->minor;
	bzero((void *)puart, sizeof(struct uart));
	pdev->controlblk   = (void *)puart;
	puart->dev  = pdev;
	puart->csr  =  (struct uart_csreg *)pdev->csr;
	pucsr = puart->csr;

	/* Initialize statistical counts */
	puart->cout = 0;
	puart->cin  = 0;
	puart->lserr= 0;
	puart->ovrrn= 0;
	puart->iirq = 0;
	puart->oirq = 0;
	
	/* Initialize input buffer */
	puart->isema  = newsem(0);
	puart->iflags = 0;
	puart->istart = 0;
	puart->icount = 0;
	
	/* Initialize output buffer */
	puart->osema  = newsem(UART_OBLEN);
	puart->oflags = 0;
	puart->ostart = 0;
	puart->ocount = 0;
	puart->oidle = 1;

	/* Set baud rate */
	pucsr->lcr = UART_LCR_DLAB;       /* Set Divisor Latch Access Bit */
	pucsr->dll = platform.uart_dll;   /* Set Divisor Latch Low Bytel  */
	pucsr->dlm = 0x00;                /* Set Divisor Latch High Byte  */
	
	pucsr->lcr = UART_LCR_8N1;        /* 8 bit, No Parity, 1 Stop    */
	pucsr->fcr = 0x00;                /* Disable FIFO for now        */
	pucsr->mcr = UART_MCR_OUT2;       /* Turn on user-defined OUT2.  */
	/* OUT2 is used to control the board's interrupt tri-state            */
	/* buffer. It should be set high to generate interrupt properly.      */
	
	/* Enable interrupts */
	pucsr->ier = UART_IER_ERBFI | UART_IER_ETBEI | UART_IER_ELSI; 
	
	/* Enable UART hardware FIFOs, clear contents and set interrupt trigger level */
	puart->csr->fcr = UART_FCR_EFIFO | UART_FCR_RRESET | UART_FCR_TRESET | UART_FCR_TRIG2;
	
	/* Enable processor handling of UART interrupt requests */
	interruptVector[IRQ_UART] = pdev->inintr;
	enable_irq(pdev->inmask);

	return OK;
}
