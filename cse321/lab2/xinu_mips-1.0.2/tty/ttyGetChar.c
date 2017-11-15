/**
 * @file ttyGetChar.c
 * @provides ttyGetChar
 *
 * $Id: ttyGetChar.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>

/**
 * Read a single character from a TTY.
 * @param pdev TTY device table entry
 * @return character read from TTY
 */
devcall ttyGetChar(device *pdev)
{
	uchar ch;
	long  len;

	len = ttyRead(pdev, (char *)&ch, 1);
	/* Check for EOF or SYSERR */
	if (len < 0)
    { return len; }
	return ch;
}
