/**
 * @file signaln.c
 * @provides signaln
 *
 * $Id: signaln.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <queue.h>
#include <semaphore.h>

/**
 * signaln - signal a semaphore n times, releasing n waiting processes,
 * non-blocking
 * @param sem id of semaphore to signal
 * @param count number of times to signal
 * @return OK on success, SYSERR on failure
 */
syscall signaln(semaphore sem, short count)
{
	irqmask ps;
	register struct sentry *psem;

/* 
 * The implementation of signaln() is essentially like
 * signal(), but with a loop to make ready 'n' processes
 * instead of one.  Signaln() should be non-blocking, that is,
 * it should not call resched() or otherwise yield the processor.
 */

	ps = disable();                      /* disable interrupts            */
	if ( isbadsem(sem) || (count <= 0) ) /* safety check                  */
	{
		restore(ps);
		return SYSERR;
	}
	psem = &semtab[sem];                 /* retrieve semaphore entry      */
	for ( ;  count > 0; count-- )        /* release n processes from wait */
	{
		if ((psem->count++) < 0)
		{ ready(dequeue(psem->queue), RESCHED_NO); }
	}
	restore(ps);                         /* restore interrupts            */
	return OK;
}


