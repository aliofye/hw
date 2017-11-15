#include <kernel.h>
#include <proc.h>
#include <queue.h>
#include <semaphore.h>
#include <stdio.h>

extern void testPass(const char *);
extern void testFail(const char *);

int test_deltaQueue(int argc, char **argv)
{
	semaphore s;
	queue q;
	bool passed = TRUE;
	int apid, bpid, cpid, dpid;
	char msg[50];

	printf("Test Suite: Delta Queues\n");

	/* Create a semaphore so that we can use its queue. */
	s = newsem(0);

	if (isbadsem(s))
	{
		passed = FALSE;
		sprintf(msg, "No semaphore, %d", s);
		testFail(msg);
	}

	q = semtab[s].queue;

	/* Create some valid processes IDs to stuff in the queue.  */
	/* These processes had better not ever run. */
	apid = create((void *)NULL, INITSTK, 0, "DELTA-A", 0);
	bpid = create((void *)NULL, INITSTK, 0, "DELTA-B", 0);
	cpid = create((void *)NULL, INITSTK, 0, "DELTA-C", 0);
	dpid = create((void *)NULL, INITSTK, 0, "DELTA-D", 0);

	if ((SYSERR ==  apid) || (SYSERR == bpid) 
		|| (SYSERR == cpid) || (SYSERR == dpid))
	{ passed = FALSE; }

	printf("  Delta sorting");
	insertd(bpid, q, 5);
	insertd(cpid, q, 6);
	insertd(apid, q, 4);
	insertd(dpid, q, 7);

	if ( (4 == firstkey(q)) && (apid = dequeue(q))
		 && (1 == firstkey(q)) && (bpid = dequeue(q))
		 && (1 == firstkey(q)) && (cpid = dequeue(q))
		 && (1 == firstkey(q)) && (dpid = dequeue(q)) )
	{ testPass(""); }
	else
	{ passed = FALSE; testFail("insertd out of order"); }

	while (EMPTY != dequeue(q))
		;
	
	printf("  Same delta");
	insertd(apid, q, 5);
	insertd(bpid, q, 5);
	insertd(cpid, q, 5);
	insertd(dpid, q, 5);

	if ( (5 == firstkey(q)) && (apid = dequeue(q))
		 && (0 == firstkey(q)) && (bpid = dequeue(q))
		 && (0 == firstkey(q)) && (cpid = dequeue(q))
		 && (0 == firstkey(q)) && (dpid = dequeue(q)) )
	{ testPass(""); }
	else
	{ passed = FALSE; testFail("insertd out of order"); }

	while (EMPTY != dequeue(q))
		;
	
	kill(apid);
	kill(bpid);
	kill(cpid);
	kill(dpid);

    freesem(s);

	if (TRUE == passed)
	{ testPass(""); }
	else
	{ testFail(""); }
	
	return OK;
}
