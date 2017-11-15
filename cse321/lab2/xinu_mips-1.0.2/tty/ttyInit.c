/**
 * @file ttyInit.c
 * @provides ttyInit
 *
 * $Id: ttyInit.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>
#include <stdlib.h>

struct tty	ttytab[NTTY];

/**
 * Initialize TTY structures.
 * @param pdev TTY device table entry
 * @return OK if device is intialized successfully
 */
devcall ttyInit(device *pdev)
{
	struct tty *ptty;

	pdev->controlblk = NULL;
	ptty = &ttytab[pdev->minor];
	bzero((void *)ptty, sizeof(struct tty));
	ptty->state = TTY_STATE_FREE;

	return OK;
}
