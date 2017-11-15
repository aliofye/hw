 /**
 * @file     xsh_mutual.c
 * @provides xsh_mutual
 *  *
 *   * $Id: xsh_mutual.c 226 2007-07-12 01:18:27Z mschul $
 *    */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

static semaphore mutex1 = NULL;

int counter = 0;

void proc1(void) {
	while(counter < 100) {
		sleep(rand()%10);
		wait(mutex1);
		fprintf(TTY0, "Count before is: %d, now proc1 will increase it by 1\n", counter);
		counter++;
		signal(mutex1);
	}
}

void proc2(void) {
	while(counter < 100) {
		sleep(rand()%10);
		wait(mutex1);
		fprintf(TTY0, "Count before is %d, now proc2 will increase it by 1\n", counter);
		counter++;
		signal(mutex1);
	}
}

void proc3(void) {
	while(counter < 100) {
		sleep(rand()%10);
		wait(mutex1);
		fprintf(TTY0, "Count before is %d, now proc3 will increase it by 1\n", counter);
		counter++;
		signal(mutex1);
	}
}

command	xsh_mutual(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]) {
	mutex1 = newsem(1);

	ready(create((void*)proc1, 1024, 20, "PROC1", 2, 0, NULL), RESCHED_NO);
	ready(create((void*)proc2, 1024, 20, "PROC2", 2, 0, NULL), RESCHED_NO);
	ready(create((void*)proc3, 1024, 20, "PROC3", 2, 0, NULL), RESCHED_NO);
	
	return OK;
}


