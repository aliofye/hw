/**
 * @file getmem.c
 * @provides getmem                                                       
 *
 * $Id: getmem.c 217 2007-07-11 01:03:18Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <memory.h>

/**
 * Allocate heap storage, returning pointer to assigned memory region.
 * @param nbytes number of bytes requested
 * @return pointer to region on success, SYSERR on failure
 */
void *getmem(ulong nbytes)
{
	irqmask ps;    
	struct memblock *prev, *next, *leftover;

	if ( (0 == nbytes) || (NULL == freelist.next) )
	{
		return (void *)SYSERR;
	}

	/* pad nbytes with room for accounting information and */
	/* round to the nearest bytes                          */
	nbytes = (ulong)roundmb(nbytes + sizeof(struct memblock));

	/* modifying memory layout, do not interrupt */
	ps = disable();

	prev = &freelist;
	next = freelist.next;
	while ( NULL != next )
	{
		/* if the current node has enough room, we'll allocate */
		if (next->length >= nbytes)
		{
			/* this block is big enough, check if it can hold nbytes   */
			/* and still have room for the leftover block's acct. info */
			if ( next->length < (nbytes + sizeof(struct memblock)) ) 
			{
				/* there was not enough room for nbytes and the new    */
				/* block's accounting information, so allocate block   */
				prev->next = next->next;
				next->next = next;

				/* maintain freelist length */
				freelist.length -= next->length;

				restore(ps);
				return (void *)(next + 1); /* + 1 to skip acct. data   */
			} 
			else 
			{
				/* block is big enough to split in two relevant blocks */
				leftover   = (struct memblock *)((ulong)next + nbytes);
				prev->next = leftover;

				/* set up data for the new (smaller) node */
				leftover->next   = next->next;
				leftover->length = next->length - nbytes;
				
				/* prepare block for checks in freemem                */
				/* a memory location pointing to itself is unlikely   */
				next->next   = next;
				next->length = nbytes;

				/* maintain freelist length */
				freelist.length -= next->length;

				restore(ps);
				return (void *)(next + 1); /* + 1 to skip acct. data  */
			}
		}

		/* iterate to next pointer, this node was too small */
		prev = next;
		next = next->next;
	}

	restore(ps);
	return (void *)SYSERR;
}
