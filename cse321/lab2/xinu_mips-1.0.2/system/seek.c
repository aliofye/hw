/**
 * @file seek.c
 * @provides seek
 *
 * $Id: seek.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>

/**
 * seek - position a device (very common special case of control)
 * @param descrp definition of device on which to seek
 * @param pos requested position to seek
 * @return function to seek on device on success, SYSERR on failure
 */
devcall seek(ushort descrp, long pos)
{
	device *devptr;

	if ( isbaddev(descrp) ) { return SYSERR; }
	devptr = &devtab[descrp];
	return ( (*devptr->seek)(devptr, pos) );
}
