/**
 * @file ionull.c
 * @provides ionull
 *
 * $Id: ionull.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>

/**
 * ionull - do nothing (used for "don't care" entries in devtab)
 * @return OK
 */
devcall ionull(void)
{
	return OK;
}
