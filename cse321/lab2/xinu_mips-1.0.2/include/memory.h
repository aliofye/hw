/**
 * @file memory.h
 * @provides roundew, truncew , roundmb, truncmb
 *
 * $Id: memory.h 235 2007-07-12 22:52:09Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#ifndef _MEMORY_H_
#define _MEMORY_H_

/**
 * roundew - round address to next even word (add 3 to round up)
 * truncew - trunctate address to next even word
 * Binary & with ~0x03 to knock off the last 2 bits
 * @param x address to round/truncate
 */
#define	roundew(x)	(void *)( (3 + (ulong)(x)) & ~0x03 )
#define	truncew(x)	(void *)( ((ulong)(x)) & ~0x03 )

/**
 * roundmb - round address up to size of memblock
 *           (add sizeof(memblock)-1 to round up)
 * truncmb - truncate address up to size of memblock
 * Binary & with ~0x07 to knock off the last 3 bits
 * @param x address to round/truncate
 */
#define	roundmb(x)	(void *)( (7 + (ulong)(x)) & ~0x07 )
#define	truncmb(x)	(void *)( ((ulong)(x)) & ~0x07 )

struct memblock
{
	struct memblock *next;  /**< pointer to next memory block        */
	ulong           length; /**< size of memory block (incl. struct) */
};

extern struct memblock freelist; /**< head of free memory list       */

extern void *minheap;            /**< bottom of heap                    */
extern void *end;                /**< linker provides end of image   */

/* Memory function prototypes */
syscall freemem(void *pmem);
void    *getmem(ulong nbytes);

#endif /* _MEMORY_H_ */
