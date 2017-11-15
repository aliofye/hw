/**
 * @file     xsh_memstat.c
 * @provides xsh_memstat
 *
 * $Id: xsh_memstat.c 446 2008-04-30 18:49:43Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <platform.h>
#include <mips.h>
#include <memory.h>
#include <proc.h>
#include <stdio.h>
#include <string.h>

extern char *maxaddr;
extern void *end;
extern void _start(void);

/**
 * Shell command (gpiostat) provides memory use and free list information.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_memstat(ushort stdin, ushort stdout, ushort stderr,
                    ushort nargs, char *args[])
{
	struct memblock *mptr; /* pointer to memory block       */
	ulong phys = 0;        /* total physical memory         */
	ulong resrv = 0;       /* total reserved system memory  */
	ulong code = 0;        /* total XINU code memory        */
	ulong stack = 0;       /* total stack memory            */
	ulong heap = 0;        /* total heap memory             */
	ulong free = 0;        /* total free memory             */
	long  i;               /* temp variable                 */

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0)
	{
		fprintf(stdout, "Usage: memstat\n");
		fprintf(stdout, "Displays the current memory usage and prints the");
		fprintf(stdout, "free list.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return OK;
	}

	/* Check for correct number of arguments */
	if (nargs > 1)
	{
		fprintf(stderr, "memstat: too many arguments\n");
		fprintf(stderr, "Try 'memstat --help' for more information\n");
		return SYSERR;
	}

	/* Calculate amount of physical memory */
	phys = (ulong)platform.maxaddr - (ulong)KSEG0_BASE;

	/* Calculate amount of reserved system memory */
	resrv = (ulong)_start - (ulong)KSEG0_BASE;

	/* Calculate amount of text memory */
	code = (ulong)&end - (ulong)_start;

	/* Caculate amount of stack memory */
	for (i=0; i<NPROC; i++)
	{
		if (proctab[i].state != PRFREE)
		{
			stack += (ulong)proctab[i].stklen;
		}
	}

	/* Calculate amount of free memory */
	for (mptr = freelist.next; mptr != NULL; mptr = mptr->next)
	{ free += mptr->length; }

	/* Caculate amount of heap memory */
	heap = phys - resrv - code - stack - free;

	/* Ouput current memory usage */
	fprintf(stdout,"Current System Memory Usage:\n");
	fprintf(stdout,"----------------------------\n");
	fprintf(stdout,"%10d bytes system area\n", resrv);
	fprintf(stdout,"%10d bytes XINU code\n", code);
	fprintf(stdout,"%10d bytes stack space\n", stack);
	fprintf(stdout,"%10d bytes heap space\n", heap);
	fprintf(stdout,"%10d bytes free space\n", free);
	fprintf(stdout,"----------------------------\n");
	fprintf(stdout,"%10d bytes physical memory\n", phys);

	/* check computed free size against maintained free size */
	if ( freelist.length != free )
	{
		fprintf(stderr, "\nPotential memory leak detected:\n");
		fprintf(stderr, "\nComputed free memory: %10d bytes\n", free);
		fprintf(stderr, "Maintained free memory: %10d bytes\n\n",
		        freelist.length);
	}

	/* Output free list */
	fprintf(stdout,"Free List:\n");
	fprintf(stdout,"BLOCK START  LENGTH  \n");
	fprintf(stdout,"-----------  --------\n");

	for (mptr=freelist.next; mptr != NULL; mptr=mptr->next)
	{ fprintf(stdout,"0x%08X   %8d\n", mptr, mptr->length); }

  return OK;
}
