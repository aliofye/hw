/**
 * @file ttyControl.c
 * @provides ttyControl
 *
 * $Id: ttyControl.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>

/**
 * Control function for TTY pseudo devices.
 * @param pdev TTY device table entry
 * @param func control function to execute
 * @param arg1 first argument for the control function
 * @param args second argument for the control function
 * @return the result of the control function
 */
devcall ttyControl(device *pdev, uchar func, uchar arg1, uchar arg2)
{
	struct tty *ptty;
	device *phw;
	char old;

	ptty = (struct tty *)pdev->controlblk;
	ASSERT((NULL != ptty) && (TTY_STATE_ALLOC == ptty->state));

	phw = ptty->tty_phw;
	ASSERT(NULL != phw);

	switch (func)
    {
	/* Set input flags: arg1 = flags to set      */
	/* return old value of flags                 */
	case TTY_IOC_SETIFLAG:
		old = ptty->iflags & arg1;
		ptty->iflags |= (arg1);
		return old;
    
	/* Clear input flags: arg1 = flags to clear  */
	/* return old value of flags                 */ 
    case TTY_IOC_CLRIFLAG:
		old = ptty->iflags & arg1;
		ptty->iflags &= ~(arg1);
		return old;
    
	/* Get input flags:                          */
	/* return = current value of flags           */
    case TTY_IOC_GETIFLAG:
		return ptty->iflags;

	/* Set output flags: arg1 = flags to set     */
	/* return old value of flags                 */
    case TTY_IOC_SETOFLAG:
		old = ptty->oflags & arg1;
		ptty->oflags |= (arg1);
		return old;
    
	/* Clear output flags: arg1 = flags to clear */
	/* return old value of flags                 */ 
    case TTY_IOC_CLROFLAG:
		old = ptty->oflags & arg1;
		ptty->oflags &= ~(arg1);
		return old;

	/* Get output flags:                         */
	/* return current value of flags             */
    case TTY_IOC_GETOFLAG:
		return ptty->oflags;

    /* Return true if EOF was seen in input      */
    case TTY_IOC_EOF:
		return (ptty->iflags & TTY_IFLAG_EOF);

    /* Return true if CBREAK was seen in input   */
    case TTY_IOC_CBREAK:
		return (ptty->iflags & TTY_IFLAG_CBREAK);

	/* Peek at next input character              */
	case TTY_IOC_NEXTC:
		if (ptty->icount < 1)
		{
			old = (*phw->getc)(phw);
			ASSERT(old != SYSERR);
		}
		else
		{ 
			old = ptty->inbuf[ptty->istart]; 
		}
		return old;
    }

	return SYSERR;
}
