/**
 * @file open.c
 * @provides open
 *
 * $Id: open.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <vararg.h>
#include <kernel.h>
#include <device.h>

/**
 * open - open a connection to a device/file (params 2 & 3 are optional)
 * @param descrp definition of device to open
 * @return function to open device on success, SYSERR on failure
 */
devcall open(ushort descrp, ...)
{
	device *devptr;
	va_list ap;
	devcall result;

	if ( isbaddev(descrp) ) { return SYSERR; }
	devptr = &devtab[descrp];
	va_start(ap, descrp);
	result = ( (*devptr->open)(devptr, ap) );
	va_end(ap);
	return result;
}
