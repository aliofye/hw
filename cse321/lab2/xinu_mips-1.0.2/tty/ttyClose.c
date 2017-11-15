/**
 * @file ttyClose.c
 * @provides ttyClose
 *
 * $Id: ttyClose.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>
#include <stdlib.h>

/**
 * Close a TTY device.
 * @param pdev TTY device table entry
 * @return OK if TTY is closed properly, otherwise SYSERR
 */
devcall ttyClose(device *pdev)
{
	struct tty *ptty;
    
	ptty = (struct tty *)pdev->controlblk;

	ASSERT(NULL != ptty);

	bzero(ptty, sizeof(struct tty));   /* Clear TTY structure.         */

	pdev->controlblk = (char *)NULL;   /* Clear device IO block.       */
	ptty->state      = TTY_STATE_FREE;
	return OK;
}
