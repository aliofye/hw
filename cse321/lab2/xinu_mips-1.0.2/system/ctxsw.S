/**
 * @file     ctxsw.s
 * @provides ctxsw
 *
 * $Id: ctxsw.S 243 2007-07-13 22:37:19Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <mips.h>
	
.text
	.align 4
	.globl	ctxsw


/**
 * @fn void ctxsw(&oldsp, &newsp)
 *
 * Switch context (values in registers) to another process, saving the
 * current processes information. This function will not return as normally
 * thought as it will load in the stack pointer for a different process and
 * jump to that location and begin executing code.
 *
 * @param  &oldsp address of the outgoing stack pointer
 * @param  &newsp address of the incoming stack pointer
 * @return special case -- see above
 */
ctxsw:
	/* Build context record on stack.                               */
	addiu	sp, sp, -CONTEXT
	sw	ra, CONTEXT-4(sp)
	sw	ra, CONTEXT-8(sp)
	
	/* Save callee-save ("non-volatile") registers.                 */
	/* A call to ctxsw is either voluntary and caller-save regs.    */
	/* should not be assumed to be safe.                            */
	/* -OR-                                                         */
	/* when the processes quantum expires, in which case the        */
	/* interrupt handler will have already saved all the registers  */
	sw	s0, S0_CON(sp)
	sw	s1, S1_CON(sp)
	sw	s2, S2_CON(sp)
	sw	s3, S3_CON(sp)
	sw	s4, S4_CON(sp)
	sw	s5, S5_CON(sp)
	sw	s6, S6_CON(sp)
	sw	s7, S7_CON(sp)
	sw	gp, GP_CON(sp)
	sw	fp, FP_CON(sp)

	/* Save outgoing stack pointer.                                 */
	sw	sp, 0(a0)
	/* Load incoming stack pointer.                                 */
	lw	sp, 0(a1)

	/* Restore callee-save ("non-volatile") registers.              */
	lw	s0, S0_CON(sp)
	lw	s1, S1_CON(sp)
	lw	s2, S2_CON(sp)
	lw	s3, S3_CON(sp)
	lw	s4, S4_CON(sp)
	lw	s5, S5_CON(sp)
	lw	s6, S6_CON(sp)
	lw	s7, S7_CON(sp)
	lw	gp, GP_CON(sp)
	lw	fp, FP_CON(sp)
	
	/* Restore argument registers.  (Only meaningful first time)    */
	lw	a0, CONTEXT(sp)	
	lw	a1, CONTEXT+4(sp)	
	lw	a2, CONTEXT+8(sp)	
	lw	a3, CONTEXT+12(sp)	
	
	/* Tear down context record, and return.                        */
	lw	v0, CONTEXT-4(sp)
	lw	ra, CONTEXT-8(sp)
	addiu	sp, sp, CONTEXT
	jr	v0
	nop

