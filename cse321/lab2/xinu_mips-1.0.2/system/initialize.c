/**
 * @file initialize.c
 * @provides nulluser, sysinit
 *
 * $Id: initialize.c 242 2007-07-13 22:28:23Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

/** 
 * The system begins intializing after the C environment has been
 * established.  After intialization, the null process remains always in
 * a ready (PRREADY) or running (PRCURR) state.
 */

#include <kernel.h>
#include <platform.h>
#include <proc.h>
#include <queue.h>
#include <semaphore.h>
#include <memory.h>
#include <clock.h>
#include <device.h>
#include <stdio.h>
#include <string.h>
#include <mips.h>
#include <gpio.h>

/* Linker provides start and end of image */
extern   void   _start(void);   /* start of XINU code                    */    
extern   void   *end;           /* end of XINU code                      */

/* Function prototypes */
extern void main(void);         /* main is the first process created     */
extern void xdone(void);        /* system "shutdown" procedure           */
local       platforminit(void); /* determines platform-dependent settings*/
local       sysinit(void);      /* intializes system structures          */

/* Declarations of major kernel variables */
struct pentry   proctab[NPROC]; /* Process table                         */
struct sentry   semtab[NSEM];   /* Semaphore table                       */
queue           readylist;      /* List of READY processes               */
struct memblock freelist;       /* List of free memory blocks            */

/* Active system status */
ushort  numproc;                /* Number of live user processes         */
ushort  currpid;                /* Id of currently running process       */

/* Params set by startup.S */
void            *minheap;       /* Bottom of heap (top of O/S stack)     */
ulong           cpuid;          /* Processor id                          */

struct platform platform;       /* Platform specific configuration       */

/**
 * Intializes the system and becomes the null process.
 * This is where the system begins after the C environment has been 
 * established.  Interrupts are initially DISABLED, and must eventually 
 * be enabled explicitly.  This routine turns itself into the null process 
 * after initialization.  Because the null process must always remain ready 
 * to run, it cannot execute code that might cause it to be suspended, wait 
 * for a semaphore, or put to sleep, or exit.  In particular, it must not 
 * do I/O unless it uses kprintf for synchronous output.
 */
int nulluser()
{
	kprintf(VERSION);  kprintf("\r\n\r\n");
	
	platforminit();

#ifdef DETAIL
	/* Output detected platform. */
	kprintf("Processor identification: 0x%08X\r\n", cpuid);
	kprintf("Detected platform as: %s\r\n\r\n",platform.name);
#endif

	sysinit();

	/* Output XINU memory layout */
	kprintf("%10d bytes physical memory.\r\n", 
		(ulong) platform.maxaddr & 0x7FFFFFFF );
#ifdef DETAIL
	kprintf("           [0x%08X to 0x%08X]\r\n",
		(ulong) KSEG0_BASE, (ulong) (platform.maxaddr - 1));
#endif 
	kprintf("%10d bytes reserved system area.\r\n",
		(ulong) _start - KSEG0_BASE);
#ifdef DETAIL
	kprintf("           [0x%08X to 0x%08X]\r\n",
		(ulong) KSEG0_BASE, (ulong) _start - 1);
#endif 

	kprintf("%10d bytes XINU code.\r\n",
		(ulong) &end - (ulong) _start);
#ifdef DETAIL
	kprintf("           [0x%08X to 0x%08X]\r\n",
		(ulong) _start, (ulong) &end - 1);
#endif 

	kprintf("%10d bytes stack space.\r\n",
		(ulong) minheap - (ulong) &end);
#ifdef DETAIL
	kprintf("           [0x%08X to 0x%08X]\r\n",
		(ulong) &end, (ulong) minheap - 1);
#endif 

	kprintf("%10d bytes heap space.\r\n",
		(ulong) platform.maxaddr - (ulong) minheap);
#ifdef DETAIL
	kprintf("           [0x%08X to 0x%08X]\r\n\r\n",
		(ulong) minheap, (ulong) platform.maxaddr - 1);
#endif 

	/* enable interrupts here */
	enable();

	open(CONSOLE, SERIAL0);

	ready(create((void *)main, INITSTK, INITPRIO, "MAIN", 2, 0, NULL),
	      RESCHED_NO);

	while(1) 
	{
		/* If there is any process ready to run, yield to it.  */
		if (nonempty(readylist)) { resched(); }
		/* If there are no processes left in the system, exit. */
		if (numproc <= 1)       { xdone(); }
	}
}

/**
 * Intializes all XINU data structures and devices.
 * @return OK if everything is initialized successfully
 */
local sysinit(void)
{
	int     i;
	pcb     *ppcb;                      /* process control block pointer */
	device  *pdev;                      /* device entry pointer          */
	struct  sentry  *psem;              /* semaphore entry pointer       */
	struct  memblock  *pmblock;         /* memory block pointer          */

	/* Initialize system variables */
	/* Count this NULLPROC as the first process in the system. */
	numproc   = 1;
	/* Initialize free memory list */
	freelist.next   = pmblock = (struct memblock *) roundmb(minheap);
	freelist.length = (ulong)truncew((ulong)platform.maxaddr - (ulong)minheap);
	pmblock->next = NULL;
	pmblock->length = (ulong)truncew((ulong)platform.maxaddr - (ulong)minheap);

	/* Initialize process table */
	for (i = 0; i < NPROC; i++) 
	{ proctab[i].state = PRFREE; }

	/* initialize null process entry */
	ppcb = &proctab[NULLPROC];
	ppcb->state        = PRCURR;
	ppcb->prio         = 0;
	strncpy(ppcb->name, "prnull", 7);
	ppcb->stkbase      = (void *)&end;
	ppcb->stklen       = (ulong)minheap - (ulong)&end;
	ppcb->stkptr       = 0;
	currpid            = NULLPROC;

	/* Initialize semaphores */
	for (i = 0; i < NSEM; i++)
	{
		psem = &semtab[i];
		psem->state = SFREE;
		psem->count = 0;
		psem->queue = newqueue();
	}
  
	/* initialize process ready list */   
	readylist = newqueue();   

#ifdef RTCLOCK
	/* initialize real time clock */
	clockinit();
#endif

#ifdef NDEVS
	for (i = 0; i < NDEVS; i++)
	{
		if (!isbaddev(i))
		{
			pdev = &devtab[i];
			(pdev->init)(pdev);
		}
	}
#endif

	GPIO_CTRL_LED_ON(GPIO_LED_CISCOWHT);

	return OK;
}

/**
 * Determines and stores all platform specific information.
 * @return OK if everything is determined successfully
 */
local platforminit(void)
{
	switch (cpuid & PRID_REV)
	{
		case PRID_REV_WRT54G:
			strncpy(platform.name, "Linksys WRT54G", 16);
			platform.maxaddr = (void *) (KSEG0_BASE | MAXADDR_WRT54G);
			platform.time_base_freq = TIME_BASE_FREQ_WRT54G;
			platform.uart_dll = UART_DLL_WRT54G;
			break;
		case PRID_REV_WRT54GL:
			strncpy(platform.name, "Linksys WRT54GL", 16);
			platform.maxaddr = (void *) (KSEG0_BASE | MAXADDR_WRT54GL);
			platform.time_base_freq = TIME_BASE_FREQ_WRT54GL;
			platform.uart_dll = UART_DLL_WRT54GL;
			break;
		case PRID_REV_WRT350N:
			strncpy(platform.name, "Linksys WRT350N", 16);
			platform.maxaddr = (void *) (KSEG0_BASE | MAXADDR_WRT350N);
			platform.time_base_freq = TIME_BASE_FREQ_WRT350N;
			platform.uart_dll = UART_DLL_WRT350N;
			break;
		default:
			strncpy(platform.name, "Unknown Platform", 16);
			platform.maxaddr = (void *) (KSEG0_BASE | MAXADDR_DEFAULT);
			platform.time_base_freq = TIME_BASE_FREQ_DEFAULT;
			return SYSERR;
	}
	
	return OK;
}

