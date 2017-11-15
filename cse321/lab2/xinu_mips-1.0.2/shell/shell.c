/**
 * @file     shell.c
 * @provides shell
 *
 * $Id: shell.c 236 2007-07-12 23:21:31Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <kernel.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <tty.h>
#include <proc.h>

struct centry commandtab[] = 
{
	{ "exit",      TRUE,  xsh_exit     },
	{ "kill",      TRUE,  xsh_kill     },
	{ "sleep",     TRUE,  xsh_sleep    },
	{ "gpiostat",  FALSE, xsh_gpiostat },
	{ "help",      FALSE, xsh_help     },
	{ "led",       FALSE, xsh_led      },
	{ "memstat",   FALSE, xsh_memstat  },
	{ "ps",        FALSE, xsh_ps       },
	{ "reset",     FALSE, xsh_reset    },
	{ "uartstat",  FALSE, xsh_uartstat },
	{ "?",         FALSE, xsh_help     },
	{ "testsuite", TRUE,  xsh_testsuite },
    { "test",      FALSE, xsh_test     },
	{ "com",      FALSE, xsh_command    },
    { "palindrome",      FALSE, xsh_palindrome    },
    { "cyclic", 	FALSE, xsh_cyclic     },
    { "synchronization", FALSE, xsh_synchronization },
    { "mutual", FALSE, xsh_mutual },
    { "chat",     FALSE, xsh_chat }	
};

ulong ncommand = sizeof( commandtab ) / sizeof( struct centry );

/**
 * The XINU shell.  Provides an interface to execute commands.
 * @param descrp descriptor of device on which the shell is open
 * @return OK for successful exit, SYSERR for unrecoverable error
 */
process shell(ushort descrp)
{
	char    buf[SHELL_BUFLEN];                 /* line input buffer        */
	ushort  buflen;                            /* length of line input     */
	char    tokbuf[SHELL_BUFLEN+SHELL_MAXTOK]; /* token value buffer       */
	short   ntok;                              /* number of tokens         */
	char    *tok[SHELL_MAXTOK];                /* pointers to token values */
	char    *outname;                          /* name of output file      */
	char    *inname;                           /* name of input file       */
	bool    background;                        /* is background proccess?  */
	ushort  stdin;                             /* stdin  device num        */
	ushort  stdout;                            /* stdout device num        */
	ushort  stderr;                            /* stderr device num        */
	syscall child;                             /* pid of child process     */
	ushort  i, j;                              /* temp variables           */

	/* Print shell banner */
	fprintf(descrp, SHELL_BANNER);
	/* Print shell welcome message */
	fprintf(descrp, SHELL_START);

	/* Continually receive and handle commands */
	while (TRUE)
	{
		/* Display prompt */
		fprintf(descrp, SHELL_PROMPT);

		/* Enable echo for input and receive input */
		control(descrp, TTY_IOC_SETIFLAG, TTY_IFLAG_ECHO, NULL);
		buflen = read(descrp, buf, SHELL_BUFLEN - 1);

		/* Check for CBREAK, clear vars and loop */
		if ( control(descrp, TTY_IOC_CBREAK, NULL, NULL) )
		{
			buflen = 0;
			continue;
		}

		/* Check for EOF and exit gracefully if seen */
		if ( control(descrp, TTY_IOC_EOF, NULL, NULL) ) { break; }

		/* Append null character to the end of the line input */
		buf[buflen] = '\0';

		/* Parse line input into tokens */
		if ( (ntok = lexan(buf, buflen, &tokbuf[0], &tok[0])) == SYSERR )
		{
			fprintf(descrp, SHELL_SYNTAXERR);
			continue;
		}

		/* Ensure parse generated tokens */
		if (0 == ntok) { continue; }

		/* Initialize command options */
		outname    = NULL;
		inname     = NULL;
		background = FALSE;

		/* Mark as background process, if last token is '&' */
		if ('&' == *tok[ntok-1])
		{
			ntok--;
			background = TRUE;
		}

		/* Check each token and perform special handling of '>' and '<' */
		for ( i = 0; i < ntok; i++ )
		{
			/* Background '&' should have already been handled; Syntax error */
			if ('&' == *tok[i])
			{
				ntok = -1;
				break;
			}

			/* Setup for output redirection if token is '>'  */
			if ('>' == *tok[i])
			{
				/* Syntax error */
				if (outname != NULL || i >= ntok-1)
				{
					ntok = -1;
					break;
				}

				outname = tok[i+1];
				ntok -= 2;

				/* shift tokens (not to be passed to command */
				for ( j = i; j < ntok; j++)
				{ tok[j] = tok[j+2]; }
				continue;
			}

			/* Setup for input redirection if token is '<' */
			if ('<' == *tok[i])
			{
				/* Syntax error */
				if(inname != NULL || i >= ntok-1)
				{
					ntok = -1;
					break;
				}
				inname = tok[i+1];
				ntok -= 2;

				/* shift tokens (not to be passed to command */
				for ( j = i; j < ntok; j++)
				{ tok[j] = tok[j+2]; }

				continue;
			}
		}

		/* Handle syntax error */
		if (ntok <= 0)
		{
			fprintf(descrp, SHELL_SYNTAXERR);
			continue;
		}

		/* Set command devices for input, output, and error */
		stdin  = descrp;
		stdout = descrp;
		stderr = descrp;

		/* Lookup first token in the command table */
		for (i = 0; i < ncommand; i++)
		{
			if (strcmp(commandtab[i].name, tok[0]) == 0) { break; }
		}

		/* Handle command not found */
		if (i >= ncommand)
		{
			fprintf(descrp, "%s: command not found\n", tok[0]);
			continue;
		}

		/* Handle command if it is built-in */
		if (commandtab[i].builtin)
		{
			if (inname != NULL || outname != NULL || background)
			{
				fprintf(descrp, SHELL_SYNTAXERR);
			}
			else
			{
				(*commandtab[i].procedure)(stdin, stdout, stderr, ntok, tok);
			}
			continue;
		}

		/* Spawn child process for non-built-in commands */
		child = create(commandtab[i].procedure, SHELL_CMDSTK, SHELL_CMDPRIO, 
		               commandtab[i].name, 5,
		               stdin, stdout, stderr, ntok, tok);

		/* Ensure child command process was created successfully */
		if (SYSERR == child)
		{
			fprintf(descrp, SHELL_CHILDERR);
			continue;
		} 

		if (background)
		{
			/* Make background process ready, but don't reschedule */
			ready(child, RESCHED_NO);
		}
		else
		{
			/* Clear waiting message; Reschedule; */
			while ( receive(FALSE) != NULL );
			ready(child, RESCHED_YES);

			/* Wait for command process to finish */
			while ( receive(TRUE) != child );
			sleep(10);
		}
    }

	/* Close shell */
	fprintf(descrp, SHELL_EXIT);
	sleep(10);
	return OK;
}
