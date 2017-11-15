/**
 * @file send.c
 * @provides send
 *
 * $Id: send.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>

/**
 * send - pass a message to another process mailbox
 * @param pid process id of recipient
 * @param msg contents of message
 * @param block reschedule if BLOCK, return to call function if NOBLOCK
 * @return OK on success, SYSERR on failure
 */
syscall	send(ushort pid, long msg, bool block)
{
	irqmask ps;    
	pcb *ppcb;

	ppcb = &proctab[pid];                 /* acquire pcb from process table */
	ps = disable();                       /* disable interrupts             */
	if (isbadpid(pid) || (ppcb->state == PRFREE) || ppcb->hasmsg != FALSE) 
	{
		restore(ps);
		return SYSERR;
	}
	ppcb->msg = msg;                      /* deliver message                */
	ppcb->hasmsg = TRUE;                  /* raise mailbox flag             */
	if (ppcb->state == PRRECV) { ready(pid, RESCHED_NO); }
	restore(ps);                          /* restore interrupts             */
	if (BLOCK == block) { resched(); }
	return OK;
}
