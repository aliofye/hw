/**
 * @file signal.c
 * @provides signal
 *
 * $Id: signal.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <queue.h>
#include <semaphore.h>

/**
 * signal - signal a semaphore, releasing one waiting process, and block
 * @param sem id of semaphore to signal
 * @return OK on success, SYSERR on failure
 */
syscall signal(semaphore sem)
{
	irqmask ps;
	register struct sentry *psem;

	ps = disable();                /* disable interrupts                  */
	if ( isbadsem(sem) )           /* safety check                        */
	{
		restore(ps);
		return SYSERR;
	}
	psem = &semtab[sem];           /* retrieve semaphore entry            */
	if ( (psem->count++) < 0 )     /* release one process from wait queue */
	{ ready(dequeue(psem->queue), RESCHED_YES); }
	restore(ps);                   /* restore interrupts                  */
	return OK;
}


