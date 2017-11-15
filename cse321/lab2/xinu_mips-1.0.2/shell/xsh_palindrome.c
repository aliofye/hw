/** 
 * @file     xsh_palindrome.c
 * @provides xsh_palindrome
 *
 * $Id: xsh_help.c 226 2007-07-12 01:18:27Z mschul $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>

void rev(char *string) {
	int length, c;
	char *begin, *end, temp;
	
	length = string_length(string);
	begin = string;
	end = string;

	for(c = 0; c < length - 1; c++) {
		end++;
	}
	for(c = 0; c < length/2; c++) {
		temp = *end;
		*end = *begin;
		*begin = temp;

		begin++;
		end--;
	}
}

int string_length(char *pointer) {
	int c = 0;
	while(*(pointer + c) != '\0') {
		c++;
	}
	return c;
}

/*
 * palindrome retruns "yes" if string is a palindrome and "no" if it is not */

command xsh_palindrome(ushort stdout, ushort stdin, ushort stderr, ushort nargs, char *args[]){	
	

	if(nargs == 2 && strncmp(args[1], "--help", 6) == 0) {
		fprintf(stdout, "Usage: palindrome WORD\n");
		fprintf(stdout, "Check if WORD is a palindrome.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return SYSERR;
	}

	/* Check for correct number of arguments */
	if (nargs < 2)
	{
		fprintf(stderr,"palindrome: too few arguments\n");
		fprintf(stderr,"Try 'palindrome --help' for more information\n");
		return SYSERR;
	}
	if (nargs > 2)
	{
		fprintf(stderr,"palindrome: too many arguments\n");
		fprintf(stderr,"Try 'palindrome --help' for more information\n");
		return SYSERR;
	}


	
	char input[100];
	strcpy(input, args[1]);
	rev(input);
	
	if(strcmp(input, args[1]) == 0){
		fprintf(stdout, "yes");
	} else{
		fprintf(stdout, "no");
	}

	fprintf(stdout, "\n");
	/*there were no errors so, return OK */

	
	return OK;
}
