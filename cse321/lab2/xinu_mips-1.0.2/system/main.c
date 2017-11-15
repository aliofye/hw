/**
 * @file     main.c
 * @provides main
 *
 * $Id: main.c 446 2008-04-30 18:49:43Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include<kernel.h>
#include<stdio.h>
#include<proc.h>

extern void shell(int);

extern ulong cpuid;

int main(int argc, char **argv)
{
	/* Associate TTY1 with second serial port. */
	open(TTY1, SERIAL1);
	enable();

	/* Launch one shell process for each TTY device. */
	ready(create((void *)shell, INITSTK, INITPRIO, "SHELL0", 1, CONSOLE),
	      RESCHED_NO);
	ready(create((void *)shell, INITSTK, INITPRIO, "SHELL1", 1, TTY1),
	      RESCHED_NO);

	return 0;
}
