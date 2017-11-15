/**
 * @file     xsh_led.c
 * @provides xsh_led
 *
 * $Id: xsh_led.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <gpio.h>
#include <stdio.h>
#include <string.h>

/**
 * Shell command (led DESCRIPTOR STATE) turns a specified led on or off.
 * @param stdin  descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_led(ushort stdin, ushort stdout, ushort stderr,
                ushort nargs, char *args[])
{
	ulong led; /* led to control */

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0) 
	{
		fprintf(stdout, "Usage:led DESCRIPTOR STATE\n");
		fprintf(stdout, "Turns a specified led on or off.\n");
		fprintf(stdout, "\tDESCRIPTOR: dmz, wlan, power, ciscow, ciscoo\n");
		fprintf(stdout, "\tSTATE: on, off\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return OK;
	}

	/* Check for correct number of arguments */
	if (nargs < 3)
	{
		fprintf(stderr,"led: missing operand\n");
		fprintf(stderr,"Try 'led --help' for more information\n");
		return SYSERR;
	}
	if (nargs > 3)
	{
		fprintf(stderr,"led: too many arguments\n");
		fprintf(stderr,"Try 'led --help' for more information\n");
		return SYSERR;
	}

	/* find led to change */
	if (strncmp(args[1],"dmz",3) == 0) { led = GPIO_LED_DMZ; }
	else if (strncmp(args[1],"wlan",4) == 0) { led = GPIO_LED_WLAN; }
	else if (strncmp(args[1],"power",5) == 0) { led = GPIO1; }
	else if (strncmp(args[1],"ciscow",6) == 0) { led = GPIO_LED_CISCOWHT; }
	else if (strncmp(args[1],"ciscoo",6) == 0) { led = GPIO_LED_CISCOONG; }
	else
	{
		fprintf(stderr,"led: invalid DESCRIPTOR\n");
		fprintf(stderr,"Try 'led --help' for more information\n");
	}
	
	/* change led state */
	if (strncmp(args[2],"on",2) == 0) { GPIO_CTRL_LED_ON(led); }
	else if (strncmp(args[2],"off",3) == 0) { GPIO_CTRL_LED_OFF(led); }
	else
	{
		fprintf(stderr,"led: invalid STATE\n");
		fprintf(stderr,"Try 'led --help' for more information\n");
	}

	return OK;
}
