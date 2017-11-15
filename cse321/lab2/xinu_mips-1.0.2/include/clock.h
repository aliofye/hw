/**
 * @file clock.h
 * Definitions relating to the hardware clock and the XINU clock interrupt.
 *
 * $Id: clock.h 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <queue.h>

#ifndef _CLOCK_H_
#define _CLOCK_H_

#define QUANTUM        10     /**< clock ticks until preemption        */
extern ulong preempt;

extern ulong ctr_mS;          /**< millisecond counter                 */
extern ulong clocktime;       /**< current time in secs since boot     */

extern ulong time_base_freq;  /**< frequency of hardware clock update  */
extern ulong time_intr_freq;  /**< frequency of XINU clock interrupt   */

extern queue sleepq;          /**< queue for sleeping processes        */

void      clockinit(void);
void      clock_update(ulong);
interrupt clockintr(void);

#endif /* _CLOCK_H_ */
