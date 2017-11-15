/**
 * @file semaphore.h
 * @provides isbadsem
 *
 * $Id: semaphore.h 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#ifndef _SEM_H_
#define _SEM_H_

#include <kernel.h>
#include <queue.h>     /**< queue.h must define # of sem queues  */

/* Semaphore state definitions */
#define SFREE 0x01     /**< this semaphore is free               */
#define SUSED 0x02     /**< this semaphore is used               */

/* type definition of "semaphore" */
typedef ulong semaphore;

/* Semaphore table entry */
struct sentry
{
	char  state;       /**< the state SFREE or SUSED             */
	short count;       /**< count for this semaphore             */
	queue queue;       /**< requires q.h.                        */
};

extern struct sentry semtab[];

/**
 * isbadsem - check validity of reqested semaphore id and state
 * @param s id number to test
 */
#define isbadsem(s) (((ushort)(s) >= NSEM) || (SFREE == semtab[s].state))

/* Semaphore function declarations */
syscall   wait(semaphore);
syscall   signal(semaphore);
syscall   signaln(semaphore, short);
semaphore newsem(short);
syscall   freesem(semaphore);
syscall   scount(semaphore);

#endif
