/**
 * @file create.c
 * @provides create, newpid, userret
 *
 * $Id: create.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */
  
#include <kernel.h>
#include <proc.h>
#include <vararg.h>
#include <mips.h>
#include <memory.h>
#include <string.h>

local newpid(void);
void userret(void);

/**
 * Create a process to start running a procedure.
 * @param procaddr procedure address
 * @param ssize stack stack size in words
 * @param priority process priority, must be > 0
 * @param name name of the process, used for debugging
 * @param nargs, number of arguments that follow
 * @return the new process' process id
 */
syscall	create(void *procaddr, ulong ssize, ushort priority,
	       char *name, ulong nargs, ...)
{
	ulong   *saddr;     /* stack address                */
	ulong   *savargs;   /* pointer to arg saving region */
	ulong   pid;        /* stores new process id        */
	pcb     *ppcb;      /* pointer to proc control blk  */
	ulong   i;
	va_list	ap;         /* points to list of var args   */
	ulong   pads;       /* padding entries in record.   */
	void	INITRET(void);

	if (ssize < MINSTK) ssize = MINSTK;
	ssize = (ulong)roundew(ssize);  /* round up to even boundary    */
	saddr = (ulong *)getmem(ssize); /* allocate new stack and pid   */
	pid   = newpid();
	                                /* a little error checking      */ 
	if ( (((ulong *)SYSERR) == saddr) || (SYSERR == pid) )
	{ return SYSERR; }

	numproc++;
	ppcb = &proctab[ pid ];
                                    /* setup PCB entry for new proc */
	ppcb->state   = PRSUSP;
	ppcb->prio    = priority;
	ppcb->stkbase = saddr;
	saddr = (ulong *)(((ulong)saddr) + ssize - sizeof(ulong));
	ppcb->stklen  = ((ulong)saddr) - (ulong)ppcb->stkbase;
	ppcb->stkptr  = saddr;
	strncpy(ppcb->name, name, PNMLEN);
	ppcb->parent  = (ushort)getpid();

	/* Initialize stack with accounting block. */
	*saddr   = STACKMAGIC;
	*--saddr = pid;
	*--saddr = ppcb->stklen;
	*--saddr = (ulong)ppcb->stkbase;
	
	if (0 == nargs)
	{ pads = 4; } 
	else if (0 == (nargs % 4))           /* Must pad record size to      */
	{ pads = 0; }                        /*  multiple of native memory   */
	else                                 /*  transfer size.              */
	{ pads = 4 - (nargs % 4); }

	for (i = 0; i < pads; i++) { *--saddr = 0; }
                                    /* Reserve space for all args.  */
	for (i = nargs ; i > 0 ; i--) { *--saddr = 0; }
	savargs = saddr;          

	/* Build the context record as expected by ctxsw.               */
                                    /* Clear room for saved state.  */
	for (i = (CONTEXT_WORDS); i > 0; i--) { *--saddr = 0; }
	ppcb->stkptr = saddr;
	                                /* Address of proc entry point  */
	saddr[(CONTEXT_WORDS) - 1] = (ulong)procaddr;      
	                              	/* Return Address value         */
	saddr[(CONTEXT_WORDS) - 2] = (ulong)INITRET;      

	/* Place arguments into activation records. */
	va_start(ap, nargs);
	for (i = 0; i < nargs; i++)
	{ savargs[i] = va_arg(ap, ulong); }
	va_end(ap);

	return pid;
}

/**
 * Obtain a new (free) process id.
 * @return a free process id, SYSERR if all ids are used
 */
local newpid(void)
{
	int	pid;			/* process id to return     */
	static int nextpid = 0;

	for (pid = 0 ; pid < NPROC ; pid++) 
	{	                /* check all NPROC slots    */
		nextpid = (nextpid + 1) % NPROC;
	    if (PRFREE == proctab[nextpid].state)
		{ return nextpid; }
	}
	return SYSERR;
}

/**
 * Entered when a process exits by return.
 */
void userret(void)
{
	kill( getpid() );
}
