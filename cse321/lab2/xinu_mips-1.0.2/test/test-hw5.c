#include <kernel.h>
#include <proc.h>
#include <stdio.h>

extern void testPass(const char *);
extern void testFail(const char *);

static void t5(int times, uchar *testArray, int *index)
{
	if (times > 0)
    {
		testArray[*index] = currpid;
		*index = *index + 1;
		testArray[*index] = times;
		*index = *index + 1;
		resched();
		t5(times - 1, testArray, index);
    }
}

#define TIMES 5

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
int test_recursion(int argc, char **argv)
{
	int apid, bpid, cpid, dpid, i, j;
	bool passed = TRUE;
	uchar testArray[100];
	int index = 0;

	printf("Test Suite: Recursion");
	ready(apid = create((void *)t5, INITSTK, 31, "RECURSION-A", 
						3, TIMES, testArray, &index), 0);
	ready(bpid = create((void *)t5, INITSTK, 32, "RECURSION-B", 
						3, TIMES, testArray, &index), 0);
	ready(cpid = create((void *)t5, INITSTK, 34, "RECURSION-C", 
						3, TIMES, testArray, &index), 0);
	ready(dpid = create((void *)t5, INITSTK, 32, "RECURSION-D", 
						3, TIMES, testArray, &index), 0);
	resched();

//	for (i = 0; i < 8 * TIMES; i++)
//	{ printf("testArray[%d] == %d\n", i, testArray[i]); }

	for (i = 0, j = TIMES; i < TIMES; i += 2, j--)
	{ 
		if (cpid != testArray[i])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i, cpid, testArray[i]);
		}
		if (j != testArray[i+1])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i+1, j, testArray[i+1]);
		}
	}

	for (i = TIMES * 2, j = TIMES; i < 6 * TIMES; i += 4, j--)
	{ 
		if (bpid != testArray[i])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i, bpid, testArray[i]);
		}
		if (j != testArray[i+1])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i+1, j, testArray[i+1]);
		}
	}

	for (i = TIMES * 2 + 2, j = TIMES; i < 6 * TIMES; i += 4, j--)
	{ 
		if (dpid != testArray[i])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i, dpid, testArray[i]);
		}
		if (j != testArray[i+1])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i+1, j, testArray[i+1]);
		}
	}

	for (i = 6 * TIMES, j = TIMES; i < 8 * TIMES; i += 2, j--)
	{ 
		if (apid != testArray[i])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i, apid, testArray[i]);
		}
		if (j != testArray[i+1])
		{
			passed = FALSE;
			printf("   Expected testArray[%d] == %d, not %d\n",
				   i+1, j, testArray[i+1]);
		}
	}

	if (TRUE == passed)
	{ testPass(""); }
	else
	{ testFail(""); }
		
	return OK;
}

