/**
 * @file write.c
 * @provides write
 *
 * $Id: write.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>

/**
 * write - write 1 or more bytes to a device
 * @param descrp definition of device on which to write
 * @param *buffer pointer to data to be written
 * @param count length of data to be written
 * @return function to write data on success, SYSERR on failure
 */
devcall write(ushort descrp, void *buffer, long count)
{
	device *devptr;

	if ( isbaddev(descrp) ) { return SYSERR; }
	devptr = &devtab[descrp];
	return( (*devptr->write)(devptr, buffer, count) );
}
