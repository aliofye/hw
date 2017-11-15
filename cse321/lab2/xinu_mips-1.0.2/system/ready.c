/**
 * @file ready.c
 * @provides ready
 *
 * $Id: ready.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <queue.h>

/**
 * Make a process eligible for CPU service.
 * @param pid process id of the process to move to the ready state
 * @param resch if TRUE, reschedule will be called
 * @return OK if the process has been added to the ready list, else SYSERR
 */
syscall ready(long pid, bool resch)
{
	register pcb *ppcb;

	ASSERT(!isbadpid(pid));

	ppcb = &proctab[pid];
	ppcb->state = PRREADY;

	insert(pid, readylist, ppcb->prio);

	if (resch) { resched(); }
	return OK;
}
