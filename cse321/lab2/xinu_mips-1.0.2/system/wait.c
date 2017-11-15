/**
 * @file wait.c
 * @provides wait
 *
 * $Id: wait.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <queue.h>
#include <semaphore.h>

/**
 * wait - make current process wait on a semaphore
 * @param sem semaphore for which to wait
 * @return OK on success, SYSERR on failure
 */
syscall	wait(semaphore sem)
{
	irqmask ps;    
	struct sentry *psem;
	pcb *ppcb;

	ps = disable();              /* disable interrupts                   */
	if ( isbadsem(sem) )         /* safety check                         */
	{
		restore(ps);
		return SYSERR;
	}
	ppcb = &proctab[currpid];    /* retrieve pcb from process table      */
	psem = &semtab[sem];         /* retrieve semaphore entry             */
	if( --(psem->count) < 0 )    /* if requested resource is unavailable */
	{
		ppcb->state = PRWAIT;    /* set process state to PRWAIT          */
		ppcb->sem = sem;         /* record semaphore id in pcb           */
		enqueue(currpid, psem->queue);
		resched();               /* place in wait queue and reschedule   */
	}
	restore(ps);                 /* restore interrupts                   */
	return OK;
}
