/**
 * @file ttyRead.c
 * @provides ttyRead
 *
 * $Id: ttyRead.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>
#include <tty.h>

/**
 * Read characters from a tty.
 *
 * Characters are read from an underlying device, normally a UART.  Input
 * is read from the underlying device in lines.  Lines may be terminated with
 * the line feed or carriage return characters.  Read requests are not
 * satsified until a full line has been read, or the tty's buffer is full. 
 * When the tty is not in raw mode, backspaces are cooked and escape 
 * sequences and the null character is ignored. 
 * When the end of file (Control+D)  character is read, the tty stops reading 
 * from the underlying device.  Subsquent calls to ttyRead will attempt to 
 * staisfy the request from the tty's buffer, otherwise EOF will be returned.
 *
 * @param pdev pointer to tty device
 * @param buf buffer for read characters
 * @param len size of the buffer
 * @return number of characters read, EOF if end of file was reached
 */
devcall ttyRead(device *pdev, char *buf, ushort len)
{
	struct tty *ptty;
	device     *phw;
	long       c = 0;
	ushort     count = 0;

	/* Setup and error check pointers to structures */
	ptty = (struct tty *)pdev->controlblk;
	ASSERT((NULL != ptty) && (TTY_STATE_ALLOC == ptty->state));

	phw = ptty->tty_phw;
	ASSERT(NULL != phw);

	/* Check for EOF */
	if (ptty->iflags & TTY_IFLAG_EOF)
	{
		return EOF;
	}

	/* If the tty's input buffer is empty, read the next line   */ 
    /*   from the underlying device into the tty's input buffer */
	if (ptty->icount == 0)
    {
		/* Read characters from the underlying device while there */
		/*   is space in the tty's input buffer and a CR, LF, or  */
        /*   EOT (Ctrl+D) character  has not been encountered     */
		while (ptty->icount < TTY_IBLEN)
		{
			/* Read character from underlying device */
			if (SYSERR == (c = (*phw->getc)(phw))) { break; }

			/* If not in RAW mode, then 'cook' special characters */
			if (!(ptty->iflags & TTY_IFLAG_RAW))
			{
				/* Cook backspace and delete */
				if (('\b' == c)
					|| (0x7F == c))
				{
					if (ptty->icount > 0)
					{ 
						ptty->icount--;
						if (ptty->iflags & TTY_IFLAG_ECHO)
						{ ttyPutChar(ptty->tty_dev, c); }
					}
					continue;
				}

				/* Drop escape sequences */
				if (0x1B == c)
				{
					if (SYSERR == (c = (*phw->getc)(phw))) { break; }
					if (SYSERR == (c = (*phw->getc)(phw))) { break; }
					continue;
				}

				/* Drop null characters */
				if ('\0' == c)
				{ continue; }
			}

			/* Add character to input buffer */
			ptty->inbuf[(ptty->istart + ptty->icount) % TTY_IBLEN] = c;
			ptty->icount++;

			/* If echo is enabled, echo the character */
			if (ptty->iflags & TTY_IFLAG_ECHO)
			{ ttyPutChar(ptty->tty_dev, c); }

			/* Stop reading into input buffer if CR, LF, or end of file */
			if (('\r' == c)	
				|| ('\n' == c)
				|| (0x04 == c))
		    { break; }
		}
	}

	ptty->iflags &= ~TTY_IFLAG_CBREAK; /* Clear break (Control-C) flag */
	ptty->iflags &= ~TTY_IFLAG_EOF;	   /* Clear EOF  (Control-D) flag  */

  /* Satisfy read request from input buffer */
  while ((count < len)  && (ptty->icount > 0))
  {
      /* Check for Break character (Control-C) and set flag */
      if (0x03 == c)
	  { ptty->iflags |= TTY_IFLAG_CBREAK; }

      /* Check for EOF character (Control-D) and set flag */
      if (0x04 == c)
	  {
		  ptty->iflags |= TTY_IFLAG_EOF;
		  len = count;
	  }
      
      /* Read from input buffer into user buffer; Preserve circular buffer */
      *buf++ = ptty->inbuf[ptty->istart];
      ptty->icount--;
      ptty->istart = (ptty->istart + 1) % TTY_IBLEN;
      count++;
  }

  return count;
}
