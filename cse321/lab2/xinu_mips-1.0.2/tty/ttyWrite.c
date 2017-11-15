/**
 * @file ttyWrite.c
 * @provides ttyWrite
 *
 * $Id: ttyWrite.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>

/**
 * Write a buffer to a tty
 * @param pdev TTY device table entry
 * @param buf buffer of characters to output
 * @param len size of the buffer
 * @return count of characters output
 */
devcall ttyWrite(device *pdev, uchar *buf, ushort len)
{
	struct tty *ptty;
	device     *phw = NULL;
	ushort     i    = 0;
	uchar      last = 0;

	/* Setup and error check pointers to structures */
	ptty = (struct tty *)pdev->controlblk;
	ASSERT((NULL != ptty) && (TTY_STATE_ALLOC == ptty->state));
	
	phw = ptty->tty_phw;
	ASSERT(NULL != phw);

	for (i = 0; i < len; i++)
    {
		/* If not in RAW mode, then 'cook' special characters    */
		if (!(ptty->oflags & TTY_OFLAG_RAW))
			{
				/* Cook Line Feed and/or Carriage Return         */
				if ( ('\r' == buf[i]) 
					 || (('\n' == buf[i]) 
						 && ('\r' != last) ))
				{
					/* LF's are converted to CRLF's,        */
					/* CR's are converted to CRLF's,        */
					/* CRLF's have the CR expanded to CRLF, */
					/* and the LF dropped below.            */
					/* Thus, only CRLF's are output.        */
					if (SYSERR == (*phw->putc)(phw, '\r')) break;
					if (SYSERR == (*phw->putc)(phw, '\n')) break;
					last = buf[i];
					continue;
				}

				/* Drop null characters or LF */
				if (('\0' == buf[i]) || ('\n' == buf[i]))
				{
					last = buf[i];
					continue;
				}

				/* Cook Backspace and Delete */
				if (('\b' == buf[i]) || (0x7F == buf[i]))
				{
					/* BS or DEL becomes 'BS, SP, BS' */
					if (SYSERR == (*phw->putc)(phw, '\b')) break;
					if (SYSERR == (*phw->putc)(phw, ' '))  break;
					if (SYSERR == (*phw->putc)(phw, '\b')) break;
					last = buf[i];
					continue;
				}
			}

		/* Write character to underlying device */
		if (SYSERR == (*phw->putc)(phw, buf[i])) break;
		
		/* Remember last character for cooking checks */
		last = buf[i];
    }

	return i;
}
