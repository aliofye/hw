/**
 * @file freemem.c
 * @provides freemem                                                     
 *
 * $Id: freemem.c 235 2007-07-12 22:52:09Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <platform.h>
#include <memory.h>

extern void *end;

/**
 * Free a memory block, returning it to free list.
 * @param *pmem pointer to memory block
 * @return OK on success, SYSERR on failure
 */
syscall	freemem(void *pmem)
{
	struct memblock *block, *next, *prev;
	irqmask ps;
	ulong top, size;

	/* block points at the memblock we want to free */ 
	block = (struct memblock *)pmem;
	/* back up to accounting information */
	block--;

	/* Simple check to make sure block is in heap */
	ASSERT( (ulong)block >= (ulong)minheap );
	ASSERT( (ulong)block < (ulong)platform.maxaddr );

	ps = disable();

    /* consistency checks for block, set up in getmem */
	if ( (block->next != block) || (block->length == 0) )
	{
		restore(ps);
		return SYSERR;
	}

	size = block->length;

	/* In order to keep the freelist well-ordered */
	/* position prev < block && block < next      */
	prev = &freelist;
	next = freelist.next;
	while ( (next != NULL) && (next < block) )
	{
		prev = next;
		next = next->next;
	}

	/* find top of previous memblock */
	/* top is meaningless if prev is the freelist, so set  */
	/* top to a meaningless value (which will fail all tests)    */
	/* otherwise, top is the previous pointer + length of ptr    */
	if (prev == &freelist) { top = NULL; }
	else { top = (ulong)prev + prev->length; }

	/* make sure block is not overlapping on prev or next blocks */
	/* next == NULL is a special case (end of the freelist)      */
	if ( ( top > (ulong)block )
	  || ( (next != NULL) && ((ulong)block + size) > (ulong)next ) )
	{
		restore(ps);
		return SYSERR;
	}

	/* maintain freelist length */
	freelist.length += block->length;

	/* Now for some simple memblock coalescing */
	/* are prev and block contiguous? */
	if ( top == (ulong)block )
	{
		/* yes, then coalesce prev & block */
		prev->length += size;

		/* sanitize the coalesced block */
		block->next   = NULL;
		block->length = 0;

		/* set block to prev for block&next coalesce check */
		block = prev;
	}
	else 
	{
		/* no, return block to free list */
		block->next = next;
		prev->next = block;
	}

	/* are block and next contiguous? */
	if ( (ulong)((ulong)block + block->length) == (ulong)next ) 
	{
		/* yes, coalesce block & next */
		block->length += next->length;
		block->next    = next->next;

		/* sanitize next */
		next->next   = NULL;
		next->length = 0;
	}

	restore(ps);
	return OK;
}
