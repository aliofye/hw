/**
 * @file control.c
 * @provides control
 *
 * $Id: control.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <device.h>

/**
 * control - control a device (e.g., set the mode)
 * @param descrp definition of device to control
 * @param func specific control function for device
 * @param arg1 specific argument for func
 * @param arg2 specific argument for func
 * @return function to control device on success, SYSERR on failure
 */
devcall	control(ushort descrp, ushort func, long arg1, long arg2)
{
	device *devptr;

	if ( isbaddev(descrp) ) { return SYSERR; }
	devptr = &devtab[descrp];
	return ( (*devptr->control)(devptr, func, arg1, arg2) );
}
