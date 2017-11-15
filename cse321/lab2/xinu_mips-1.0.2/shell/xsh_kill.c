/**
 * @file     xsh_kill.c
 * @provides xsh_kill
 *
 * $Id: xsh_kill.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Shell command (kill) terminates a process.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_kill(ushort stdin, ushort stdout, ushort stderr,
                 ushort nargs, char *args[])
{
	long pid; /* pid for process to kill */

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0) 
	{
		fprintf(stdout, "Kills a process number PID.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return OK;
	}

	/* Check for correct number of arguments */
	if (nargs < 2) 
	{
		fprintf(stderr, "kill: missing operand\n");
		fprintf(stderr, "Try 'kill --help' for more information\n");
		return SYSERR;
	}
	if (nargs > 2) 
	{
		fprintf(stderr, "kill: too many arguments\n");
		fprintf(stderr, "Try 'kill --help' for more information\n");
		return SYSERR;
	}

	pid = atol(args[1]);

	/* Block killing of the null process */
	if (pid == NULLPROC)
	{
		fprintf(stderr, "kill: (%d) Operation not permitted\n",pid);
		return SYSERR;
	}

	/* Notify of killing of the shell */
	if (pid == getpid())
	{
		fprintf(stderr, "kill: Shell killed\n");
		sleep(2000);
	}

	/* Kill process, noting if kill failed */
	int result = kill(pid);
	if (result == SYSERR)
	{
		fprintf(stderr, "kill: (%d) No such process\n",pid);
	}

	return result;
}
