/**
 * @file getpid.c
 * @provides getpid
 *
 * $Id: getpid.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>

/**
 * Get the process id of currently executing process.
 * @return process id of the currently running process
 */
syscall getpid(void)
{
	return(currpid);
}
