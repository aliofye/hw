/**
 * @file receive.c
 * @provides receive
 *
 * $Id: receive.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <proc.h>

/**
 * receive - request a message from mailbox
 * @param block wait for message if BLOCK, return NULL if
 *  NOBLOCK and no message available
 * @return message if available, NULL if no message in mailbox
 */
syscall	receive(bool block)
{
	irqmask ps;    
	pcb   *ppcb;
	ulong msg;

	ps = disable();
	ppcb = &proctab[currpid];
	if ( !ppcb->hasmsg ) 
	{
		if ( BLOCK == block )      /* if no message, block               */
		{
			ppcb->state = PRRECV;  /* change state from PRCURR to PRRECV */
			resched();             /* reschedule                         */
		}
		else                       /* if no message, return NULL         */
		{
			restore(ps);
			return NULL;
		}
	}
	msg = ppcb->msg;		       /* retrieve message                   */
	ppcb->hasmsg = FALSE;          /* reset mailbox                      */
	restore(ps);
	return msg;
}
