/**
 * @file ioerr.c
 * @provides ioerr
 *
 * $Id: ioerr.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>

/**
 * ioerr - return an error (used for "error" entries in devtab)
 * @return SYSERR
 */
devcall ioerr(void)
{
	return SYSERR;
}
