/**
* @file     xsh_synchronization.c
 * @provides xsh_synchronization
 *  *
 *   * $Id: xsh_synchronization.c 226 2007-07-12 01:18:27Z mschul $
 *    */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

static semaphore synch12 = NULL;
static semaphore synch23 = NULL;
static semaphore synch31 = NULL;

int sync_counter = 0;

void process1(void) {
        while(sync_counter < 100) {
                sleep(rand()%10);
                wait(synch31);
                fprintf(TTY0, "Counter before is: %d, now process1 is increasing it by 1\n", 
sync_counter);
                sync_counter++;
                signal(synch12);
        }
}

void process2(void) {
         while(sync_counter < 100) {
                sleep(rand()%10);
                wait(synch12);
                fprintf(TTY0, "Counter before is: %d, now process2 is increasing it by 1\n", 
sync_counter);
                sync_counter++;
                signal(synch23);
        }
}

void process3(void) {
	while(sync_counter < 100) {
		sleep(rand()%10);
                wait(synch23);
                fprintf(TTY0, "Counter before is: %d, now process3 is increasing it by 1\n", 
sync_counter);
                sync_counter++;
                signal(synch31);
        }
}


command	xsh_synchronization(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]) {
	synch12 = newsem(0);
	synch23 = newsem(0);
	synch31 = newsem(0);
	
	ready(create((void*)process1, 1024, 20, "PROC1", 2, 0, NULL), RESCHED_NO);
	ready(create((void*)process2, 1024, 20, "PROC2", 2, 0, NULL), RESCHED_NO);
	ready(create((void*)process3, 1024, 20, "PROC3", 2, 0, NULL), RESCHED_NO);
	signal(synch31);

	return OK;
}
