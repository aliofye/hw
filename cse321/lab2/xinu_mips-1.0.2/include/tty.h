/*
 * @file tty.h
 *
 * $Id: tty.h 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#ifndef __TTY_H__
#define __TTY_H__

#include <vararg.h>

/* TTY Buffer lengths */
#define TTY_IBLEN 1024              /**< input buffer size               */

struct tty 
{
	uchar         state;            /**< TTY_STATE_* below               */

	/* Pointers to associated structures */
	device        *tty_dev;         /**< tty device structure            */
	device        *tty_phw;         /**< hardware device structure       */

	/* TTY input fields */
	uchar         iflags;           /**< Input flags                     */
	ushort        istart;           /**< Index of first character        */
	ushort        icount;           /**< Characters in input buffer      */
	uchar         inbuf[TTY_IBLEN]; /**< Input buffer                    */

	/* TTY output fields */
	uchar         oflags;           /**< Output flags                    */
};

extern struct tty ttytab[];

/* TTY states */
#define TTY_STATE_FREE  0
#define TTY_STATE_ALLOC 1

/* TTY input flags */
#define TTY_IFLAG_RAW       0x0001  /**< do raw input                    */
#define TTY_IFLAG_ECHO      0x0002  /**< echo input                      */
#define TTY_IFLAG_CBREAK    0x0004  /**< have seen Break (Control-C)     */
#define TTY_IFLAG_EOF       0x0008  /**< have seen EOF (Control-D)       */

/* TTY output flags */
#define TTY_OFLAG_RAW       0x0001  /**< do raw output                   */

/* ttyControl() functions  */
#define TTY_IOC_SETIFLAG    0x0020  /**< set input flags                 */
#define TTY_IOC_CLRIFLAG    0x0021  /**< clear input flags               */
#define TTY_IOC_GETIFLAG    0x0022  /**< get input flags                 */
#define TTY_IOC_SETOFLAG    0x0023  /**< set output flags                */
#define TTY_IOC_CLROFLAG    0x0024  /**< clear output flags              */
#define TTY_IOC_GETOFLAG    0x0025  /**< get output flags                */
#define TTY_IOC_EOF         0x0026  /**< check if EOF in input           */
#define TTY_IOC_CBREAK      0x0027  /**< check if CBREAK in input        */
#define TTY_IOC_NEXTC       0x0028  /**< Peek at next input character    */

/* Driver functions */
struct tty *ttyAlloc(void);
devcall ttyInit(device *);
devcall ttyOpen(device *, va_list);
devcall ttyClose(device *);
devcall ttyRead(device *, char *, ushort);
devcall ttyWrite(device *, uchar *, ushort);
devcall ttyGetChar(device *);
devcall ttyPutChar(device *, uchar);
devcall ttyControl(device *, uchar, uchar, uchar);

#endif /* __TTY_H__ */
