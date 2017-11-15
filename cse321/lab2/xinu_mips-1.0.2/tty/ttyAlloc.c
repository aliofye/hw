/**
 * @file ttyAlloc.c
 * @provides ttyAlloc
 *
 * $Id: ttyAlloc.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>

/**
 * Allocate a tty structure.
 * @return pointer to a TTY control block, NULL if none are free
 */
struct tty *ttyAlloc(void)
{
	irqmask  ps;
	int      i;

	ps = disable();
	for (i = 0; i < NTTY; ++i)
    {
		if (TTY_STATE_FREE == ttytab[i].state) 
		{
			ttytab[i].state = TTY_STATE_ALLOC;
			restore(ps);
			return &ttytab[i];
		}
    }
	restore(ps);
	return NULL;
}
