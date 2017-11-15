/**
*file     xsh_cyclic.c
 * @provides xsh_cyclic
 *  *
 *   * $Id: xsh_cyclic.c 226 2007-07-12 01:18:27Z mschul $
 *    */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <stdio.h>
#include <ctype.h>
#include <clock.h>
#define SLOTX 6
#define CYCLEX 2
#define SLOT_T 2000

int cycle = 0;
int slot = 0;

void one(void) {
	printf("Task 1 running\n");
	sleep(1);
}

void two(void) {
	printf("Task 2 running\n");
	sleep(1);
}

void three(void) {
	printf("Task 3 running\n");
	sleep(1);
}

void four(void) {
	printf("Task 4 running\n");
	sleep(1);
}

void five(void) {
	printf("Task 5 running\n");
	sleep(1);
}

void burn(void) { printf (" brn cycle \n ");}

void (*ttable[SLOTX][CYCLEX])(void) = {
	{one, one},
	{two, three},
	{one, one},
	{two, burn},
	{one, one},
	{burn, burn}
};

command xsh_cyclic(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]) {
    	while (1) {
      		printf(" \n Starting a new hyperperiod \n");
      		for (slot=0; slot <SLOTX; slot++) { 
			printf ("\n Starting a new frame \n");
			for (cycle=0; cycle<CYCLEX; cycle++) {
	  			(*ttable[slot][cycle])();
			}
		}
	}	
	return OK;
}