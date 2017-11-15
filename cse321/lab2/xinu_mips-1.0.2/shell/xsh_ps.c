/**
 * @file     xsh_ps.c 
 * @provides xsh_ps
 *
 * $Id: xsh_ps.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Shell command (ps) outputs process table information.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 */
command xsh_ps(ushort stdin, ushort stdout, ushort stderr,
               ushort nargs, char *args[])
{
	pcb   *ppcb; /* pointer to process entry */
	uchar i;     /* temp variable            */

	/* readable names for PR* status in proc.h */
	char *pstnams[] =
	{ "curr ", "free ", "ready", "recv ",
	  "sleep", "susp ", "wait ", "rtim " };

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0)
	{
		fprintf(stdout, "Usage: ps\n");
		fprintf(stdout, "Displays a table of running processes.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");

		return OK;
	}

	/* Check for correct number of arguments */
	if (nargs > 1) 
	{
		fprintf(stderr, "ps: too many arguments\n");
		fprintf(stderr, "Try 'ps --help' for more information\n");
		return SYSERR;
	}

	/* Output process table header */
	fprintf(stdout,
	  "PID NAME         STATE PRIO PPID STACK BASE STACK PTR  STACK LEN \n");
	fprintf(stdout,
	  "--- ------------ ----- ---- ---- ---------- ---------- ----------\n");

	/* Output information for each process */
	for ( i = 0; i < NPROC; i++ )
	{
		ppcb = &proctab[i];
		if (ppcb->state == PRFREE) { continue; }

		fprintf(stdout, "%3d %-12s %s %4d %4d 0x%08X 0x%08X %10d\n", 
				i, ppcb->name, pstnams[(int)ppcb->state-1],
		        ppcb->prio, ppcb->parent, ppcb->stkbase,
		        ppcb->stkptr, ppcb->stklen);
	}

	return OK;
}
