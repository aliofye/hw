/**
 * @file     xsh_gpiostat.c
 * @provides xsh_gpiostat
 *
 * $Id: xsh_gpiostat.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <gpio.h>
#include <stdio.h>
#include <string.h>

/**
 * Shell command (gpiostat) provides information about the current status
 * of the GPIO pins.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_gpiostat(ushort stdin, ushort stdout, ushort stderr,
                     ushort nargs, char *args[])
{
	struct gpio_csreg *pgcsr;           /* pointer to gpio registers     */
	uchar  p;
	ulong offset;

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0)
	{
		fprintf(stdout, "Usage: gpiostat\n");
		fprintf(stdout, "Displays statitics for general purpose ");
		fprintf(stdout, "input/output pins.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return SYSERR;
	}

	/* Check for correct number of arguments */
	if (nargs > 1) 
	{
		fprintf(stderr, "gpiostat: too many arguments\n");
		fprintf(stderr, "Try 'gpiostat --help' for more information.\n");
		return SYSERR;
	}

	/* Initialize pointers */
	pgcsr = (struct gpio_csreg *)GPIO_BASE;

	/* Output GPIO pin status */
	offset = 0;

	fprintf(stdout, "PIN MODE   INPUT   OUTPUT  CONTROL\n");
	fprintf(stdout, "--- ------ ------- ------- -------\n");
	for (p = 0; p < GPIO_PIN_COUNT; p++)
	{
		offset = 1 << p;
		fprintf(stdout, "%2d ", p);
		if (pgcsr->enable & offset)
		{ fprintf(stdout, " Output "); }
		else
		{ fprintf(stdout, " Input  "); }
		fprintf(stdout, "   %1d    ", (pgcsr->input & offset) >> p);
		fprintf(stdout, "   %1d    ", (pgcsr->output & offset) >> p);
		fprintf(stdout, "   %1d    ", (pgcsr->control & offset) >> p);
		fprintf(stdout, "\n");
	}
	
	return OK;
}
