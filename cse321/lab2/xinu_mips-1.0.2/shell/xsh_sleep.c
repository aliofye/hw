/**
 * @file     xsh_sleep.c
 * @provides xsh_sleep
 *
 * $Id: xsh_sleep.c 231 2007-07-12 14:15:16Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Shell command (sleep DELAY) delay for a given number of seconds.
 * @param stdin descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_sleep(ushort stdin, ushort stdout, ushort stderr,
                  ushort nargs, char *args[])
{
	long delay; /* time to sleep */

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0) 
	{
		fprintf(stdout, "Usage:sleep DELAY\n");
		fprintf(stdout, "Sleep for DELAY seconds.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return OK;
	}

	/* Check for correct number of arguments */
	if (nargs < 2)
	{
		fprintf(stderr,"sleep: missing operand\n");
		fprintf(stderr,"Try 'sleep --help' for more information\n");
		return SYSERR;
	}
	if (nargs > 2)
	{
		fprintf(stderr,"sleep: too many arguments\n");
		fprintf(stderr,"Try 'sleep --help' for more information\n");
		return SYSERR;
	}

	/* Calculate delay and sleep */
	delay = atol(args[1]);
	if (delay < 0)
	{
		fprintf(stderr,"sleep: invalid delay of %d seconds\n");
	}
	return sleep(delay * 1000);
}
