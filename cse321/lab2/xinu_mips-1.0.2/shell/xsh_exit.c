/**
 * @file     xsh_exit.c
 * @provides xsh_exit
 *
 * $Id: xsh_exit.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>

/**
 * Shell command (exit) closes the shell.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command	xsh_exit(ushort stdin, ushort stdout, ushort stderr,
                 ushort nargs, char *args[])
{
	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0)
	{
		fprintf(stdout, "Usage: exit\n");
		fprintf(stdout, "Closes the XINU shell.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return SYSERR;
	}

	/* Check for correct number of arguments */
	if (nargs > 1) 
	{
		fprintf(stderr, "exit: too many arguments\n");
		fprintf(stderr, "Try 'exit --help' for more information.\n");
		return SYSERR;
	}

	fprintf(stdout, SHELL_EXIT);
	sleep(10);
	kill(getpid());

	return OK;
}
