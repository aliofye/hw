/**
 * @file resched.c
 * @provides resched
 *
 * $Id: resched.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <clock.h>
#include <queue.h>

extern void ctxsw(void *, void *);
/**
 * Reschedule processor to highest priority ready process.
 * Upon entry, currpid gives current process id.  Proctab[currpid].pstate 
 * gives correct NEXT state for current process if other than PRREADY.
 * @return OK when the process is context switched back
 */
syscall resched(void)
{
	pcb *oldproc;   /* pointer to old process entry */
	pcb *newproc;   /* pointer to new process entry */

	oldproc = &proctab[ currpid ];

	oldproc->irqstate = disable();

	/* place current process at end of ready queue */
	if (PRCURR == oldproc->state) 
	{
		oldproc->state = PRREADY;
		insert(currpid, readylist, oldproc->prio);
	}

	/* remove highest priority process in ready queue */
	currpid = dequeue(readylist);
	newproc = &proctab[ currpid ];
	newproc->state = PRCURR;	/* mark it currently running	*/
#ifdef  RTCLOCK
	preempt = QUANTUM;          /* reset preemption counter     */
#endif

	ctxsw(&oldproc->stkptr, &newproc->stkptr);

	/* The OLD process returns here when resumed. */
	restore(oldproc->irqstate);
	return OK;
}
