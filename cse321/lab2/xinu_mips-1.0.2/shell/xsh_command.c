/**
 * @file     xsh_test.c
 * @provides xsh_test
 *
 * $Id: xsh_test.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <stdio.h>
/**
 * Shell command (test) provides a mechanism for testing XINU features.  The
 * action and output varies depending on the feature currently being tested.
 * This is not meant to serve as a permanent shell command for a particular
 * action.
 * @param stdin descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command	xsh_command(ushort stdin, ushort stdout, ushort stderr,
                 ushort nargs, char *args[])
{	
    printf("Hello XINU world/n ");
	return OK;
}

