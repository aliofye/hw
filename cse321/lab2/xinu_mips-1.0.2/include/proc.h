/**
 * @file proc.h
 * @provides isbadpid
 *
 * $Id: proc.h 446 2008-04-30 18:49:43Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#ifndef _PROC_H_
#define _PROC_H_

#include <kernel.h>
#include <semaphore.h>

/* process table declarations and defined constants                      */

#ifndef NPROC                 /*   if number of processes is not set,    */
#define NPROC       50        /**< set the number of processes           */
#endif

/* unusual value marks the top of the process stack                      */
#define STACKMAGIC 0x0A0AAAA9

/* process state constants                                               */

#define PRCURR      1       /**< process is currently running            */
#define PRFREE      2       /**< process slot is free                    */
#define PRREADY     3       /**< process is on ready queue               */
#define PRRECV      4       /**< process waiting for message             */
#define PRSLEEP     5       /**< process is sleeping                     */
#define PRSUSP      6       /**< process is suspended                    */
#define PRWAIT      7       /**< process is on semaphore queue           */

/* miscellaneous process definitions                                     */

#define PNMLEN      16      /**< length of process "name"                */
/* the null process is always eligible to run                            */
#define NULLPROC    0       /**< id of the null process                  */
#define BADPID     (-1)     /**< used when invalid pid needed            */

/** 
 * Check for invalid process ids.  Note that interrupts must be disabled
 * for the condition to hold true between statements.
 */
#define isbadpid(x) ((x)>=NPROC || PRFREE == proctab[(x)].state)

/* process table entry */

typedef struct pentry
{
	uchar   state;          /**< process state: PRCURR, etc.             */
	ushort  prio;           /**< process priority                        */
	void    *stkptr;        /**< saved stack pointer                     */
	void    *stkbase;       /**< base of run time stack                  */
	ulong   stklen;         /**< stack length                            */
	char    name[PNMLEN];   /**< process name                            */
	irqmask irqstate;       /**< saved interrupt mask                    */
	semaphore sem;          /**< semaphore waiting for                   */
	ushort  parent;         /**< pid for the parent process              */
	long    msg;            /**< message sent to this process            */
	bool    hasmsg;         /**< nonzero iff msg is valid                */
} pcb;

/* process initialization constants */
#define INITSTK  65536      /**< initial process stack size              */
#define INITPRIO 20         /**< initial process priority                */
#define INITRET  userret    /**< processes return address                */
#define MINSTK   4096       /**< minimum process stack size              */
#define NULLSTK  MINSTK     /**< null process stack size                 */

/* reschedule constants for send and receive */
#define BLOCK       1
#define NOBLOCK     0


extern struct pentry proctab[];
extern ushort numproc;      /**< currently active processes              */
extern ushort currpid;      /**< currently executing process             */

/* IPC prototypes */
syscall send(ushort pid, long msg, bool block);
syscall receive(bool block);

#endif /* _PROC_H_ */
