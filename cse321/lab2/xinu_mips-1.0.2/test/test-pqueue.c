#include <kernel.h>
#include <proc.h>
#include <queue.h>
#include <semaphore.h>
#include <stdio.h>

extern void testPass(const char *);
extern void testFail(const char *);

int test_procQueue(int argc, char **argv)
{
	semaphore s;
	queue q;
	bool passed = TRUE;
	int apid, bpid, cpid, dpid;
	char msg[50];

	printf("Test Suite: Process Queues\n");

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
	apid = create((void *)NULL, INITSTK, 0, "PQUEUE-A", 0);
	bpid = create((void *)NULL, INITSTK, 0, "PQUEUE-B", 0);
	cpid = create((void *)NULL, INITSTK, 0, "PQUEUE-C", 0);
	dpid = create((void *)NULL, INITSTK, 0, "PQUEUE-D", 0);

	if ((SYSERR ==  apid) || (SYSERR == bpid) 
		|| (SYSERR == cpid) || (SYSERR == dpid))
	{ passed = FALSE; }

	printf("  Priority sorting");
	insert(cpid, q, 5);
	insert(bpid, q, 6);
	insert(dpid, q, 4);
	insert(apid, q, 7);

	if ( (7 == firstkey(q)) && (apid = dequeue(q))
		 && (6 == firstkey(q)) && (bpid = dequeue(q))
		 && (5 == firstkey(q)) && (cpid = dequeue(q))
		 && (4 == firstkey(q)) && (dpid = dequeue(q)) )
	{ testPass(""); }
	else
	{ passed = FALSE; testFail("insert out of order"); }

	while (EMPTY != dequeue(q))
		;
	
	printf("  Same priority");
	insert(apid, q, 5);
	insert(bpid, q, 5);
	insert(cpid, q, 5);
	insert(dpid, q, 5);

	if ( (5 == firstkey(q)) && (apid = dequeue(q))
		 && (5 == firstkey(q)) && (bpid = dequeue(q))
		 && (5 == firstkey(q)) && (cpid = dequeue(q))
		 && (5 == firstkey(q)) && (dpid = dequeue(q)) )
	{ testPass(""); }
	else
	{ passed = FALSE; testFail("insert out of order"); }

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
