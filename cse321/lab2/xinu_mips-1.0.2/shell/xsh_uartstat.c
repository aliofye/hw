/**
 * @file     xsh_uartstat.c
 * @provides xsh_uartstat
 *
 * $Id: xsh_uartstat.c 231 2007-07-12 14:15:16Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <device.h>
#include <uart.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

local uartStat(ushort, ushort, ushort, ushort);

/**
 * Shell command (uartstat UARTNUM) provides information about the current 
 * status of a UART.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 */
command xsh_uartstat(ushort stdin, ushort stdout, ushort stderr,
                     ushort nargs, char *args[])
{
	ushort dev;
	char   n;

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0) 
	{
		fprintf(stdout, "Usage: uartstat UARTNUM\n");
		fprintf(stdout, "Displays statistics for uart UARTNUM.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return OK;
	}

	/* Check for correct number of arguments */
	if (nargs < 2) 
	{
		for ( n = 0; n < NUART; n++ )
		{ uartStat( stdin, stdout, stderr, n ); }

		return OK;
	}

	if (nargs > 2) 
	{
		fprintf(stderr, "uartstat: too many arguments\n");
		fprintf(stderr, "Try 'uartstat --help' for more information\n");
		return SYSERR;
	}

	/* Check for valid device */
	dev = (ushort)atol(args[1]);
	if ( dev >= NUART )
	{
		fprintf(stderr, "uartstat: (%d) No such uart\n",dev);
		return SYSERR;
	}

	uartStat( stdin, stdout, stderr, dev );

	return OK;
}

local uartStat(ushort stdin, ushort stdout, ushort stderr, ushort dev)
{
	struct uart       *uptr;  /* pointer to uart entry     */
	struct uart_csreg *ucptr; /* pointer to uart registers */
	char   *label[2] = { "OFF", "ON " };

	/* Initialize pointers */
	uptr  = &uarttab[dev];  
	ucptr = uptr->csr;

	fprintf(stdout, "uart%d:\n", dev);

	/* UART statistics */
	fprintf(stdout, "\tSTATISTICS:\n");
	fprintf(stdout, "\t------------------------------------------\n");
	fprintf(stdout, "\t%8d Characters Output\n", uptr->cout);
	fprintf(stdout, "\t%8d Characters Input\n", uptr->cin);
	fprintf(stdout, "\t%8d Characters Overrun\n", uptr->ovrrn);
	fprintf(stdout, "\t%8d Receiver Error Count\n", uptr->lserr);
	fprintf(stdout, "\t%8d Output IRQ Count\n", uptr->oirq);
	fprintf(stdout, "\t%8d Input IRQ Count\n", uptr->iirq);

	/* Interrupt enable status */
	int enabled;
	fprintf(stdout, "\n\tINTERRUPT ENABLE:\n");
	fprintf(stdout, "\t------------------------------------------\n");

	enabled = (ucptr->ier & UART_IER_ERBFI) ? 1 : 0;
	fprintf(stdout, "\t%s  Receiver FIFO Reached Trigger Level\n",
	        label[enabled]);

	enabled = (ucptr->ier & UART_IER_ETBEI) ? 1 : 0;
	fprintf(stdout, "\t%s  Transmitter FIFO Empty\n", label[enabled]);

	enabled = (ucptr->ier & UART_IER_ELSI) ? 1 : 0;
	fprintf(stdout, "\t%s  Receiver Error or BREAK\n", label[enabled]);

	enabled = (ucptr->ier & UART_IER_EMSI) ? 1 : 0;
	fprintf(stdout, "\t%s  Modem Status", label[enabled]);

	fprintf(stdout, "\n");
	return OK;
}
