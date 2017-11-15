#include <kernel.h>
#include <proc.h>
#include <semaphore.h>
#include <stdio.h>

extern void testPass(const char *);
extern void testFail(const char *);

extern bool test_checkSemCount(semaphore s, short c);
extern bool test_checkProcState(ushort pid, uchar state);
extern bool test_checkResult(uchar testResult, uchar expected);

extern void test_semWaiter(semaphore s, int times, uchar *testResult);

int test_semaphore3(int argc, char **argv)
{
	int apid, bpid;
	bool passed = TRUE;
	semaphore s;
	uchar testResult = 0;
	char msg[50];

	printf("Test Suite: Counting Semaphores\n");

	printf("  Semaphore creation: ");
	s = newsem(1);
	if (isbadsem(s))
	{
		passed = FALSE;
		sprintf(msg, "%d", s);
		testFail(msg);
	}
	else if (test_checkSemCount(s, 1))
	{ testPass(""); }
	else
	{ passed = FALSE; }

	ready(apid = create((void *)test_semWaiter, INITSTK, 31, "SEMAPHORE-A", 
						3, s, 1, &testResult), RESCHED_NO);
	ready(bpid = create((void *)test_semWaiter, INITSTK, 31, "SEMAPHORE-B", 
						3, s, 1, &testResult), RESCHED_YES);

	printf("  Wait on semaphore: ");
	/* Process A should be admitted, but B should wait. */
	if ( test_checkProcState(apid, PRFREE)
		 && test_checkProcState(bpid, PRWAIT)
		 && test_checkSemCount(s, -1)
		 && test_checkResult(testResult, 1) )
	{ testPass(""); }
	else
	{ passed = FALSE; }

	signal(s);

	/* Process B waited, so signal should release it. */
	printf("  Signal waiting semaphore: ");
	if ( test_checkProcState(bpid, PRFREE)
		 && test_checkSemCount(s, 0)
		 && test_checkResult(testResult, 2) )
	{ testPass(""); }
	else
	{ passed = FALSE; }

	if (TRUE == passed)
	{ testPass(""); }
	else
	{ testFail(""); }
		
	/* Processes should be dead, but in case the test failed. */
	kill(apid);
	kill(bpid);
	freesem(s);

	return OK;
}

