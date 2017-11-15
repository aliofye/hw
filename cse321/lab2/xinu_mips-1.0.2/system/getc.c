/**
 * @file getc.c
 * @provides getc
 *
 * $Id: getc.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>

/**
 * getc - get one character from a device
 * @param descrp definition of device from which to acquire character
 * @return function to get character on success, SYSERR on failure
 */
devcall getc(ushort descrp)
{
	device *devptr;

	if ( isbaddev(descrp) ) { return SYSERR; }
	devptr = &devtab[descrp];
	return ( (*devptr->getc)(devptr) );
}
