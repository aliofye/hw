/**
 * @file clkirq.S
 * @provides clock_update
 * Platform-dependent code for clock interrupt maintenance.
 *
 * $Id: clockirq.S 221 2007-07-11 18:45:46Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <mips.h>

.text
.align 4	

/**
 * @fn void clock_update(ulong ticks)
 * 
 * Reset hardware timer to go off again in 'ticks' clock cycles.
 * - If (ticks < * count < ticks*2),
 * - Then count is reset to (count - ticks),
 * - Else count is reset to zero.
 * This should mostly eliminate clock skew caused by lag between interrupt
 * request and timer register update.
 */
.globl clock_update
clock_update:
	mfc0	a1, CP0_COUNT
	mtc0	a0, CP0_COMPARE
	subu	a1, a1, a0
	bltu	a1, a0, up2
	mtc0	zero, CP0_COUNT
	jr	ra

up2:
	mtc0	a1, CP0_COUNT
	jr	ra 
	nop

