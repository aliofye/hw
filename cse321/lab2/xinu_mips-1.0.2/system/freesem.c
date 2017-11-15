/**
 * @file freesem.c
 * @provides freesem
 *
 * $Id: freesem.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <semaphore.h>
#include <queue.h>

/**
 * freesem - deallocate a semaphore.
 * Reset the semaphore count, releasing any processes
 * in the waiting queue.  Deallocate entry in global
 * semaphore table.
 * @param sem id of semaphore to be released
 * @return OK on success, SYSERR on failure
 */
syscall freesem(semaphore sem)
{
	irqmask ps;    
	struct sentry *sptr;
	int	pid;

	ps = disable();                 /* disable interrupts              */
	if ( isbadsem(sem) )            /* check sem validity              */
	{
		restore(ps);
		return SYSERR;
	}
	sptr = &semtab[sem];
	while ( nonempty(sptr->queue) ) /* release processes in wait queue */
	{
		pid = dequeue(sptr->queue);
		ready(pid, RESCHED_NO);
	}
	sptr->count = 0;                /* reset the semaphore count       */
	sptr->state = SFREE;            /* deallocate in semaphore table   */
	restore(ps);                    /* restore interrupts              */
	return OK;
}
