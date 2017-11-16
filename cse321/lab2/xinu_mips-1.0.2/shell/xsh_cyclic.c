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
#define HYPERX 6
#define FRAMEX 2
#define HYPERY 8
#define FRAMEY 2
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

void burn(void) { printf ("Burn Cycle\n");}

void (*tableone[HYPERX][FRAMEX])(void) = {
	{one, one},
	{two, three},
	{burn, two},
	{one, one},
	{burn, burn},
	{one, one}
};

void (*tabletwo[HYPERY][FRAMEY])(void) = {
	{one, three},
	{two, burn},
	{four, four},
	{one, three},
	{two, two},
	{one, burn},
	{one, burn},
	{two, two}
}; 

command xsh_cyclic(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]) {
    	if(nargs == 2 && strncmp(args[1], "--help", 6) == 0) {
			fprintf(stdout, "Usage: cyclic TABLE\n");
			fprintf(stdout, "Print out the cyclic TABLE, where TABLE can be 1 or 2\n");
			fprintf(stdout, "\t--help\t display this help and exit\n");
			return SYSERR;
		}

		/* Check for correct number of arguments */
		if (nargs < 2)
		{
			fprintf(stderr,"cyclic: too few arguments\n");
			fprintf(stderr,"Try 'cyclic --help' for more information\n");
			return SYSERR;
		}
		if (nargs > 2)
		{
			fprintf(stderr,"cylic: too many arguments\n");
			fprintf(stderr,"Try 'cyclic --help' for more information\n");
			return SYSERR;
		}
    	
		if(strncmp(args[1], "1", 1) == 0){
			while (1) {
	      		printf("\n Starting a new hyperperiod \n");
	      		for (slot=0; slot <HYPERX; slot++) { 
					printf ("\n Starting a new frame \n");
					for (cycle=0; cycle<FRAMEX; cycle++) {
			  			(*tableone[slot][cycle])();
			  			sleep(300);
					}
					sleep(300);
				}
				sleep(300);
			}
			return OK;	
		} else if(strncmp(args[1], "2", 1) == 0){
			while (1) {
	      		printf(" \n Starting a new hyperperiod \n");
	      		for (slot=0; slot <HYPERY; slot++) { 
					printf ("\n Starting a new frame \n");
					for (cycle=0; cycle<FRAMEY; cycle++) {
			  			(*tabletwo[slot][cycle])();
			  			sleep(300);
					}
					sleep(300);
				}
				sleep(300);
			}
			return OK;	
		} else {
			printf(" \n Invalid table number! \n");
			return SYSERR;
		}
    	
	return OK;
}