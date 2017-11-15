/**
 * @file clkintr.c
 * @provides clockintr
 *
 * $Id: clockintr.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <clock.h>

extern void wakeup(void);
extern syscall resched(void);
extern void restore_intr(void *);

/**
 * XINU Clock handler.
 * Ticks. Tocks. Wakes up sleeping procs.
 */
interrupt clockintr(void)
{
	clock_update(time_intr_freq);

	/* Another millisecond has passed. */
	ctr_mS--;

	/* Update global second counter. */
	if (0 == ctr_mS) 
	{
		clocktime++;
		ctr_mS = 1000;
	}

	/* If sleepq is not empty, decrement first key.   */
	/* If key reaches zero, call wakeup.              */
	if (nonempty(sleepq))
	{
		if (--firstkey(sleepq) <= 0)
		restore_intr(&wakeup);
	}

	/* Check to see if this proc should be preempted. */
	if (--preempt <= 0)
	{  
		restore_intr(&resched);
	}
}
