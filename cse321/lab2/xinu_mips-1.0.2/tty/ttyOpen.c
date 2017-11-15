/**
 * @file ttyOpen.c
 * @provides ttyOpen
 *
 * $Id: ttyOpen.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>
#include <vararg.h>

/**
 * Associate a TTY with a hardware device.
 * @param pdev TTY device table entry
 * @param ap 2nd argument is the device number for the hardware device
 * @return OK if TTY is opened properly, otherwise SYSERR
 */
devcall ttyOpen(device *pdev, va_list ap)
{
	struct tty *ptty = NULL;
	int dvnum = 0;

	/* Check if TTY is already open */
	if (pdev->controlblk)
    {   return OK;   }

	/* Allocate a tty */
	ptty = (struct tty *)ttyAlloc();

	ASSERT(NULL != ptty);

	/* Mutually link tty record with device table entry */
	pdev->controlblk = (char *)ptty;
	ptty->tty_dev = pdev;

	/* Initialize input buffer */
	ptty->iflags = 0;
	ptty->istart = 0;
	ptty->icount = 0;

	/* Initialize output flags */
	ptty->oflags = 0;

	/* Second arg should be device index for physical hardware */
	dvnum = va_arg(ap, int); 
	ASSERT(!isbaddev(dvnum));

	ptty->tty_phw  = &devtab[dvnum];

	return OK;
}
