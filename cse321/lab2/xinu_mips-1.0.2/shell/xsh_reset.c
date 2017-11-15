/**
 * @file     xsh_reset.c
 * @provides xsh_reset
 *
 * $Id: xsh_reset.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <gpio.h>
#include <stdio.h>
#include <string.h>

/**
 * Shell command (reset) performs a soft restart of the router.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_reset(ushort stdin, ushort stdout, ushort stderr,
                  ushort nargs, char *args[])
{
	struct gpio_csreg *pgcsr; /* pointer to gpio registers     */

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0)
	{
		fprintf(stdout, "Usage: reset\n");
		fprintf(stdout, "Performs a soft reset of the router.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return SYSERR;
	}
	
	/* Check for correct number of arguments */
	if (nargs > 1) 
	{
		fprintf(stderr, "reset: too many arguments\n");
		fprintf(stderr, "Try 'reset --help' for more information\n");
		return SYSERR;
	}

	/* Initialize pointers */
	pgcsr = (struct gpio_csreg *)GPIO_BASE;

	/* Reset router */
	pgcsr->input |= GPIO_BUT_RESET;

	return OK;
}
