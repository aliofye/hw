/**
 * @file kill.c
 * Provides: kill
 *
 * $Id: kill.c 240 2007-07-13 21:43:45Z brylow $
 */

/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <queue.h>
#include <semaphore.h>
#include <memory.h>

extern void xdone(void);

/*
 * kill  --  kill a process and remove it from the system
 */
syscall	kill(int pid)
{
	irqmask ps;
	pcb	*ppcb;  /* points to process control block for pid */

	if ( isbadpid(pid) || (0 == pid)
		|| (PRFREE == (ppcb = &proctab[pid])->state) )
	{ return SYSERR; }
	ps = disable();
	if (isbadpid(pid))
	{
		restore(ps);
		return SYSERR;
	}
	ppcb = &proctab[pid];

	--numproc;

	send(ppcb->parent, pid, BLOCK);

	freemem(ppcb->stkbase);

	switch (ppcb->state)
	{
	case PRCURR:
		ppcb->state = PRFREE;	/* suicide */
		resched();

	case PRWAIT:
		semtab[ppcb->sem].count++;

	case PRSLEEP: 
	case PRREADY:
		remove(pid);

	default:
		ppcb->state = PRFREE;
	}

	restore(ps);
	return OK;
}
