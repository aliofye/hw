/**
 * @file halt.s
 * @provides halt
 *
 * $Id: halt.S 243 2007-07-13 22:37:19Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <mips.h>
	
.text
	.align 4
	.globl	halt


/**
 * @fn void halt(void)
 *
 * Essentially this is a busy wait, however the opcode 'wait' puts the
 * processor in a powersave state (which can be awoken for arbitrary
 * reasons)
 */
halt:
	wait
	j	halt
	nop

