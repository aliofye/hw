/**
 * @file newsem.c
 * @provides newsem, allocsem
 *
 * $Id: newsem.c 217 2007-07-11 01:03:18Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <semaphore.h>

static semaphore allocsem(void);

/**
 * newsem - allocate and initialize a new semaphore.
 * @param count - number of resources available without waiting.
 *  example: count = 1 for mutual exclusion lock
 * @return new semaphore id on success, SYSERR on failure
 */
semaphore newsem(short count)
{
	irqmask ps;    
	semaphore sem;

	ps = disable();                     /* disable interrupts    */
	sem = allocsem();                   /* request new semaphore */
	if ( sem != SYSERR && count >= 0 )  /* safety check          */
	{
		semtab[sem].count = count;      /* initialize count      */
		restore(ps);                    /* restore interrupts    */
		return sem;	                    /* return semaphore id   */
	}

	restore(ps);
	return SYSERR;
}

/**
 * allocsem - allocate an unused semaphore and return its index.
 * Scan the global semaphore table for a free entry, mark the entry
 * used, and return the new semaphore
 * @return available semaphore id on success, SYSERR on failure
 */
static semaphore allocsem(void)
{
	int i = 0;
	while(i < NSEM)                     /* loop through semaphore table */
	{                                   /*  to find SFREE semaphore     */
		if( semtab[i].state == SFREE )
		{
			semtab[i].state = SUSED;
			return i;
		}
		i++;
	}
	return SYSERR;
}
