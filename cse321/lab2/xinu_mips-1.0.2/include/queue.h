/**
 * @file queue.h 
 * @provides firstid, firstkey, isempty, lastkey, nonempty
 * 
 * The process queue system allows a statically-allocated array to
 * model sorted process queueing before more complex operating system
 * services, like dynamic memory allocation, are up and running.
 *
 * These process queues assume several important invariants:
 *  1) A fixed number of process queues in the system, known
 *     at compile time,
 *  2) A process queue can contain only processes and their
 *     associated key values, and thus queue length is at
 *     most NPROC, the total number of processes, and
 *  3) A process can be in at most one queue at a time.
 *
 * Ordering of processes within a given queue depends upon the sorting
 * functions called when maintaining that particular system queue.
 *
 * $Id: queue.h 240 2007-07-13 21:43:45Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

/* queue structure declarations, constants, and inline procedures       */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#ifndef NSEM
#define NSEM    100     /**< number of semaphores, if not defined        */
#endif

#ifndef NQENT
#define NQENT   NPROC   /**< one for each process                        */ \
          + 2           /**< plus two for each list (ready list)         */ \
          + 2           /**< plus two for each list (sleep list)         */ \
          + NSEM + NSEM /**< plus two for each semaphore                 */
#endif

typedef unsigned long queue;

struct qentry
{                       /**< one for each process plus two for each list */
	short key;          /**< key on which the queue is ordered           */
	short next;         /**< index of next process or tail               */
	short prev;         /**< index of previous process or head           */
};

extern struct qentry queuetab[];
extern queue         readylist;

/* inline list manipulation procedures                                   */

#define queuehead(q) (((q) >> 16) & 0xFFFF)
#define queuetail(q) ((q) & 0xFFFF)

/** 
 * Check for invalid process ids.  Note that interrupts must be disabled
 * for the condition to hold true between statements.
 */
#define isbadqueue(x) (queuehead(x)<0 || (queuehead(x) != (queuetail(x) - 1)) || queuetail(x)>=NQENT)

#define isempty(q)   (queuetab[queuehead(q)].next >= NPROC)
#define nonempty(q)  (queuetab[queuehead(q)].next < NPROC)
#define firstkey(q)  (queuetab[queuetab[queuehead(q)].next].key)
#define lastkey(q)   (queuetab[queuetab[queuetail(q)].prev].key)
#define firstid(q)   (queuetab[queuehead(q)].next)

short enqueue(short, queue);
short insert(short, queue, short);
short insertd(short, queue, short);
short remove(short);
short dequeue(queue);
queue newqueue(void);

#endif /* _QUEUE_H_ */
