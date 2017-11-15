/**
 * @file insertd.c
 * @provides insertd
 *
 * $Id: insertd.c 240 2007-07-13 21:43:45Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <queue.h>

/**
 * Insert a process in delta queue in ascending order
 * @param pid    process id to insert
 * @param q      queue in which process should be inserted
 * @param key    delta key
 * @return OK
 */
short insertd(short pid, queue q, short key)
{
	short next;         /* runs through list                  */
	short prev;         /* follows next through list          */
	short head, tail;

	if (isbadqueue(q) || isbadpid(pid))
	{ return SYSERR; }

	head = queuehead(q);
	tail = queuetail(q);

	prev = head;
	next = queuetab[head].next;
	while ( (queuetab[next].key <= key) && (next != tail) )
	{
	    key -= queuetab[next].key;
	    prev = next;
	    next = queuetab[next].next;
	}
	queuetab[pid].next  = next;
	queuetab[pid].prev  = prev;
	queuetab[pid].key   = key;
	queuetab[prev].next = pid;
	queuetab[next].prev = pid;
	if (next != tail)
	{ queuetab[next].key -= key; }

	return OK;
}
