/**
 * @file close.c
 * @provides close
 *
 * $Id: close.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>

/**
 * close - close a device
 * @param descrp definition of device to close
 * @return function to close device on success, SYSERR on failure
 */
devcall close(ushort descrp)
{
	device *devptr;

	if ( isbaddev(descrp) ) { return SYSERR; }
	devptr = &devtab[descrp];
	return ( (*devptr->close)(devptr) );
}
