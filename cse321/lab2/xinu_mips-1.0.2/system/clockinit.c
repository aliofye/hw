/**
 * @file clockinit.c
 * @provides clockinit
 *
 * $Id: clockinit.c 235 2007-07-12 22:52:09Z agember $
 */

#include <kernel.h>
#include <platform.h>
#include <interrupt.h>
#include <clock.h>
#include <queue.h>

#ifdef RTCLOCK
ulong time_base_freq = 0;     /** frequency of hardware clock update   */
ulong time_intr_freq = 0;     /** frequency of XINU clock interrupt    */
ulong ctr_mS = 0;             /** counts down in 1000ths of second     */
ulong clocktime = 0;          /** current time in seconds              */
queue sleepq;                 /** queue of sleeping processes          */
ulong preempt;                /** preemption counter                   */

/**
 * Initialize the clock and sleep queue.  This function is called at startup.
 */
void clockinit(void)
{
	sleepq = newqueue();            /* initialize sleep queue       */

	preempt = QUANTUM;              /* initial time quantum	        */
	ctr_mS = 1000;                  /* Set millisecond counter.     */
	
	if (0 == platform.time_base_freq)        /* Sensible default for freq.   */
	{ platform.time_base_freq = 100000000; }

	/* Program timer to trip every millisecond. */
	time_intr_freq = platform.time_base_freq / 1000;

#ifdef DETAIL
	kprintf("Time base %dHz, Clock interrupt at %dHz\r\n",
			platform.time_base_freq, 
			(platform.time_base_freq / time_intr_freq) );
#endif

	/* Register clock interrupt */
	interruptVector[IRQ_TIMER] = clockintr;
	enable_irq(IRQ_TIMER);
	clock_update(time_intr_freq);
}
#endif
