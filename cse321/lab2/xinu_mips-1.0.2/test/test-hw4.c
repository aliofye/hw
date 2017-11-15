#include <kernel.h>
#include <proc.h>
#include <stdio.h>

extern void testPass(const char *);
extern void testFail(const char *);

static void bigargs(uchar a, uchar b, uchar c, uchar d, uchar e, uchar f,
					uchar *testArray)
{
	testArray[0] = a;
	testArray[1] = b;
	testArray[2] = c;
	testArray[3] = d;
	testArray[4] = e;
	testArray[5] = f;
	testArray[6] = a + b + c + d + e + f;
	return;
}

static void t4(int times, uchar *testArray, int *shared)
{
	int i = 0;

	for (i = 0; i < times; i++)
    {
		testArray[*shared] = currpid;
		*shared = *shared + 1;
		resched();
    }
}

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
int test_bigargs(int argc, char **argv)
{
	uchar testArray[20];
	printf("Test Suite: More than four arguments");
	
	ready(create((void *)bigargs, INITSTK, 31, "BIGARGS", 
				 7, 10, 20, 30, 40, 50, 60, testArray), RESCHED_YES);
	
	if ((10 == testArray[0])
		&& (20 == testArray[1])
		&& (30 == testArray[2])
		&& (40 == testArray[3])
		&& (50 == testArray[4])
		&& (60 == testArray[5])
		&& (210 == testArray[6]))
	{ testPass(""); }
	else
	{ testFail(""); }

	return OK;
}

#define TIMES 5

int test_schedule(int argc, char **argv)
{
	uchar testArray[20];
	int shared = 0;

	int apid, bpid, cpid, dpid, i;
	bool passed = TRUE;

	printf("Test Suite: Priority Scheduling");
	ready(apid = create((void *)t4, INITSTK, 31, "PRIORITY-A", 
						3, TIMES, testArray, &shared), 0);
	ready(bpid = create((void *)t4, INITSTK, 32, "PRIORITY-B", 
						3, TIMES, testArray, &shared), 0);
	ready(cpid = create((void *)t4, INITSTK, 34, "PRIORITY-C", 
						3, TIMES, testArray, &shared), 0);
	ready(dpid = create((void *)t4, INITSTK, 32, "PRIORITY-D", 
						3, TIMES, testArray, &shared), 0);
	resched();

	for (i = 0; i < TIMES; i++)
	{ 
		if (cpid != testArray[i]) 
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i, cpid, testArray[i]);
		}
	}

	for (i = TIMES; i < 3 * TIMES; i += 2)
	{ 
		if (bpid != testArray[i])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i, bpid, testArray[i]);
		}
	}

	for (i = TIMES + 1; i < 3 * TIMES; i += 2)
	{ 
		if (dpid != testArray[i])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i, dpid, testArray[i]);
		}
	}
 
	for (i = 3 * TIMES; i < 4 * TIMES; i++)
	{ 
		if (apid != testArray[i])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i, apid, testArray[i]);
		}
	}

	if (TRUE == passed)
	{ testPass(""); }
	else
	{ testFail(""); }
		
	return OK;
}
