/**
 * @file read.c
 * @provides read
 *
 * $Id: read.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>

/**
 * read - read one or more bytes from a device
 * @param descrp definition of device from which to read
 * @param *buffer pointer into read-to location
 * @param count length of buffer
 * @return function to read from device on success, SYSERR on failure
 */
devcall read(ushort descrp, void *buffer, long count)
{
	device *devptr;

	if ( isbaddev(descrp) ) { return SYSERR; }
	devptr = &devtab[descrp];
	return ( (*devptr->read)(devptr, buffer, count) );
}
