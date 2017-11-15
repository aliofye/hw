/**
 * @file wakeup.c
 * @provides wakeup                                                       
 *
 * $Id: wakeup.c 217 2007-07-11 01:03:18Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <queue.h>
#include <clock.h>

/**
 * Called by clock interrupt dispatcher to awaken processes.
 */
void wakeup(void)
{
	/* wakeup all processes that have no more time to sleep */
	while ( nonempty(sleepq) && (firstkey(sleepq) <= 0) )
	{
		/* prepare the process, but we need to wake up all       */
		/* processes (possibly more important) which have lapsed */
		ready(dequeue(sleepq), RESCHED_NO);
	}

	/* All timed out processes are awake, a now awake process    */
	/* may be more important than the currently running process  */
	/* so we need a forced reschedule.                           */
	resched();
	return;
}
