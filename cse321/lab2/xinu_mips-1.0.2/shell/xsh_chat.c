/** 
* @file     xsh_chat.c
 * @provides xsh_chat
 *  *
 *   * $Id: xsh_chat.c 226 2007-07-12 01:18:27Z mschul $
 *    */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char id[30];
	char pwd[30];
} Accounts;



command xsh_chat(ushort stdout, ushort stdin, ushort stderr, ushort nargs, char *args[]){	
	if(nargs == 2 && strncmp(args[1], "--help", 6) == 0) {
		fprintf(stdout, "Usage: chat USERNAME\n");
		fprintf(stdout, "Log in to chat.\n");
		fprintf(stdout, "\t--help\t display this help and exit\n");
		return SYSERR;
	}

	
	if (nargs > 2)
	{
		fprintf(stderr,"chat: too many arguments\n");
		fprintf(stderr,"Try 'chat --help' for more information\n");
		return SYSERR;
	}
	
	
	int user;	
	Accounts accounts[2];
	strcpy(accounts[0].id, "eyad");
	strcpy(accounts[0].pwd, "pass");
	strcpy(accounts[1].id, "ali");
	strcpy(accounts[1].pwd, "pass");
	
	int status = 0;
	
	char input_id[30];
	char input_pwd[30];
	
	fprintf(stdout, "Enter your username: ");
	read(stdin, input_id, 30);
	fprintf(stdout, "Enter the password: ");
	read(stdin, input_pwd, 30);
	
	int i;
	for(i = 0; i < 2; i++) {
		if(strncmp(accounts[i].id, input_id, 3) == 0 && strncmp(accounts[i].pwd, input_pwd, 3)  == 0) { 
			fprintf(stdout, "\n--------------\n");
			fprintf(stdout, "Log in success\n");
			fprintf(stdout, "--------------\n");
			fprintf(stdout, "Welcome! %s\n\n", accounts[i].id);
			fprintf(stdout, "Type ""bye"" to quit\n\n");
			fprintf(stdout, "Start typing, then press enter to send. \n\n");
			input_id[3] = '\0';
			user = i;
			status = 1;
			break;
		}
	}
	
	//if login was unsuccessful
	if(status == 0) {
		fprintf(stdout, "\n--------------\n");
		fprintf(stdout, "Log in fail\n");
		fprintf(stdout, "--------------\n\n");
		return SYSERR;
	}
		
	
	char message[500];

	
	while(1) {
		if(user == 0) {
			
			read(stdin, message, 500);
			
			if(strncmp(message, "bye", 3) == 0) {
				fprintf(stdout, "You have logged out. \n");
				write(TTY0, "Eyad just left the room.", 24);
				break;
			}
			write(TTY0, "Eyad says: ", 11);
			write(TTY0, message, strlen(message));
		}
		else if(user == 1) {
			read(stdin, message, 500);

			if(strncmp(message, "bye", 3) == 0) {
				fprintf(stdout, "You have logged out. \n");
				write(TTY1, "Ali just left the room.", 23);
				break;
			}
			write(TTY1, "Ali says: ", 10);
			write(TTY1, message, strlen(message));
		}
	}
	
	/*there were no errors so, return OK */
	return OK;
}
