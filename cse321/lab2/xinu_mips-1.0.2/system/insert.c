/**
 * @file insert.c
 * @provides insert
 *
 * $Id: insert.c 240 2007-07-13 21:43:45Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <queue.h>

/**
 * Insert a process into a queue in descending key order.
 * @param pid    process id to insert
 * @param q      queue in which process should be inserted
 * @param key    sorting key (priority, for example)
 * @return OK
 */
short insert(short pid, queue q, short key)
{
	short next;			/* runs through list		*/
	short prev;
	short head, tail;

	if (isbadqueue(q) || isbadpid(pid))
	{ return SYSERR; }

	head = queuehead(q);
	tail = queuetail(q);

	next = queuetab[head].next;
	while ( (queuetab[next].key >= key) && (next != tail) )
	{ next = queuetab[next].next; }

	queuetab[pid].next = next;
	queuetab[pid].prev = prev = queuetab[next].prev;
	queuetab[pid].key  = key;
	queuetab[prev].next = pid;
	queuetab[next].prev = pid;
	return OK;
}
