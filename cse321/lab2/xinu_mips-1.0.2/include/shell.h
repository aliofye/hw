/**
 * @file shell.h
 *
 * $Id: shell.h 238 2007-07-13 17:25:53Z brylow $
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#ifndef _SHELL_H_
#define _SHELL_H_

/* entry in command table */
struct centry
{
	char *name;                     /**< name of command                 */
	bool builtin;                   /**< built-in command?               */

	/** procedure */
	command (*procedure)(ushort, ushort, ushort, ushort, char *[]);
};

/* Size contstants */
#define SHELL_BUFLEN  80            /**< length of general buffer        */
#define SHELL_MAXTOK  16            /**< maximum tokens per line         */
#define SHELL_CMDSTK  8192          /**< size of command proc. stack     */
#define SHELL_CMDPRIO 20            /**< command process priority        */

/* Message constants */
#define SHELL_BANNER  "\033[1;35m........................................................\n           _ _            ______                _ \n     /\\   | (_)   ___    |  ____|              | |\n    /  \\  | |_   ( _ )   | |__  _   _  __ _  __| |\n   / /\\ \\ | | |  / _ \\/\\ |  __|| | | |/ _` |/ _` |\n  / ____ \\| | | | (_>  < | |___| |_| | (_| | (_| |\n /_/    \\_\\_|_|  \\___/\\/ |______\\__, |\\__,_|\\__,_|\n                                 __/ |            \n\n ........................................................\033[0;39m\n"
/** start message */
#define SHELL_START     "Welcome to the wonderful world of XINU!\n"
#define SHELL_EXIT      "Shell closed.\n"    /**< exit message           */
#define SHELL_PROMPT    "xsh$ "              /**< prompt                 */
#define SHELL_SYNTAXERR "Syntax error.\n"    /**< syntax error           */
#define SHELL_CHILDERR  "Cannot create.\n"   /**< command error          */

/* Token parsing functions */
#define isEndOfLine(c)    ((c) == '\0' || (c) == '\r' || (c) == '\n')
#define isQuote(c)        ((c) == '"' || (c) == '\'')
#define isOtherSpecial(c) ((c) == '<' || (c) == '>' || (c) == '&')
#define isWhitespace(c)   ((c) == ' ' || (c) == '\t')

extern struct centry commandtab[];   /**< table of commands              */
extern ulong         ncommand;       /**< number of commands in table    */

/* Function prototypes */
process shell(ushort);
short lexan(char *, ushort, char *, char *[]);
command xsh_exit(     ushort, ushort, ushort, ushort, char *[]);
command xsh_gpiostat( ushort, ushort, ushort, ushort, char *[]);
command xsh_help(     ushort, ushort, ushort, ushort, char *[]);
command xsh_kill(     ushort, ushort, ushort, ushort, char *[]);
command xsh_led(      ushort, ushort, ushort, ushort, char *[]);
command xsh_memstat(  ushort, ushort, ushort, ushort, char *[]);
command xsh_ps(       ushort, ushort, ushort, ushort, char *[]);
command xsh_reset(    ushort, ushort, ushort, ushort, char *[]);
command xsh_sleep (   ushort, ushort, ushort, ushort, char *[]);
command xsh_test(     ushort, ushort, ushort, ushort, char *[]);
command xsh_testsuite(ushort, ushort, ushort, ushort, char *[]);
command xsh_uartstat( ushort, ushort, ushort, ushort, char *[]);
command xsh_command(ushort, ushort, ushort, ushort, char *[]);
command xsh_palindrome(ushort, ushort, ushort, ushort, char *[]);
command xsh_cyclic(ushort, ushort, ushort, ushort, char *[]);
command xsh_synchronization(ushort, ushort, ushort, ushort, char *[]);
command xsh_mutual(ushort, ushort, ushort, ushort, char *[]);
command xsh_chat(ushort, ushort, ushort, ushort, char *[]);
#endif /* _SHELL_H_ */

