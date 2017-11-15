/**
 * @file scount.c
 * @provides scount
 *
 * $Id: scount.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <semaphore.h>

/**
 * scount - return a semaphore count
 * @param sem id of semaphore to query
 * @return count from semtab entry on success, SYSERR on failure
 */
syscall scount(semaphore sem)
{
	if ( isbadsem(sem) )
	{ return SYSERR; }
	return (semtab[sem].count);
}
