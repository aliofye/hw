/**
 * @file putc.c
 * @provides putc
 *
 * $Id: putc.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>

/**
 * putc - write a single character to a device
 * @param descrp definition of device on which to write
 * @param ch character to write
 * @return function to write character on success, SYSERR on failure
 */
devcall putc(ushort descrp, char ch)
{
	device *devptr;

	if (isbaddev(descrp) ) { return SYSERR; }
	devptr = &devtab[descrp];
	return ( (*devptr->putc)(devptr, ch) );
}
