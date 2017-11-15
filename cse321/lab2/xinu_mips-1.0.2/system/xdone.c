/**
 * @file xdone.c
 * @provides xdone
 *
 * $Id: xdone.c 241 2007-07-13 22:24:20Z agember $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <gpio.h>

extern void halt(void);

/**
 * Print system completion message as last process exits.
 */

void xdone(void)
{
	kprintf("\r\n\r\nAll user processes have completed.\r\n\r\n");
	GPIO_CTRL_LED_OFF(GPIO_LED_CISCOWHT);
	halt();
}
