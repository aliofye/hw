/**
 * @file sleep.c
 * @provides sleep                                                         
 *
 * $Id: sleep.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <queue.h>
#include <clock.h>

/**
 * Delay the calling process n milliseconds.
 * @param ms number of milliseconds to sleep
 * @return OK if process is sleeping, SYSERR if no clock
 */
syscall	sleep(int ms)
{
	irqmask ps;

#ifdef RTCLOCK
	ASSERT( ms >= 0 );

	if (ms > 0) 
	{
		/* tinkering with processes, no interrupts */
		ps = disable();
		insertd(currpid, sleepq, ms);
		proctab[currpid].state = PRSLEEP;
		restore(ps);
	}

	resched();
	return OK;
#elif
	/* if we have no clock, sleep was an erroneous call */
	return SYSERR;
#endif
}
