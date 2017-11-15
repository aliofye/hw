/**
 * @file uartControl.c
 * @provides uartControl
 *
 * $Id: uartControl.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <uart.h>
#include <device.h>

/**
 * Control parameters to a UART.
 * @param pdev  pointer to UART device
 * @param func  index of function to run (defined in uart.h)
 * @param arg1  first argument to called function
 * @param arg2  second argument to called function
 */
devcall uartControl(device *pdev, int func, unsigned char arg1, unsigned char arg2)
{  
	struct uart *puart  = (struct uart *)pdev->controlblk;
	char         temp;

	switch (func) 
	{

	/* Set input mode flags: arg1 = flags to set */
	/* return = old value of flags               */
	case UART_IOC_SETIFLAG:
		temp = puart->iflags & arg1;
		puart->iflags |= (arg1);
		return temp;

	/* Clear input mode flags: arg1 = flags to clear */
	/* return = old value of flags                   */ 
	case UART_IOC_CLRIFLAG:
		temp = puart->iflags & arg1;
		puart->iflags &= ~(arg1);
		return temp;

	/* Get input flags: return = current value of flags */
	case UART_IOC_GETIFLAG:
		return puart->iflags;

	/* Set output mode flags: arg1 = flags to set */
	/*  return = old value of flags               */
	case UART_IOC_SETOFLAG:
		temp = puart->oflags & arg1;
		puart->oflags |= (arg1);
		return temp;

	/* Clear output mode flags: arg1 = flags to clear */
	/* return = old value of flags                    */ 
	case UART_IOC_CLROFLAG:
		temp = puart->oflags & arg1;
		puart->oflags &= ~(arg1);
		return temp;

	/* Get output flags: return = current value of flags */
	case UART_IOC_GETOFLAG:
		return puart->oflags;

	/* Determine if the UART transmitter is idle, return TRUE if idle */
	case UART_IOC_OUTPUT_IDLE:
		return puart->oidle;

	}
	return SYSERR;
}
