/** 
 * @file     xsh_help.c
 * @provides xsh_help
 *
 * $Id: xsh_help.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>

/**
 * Shell command (help) provides a list of commands recognized by the
 * shell, or displays help information for a particular command.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_help(ushort stdin, ushort stdout, ushort stderr,
                 ushort nargs, char *args[])
{
	uchar i;
	char *command_args[2]; /* temporary storage for [command] --help */

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0) 
	{
		fprintf(stdout, "Usage: help [command]\n");
		fprintf(stdout, "Provides a list of commands for the shell.\n");
		fprintf(stdout, "If command is provided, help information will ");
		fprintf(stdout, "be provided for the specified command; equivalent ");
		fprintf(stdout, "to entering 'command --help' into the shell.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return OK;
	}

	/* Check for correct number of arguments */
	if (nargs > 2) 
	{
		fprintf(stderr, "help: too many arguments\n");
		fprintf(stderr, "Try 'help --help' for more information.\n");
		return SYSERR;
	}

	/* Output help for specific command, if 'command' argument was supplied */
	if (nargs == 2)
	{
		for ( i = 0; i < ncommand; i++)
		{
			if (strncmp(args[1],commandtab[i].name,6) == 0)
			{
				command_args[0] = args[2];
				command_args[1] = "--help";
				(*commandtab[i].procedure)(stdin, stdout, stderr,
				                           2, command_args);
				return OK;
			}
		}
		fprintf(stdout, "help: no help topics match '%s'.  Try 'help --help'");
		fprintf(stdout, "for more information.\n");
		return SYSERR;
	}

	/* Output command list */
	fprintf(stdout, "Shell Commands:\n");
	for( i = 0; i < ncommand; i++)
	{ fprintf(stdout, "\t%s\n", commandtab[i].name); }

	return OK;
}
