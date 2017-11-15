#include <kernel.h>
#include <proc.h>
#include <semaphore.h>
#include <stdio.h>

extern void testPass(const char *);
extern void testFail(const char *);

void test_semWaiter(semaphore s, int times, uchar *testResult)
{
	while (times > 0)
    {
		wait(s);
		(*testResult)++;
		times--;
    }
}

bool test_checkSemCount(semaphore s, short c)
{
	char msg[50];

	if (c != semtab[s].count)
	{
		sprintf(msg, "count = %d, not %d", semtab[s].count, c);
		testFail(msg);
		return FALSE;
	}
	return TRUE;		
}

bool test_checkProcState(ushort pid, uchar state)
{
	char msg[50];

	if (state != proctab[pid].state)
	{
		sprintf(msg, "pid %d state %d, not %d", 
				pid, proctab[pid].state, state);
		testFail(msg);
		return FALSE;
	}
	return TRUE;
}

bool test_checkResult(uchar testResult, uchar expected)
{
	char msg[80];

	if (expected != testResult)
	{
		sprintf(msg, "process didn't seem to wait, expected %d, saw %d", 
				expected, testResult);
		testFail(msg);
		return FALSE;
	}
	return TRUE;
}

int test_semaphore(int argc, char **argv)
{
	int apid;
	bool passed = TRUE;
	semaphore s;
	uchar testResult = 0;
	char msg[50];

	printf("Test Suite: Single Semaphore\n");

	printf("  Semaphore creation: ");
	s = newsem(0);
	if (isbadsem(s))
	{
		passed = FALSE;
		sprintf(msg, "%d", s);
		testFail(msg);
	}
	else if (test_checkSemCount(s, 0))
	{ testPass(""); }
	else
	{ passed = FALSE; }

	ready(apid = create((void *)test_semWaiter, INITSTK, 31, "SEMAPHORE-A", 
						3, s, 1, &testResult), RESCHED_YES);

	printf("  Wait on semaphore: ");
	if ( test_checkProcState(apid, PRWAIT)
		 && test_checkSemCount(s, -1)
		 && test_checkResult(testResult, 0) )
	{ testPass(""); }
	else
	{ passed = FALSE; }

	signal(s);

	printf("  Signal semaphore: ");
	if ( test_checkProcState(apid, PRFREE)
		 && test_checkSemCount(s, 0)
		 && test_checkResult(testResult, 1) )
	{ testPass(""); }
	else
	{ passed = FALSE; }

	if (TRUE == passed)
	{ testPass(""); }
	else
	{ testFail(""); }
		
	/* Process A should be dead, but in case the test failed. */
	kill(apid);
	freesem(s);

	return OK;
}

