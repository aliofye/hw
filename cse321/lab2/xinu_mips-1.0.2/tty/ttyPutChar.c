/**
 * @file ttyPutChar.c
 * @provides ttyPutChar
 *
 * $Id: ttyPutChar.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>

/**
 * Wwrite a single character to a TTY.
 * @param pdev TTY device table entry
 * @param ch character to output
 * @return 1 if character was written successfully
 */
devcall ttyPutChar(device *pdev, uchar ch)
{
	return ttyWrite(pdev, &ch, 1);
}
