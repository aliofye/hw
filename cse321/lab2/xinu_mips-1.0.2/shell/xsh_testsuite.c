/**
 * @file     xsh_testsuite.c
 * @provides xsh_testsuite
 *
 * $Id: xsh_testsuite.c 242 2007-07-13 22:28:23Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <proc.h>
#include <xc.h>

#define NTESTS 9

local testItem(ushort, ushort, ushort, ushort);
extern int test_bigargs(int, char **);
extern int test_schedule(int, char **);
extern int test_recursion(int, char **);
extern int test_semaphore(int, char **);
extern int test_semaphore2(int, char **);
extern int test_semaphore3(int, char **);
extern int test_semaphore4(int, char **);
extern int test_procQueue(int, char **);
extern int test_deltaQueue(int, char **);

/**
 * Shell command (testsuite) provides a menu of standard XINU component
 * tests.
 * @param stdin descriptor of input device
 * @param stdout descriptor of output device
 * @param stderr descriptor of error device
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command	xsh_testsuite(ushort stdin, ushort stdout, ushort stderr,
					  ushort nargs, char *args[])
{	
	char   n;
	int    testnum;

	/* Output help, if '--help' argument was supplied */
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0) 
	{
		fprintf(stdout, "Usage: testsuite TESTNUM\n");
		fprintf(stdout, "Suite of standard XINU component tests.\n");
		fprintf(stdout, "0. Argument passing\n");
		fprintf(stdout, "1. Priority Scheduling\n");
		fprintf(stdout, "2. Recursion\n");
		fprintf(stdout, "3. Single Semaphore\n");
		fprintf(stdout, "4. Multiple Semaphores\n");
		fprintf(stdout, "5. Counting Semaphores\n");
		fprintf(stdout, "6. Killing Semaphores\n");
		fprintf(stdout, "7. Process Queues\n");
		fprintf(stdout, "8. Delta Queues\n");

		fprintf(stdout, "\t--help\t display this help and exit\n");
		return OK;
	}

	/* Check for correct number of arguments */
	if (nargs < 2) 
	{
		for ( n = 0; n < NTESTS; n++ )
		{ testItem( stdin, stdout, stderr, n ); }

		return OK;
	}

	if (nargs > 2) 
	{
		fprintf(stderr, "testsuite: too many arguments\n");
		fprintf(stderr, "Try 'testsuite --help' for more information\n");
		return SYSERR;
	}

	/* Check for valid device */
	testnum = (ushort)atol(args[1]);
	if ( testnum >= NTESTS )
	{
		fprintf(stderr, "testsuite: (%d) No such test.\n", testnum);
		return SYSERR;
	}

	testItem( stdin, stdout, stderr, testnum );

	return OK;
}

local testItem(ushort stdin, ushort stdout, ushort stderr, ushort testnum)
{
	irqmask ps;

	ps = disable();

	switch(testnum)
	{
	case 0:    
		ready(create((void *)test_bigargs, INITSTK, 30, 
					 "Test-BigArgs", 2, 0, NULL), RESCHED_YES);
		break;
	case 1:    
		ready(create((void *)test_schedule, INITSTK, 30, 
					 "Test-Schedule", 2, 0, NULL), RESCHED_YES);
		break;
	case 2:    
		ready(create((void *)test_recursion, INITSTK, 30, 
					 "Test-Recursion", 2, 0, NULL), RESCHED_YES);
		break;
	case 3:    
		ready(create((void *)test_semaphore, INITSTK, 30, 
					 "Test-Semaphore", 2, 0, NULL), RESCHED_YES);
		break;
	case 4:    
		ready(create((void *)test_semaphore2, INITSTK, 30, 
					 "Test-Semaphores", 2, 0, NULL), RESCHED_YES);
		break;
	case 5:
		ready(create((void *)test_semaphore3, INITSTK, 30, 
					 "Test-CountingSems", 2, 0, NULL), RESCHED_YES);
		break;
	case 6:
		ready(create((void *)test_semaphore4, INITSTK, 30, 
					 "Test-KillSem", 2, 0, NULL), RESCHED_YES);
		break;
	case 7:
		ready(create((void *)test_procQueue, INITSTK, 30, 
					 "Test-ProcQueue", 2, 0, NULL), RESCHED_YES);
		break;
	case 8:
		ready(create((void *)test_deltaQueue, INITSTK, 30, 
					 "Test-DeltaQueue", 2, 0, NULL), RESCHED_YES);
		break;
	  	  
	default:
		fprintf(stderr, "testsuite: (%d) No such test.\n", testnum);
	}

	sleep(10);
	restore(ps);
	return OK;
}
