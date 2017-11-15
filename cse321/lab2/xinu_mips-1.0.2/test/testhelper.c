#include <kernel.h>
#include <proc.h>
#include <semaphore.h>
#include <stdio.h>

void testPass(const char *msg)
{
	printf("\033[40G[\033[1;32mPASSED\033[0;39m] %s\n", msg);
}

void testFail(const char *msg)
{
	printf("\033[40G[\033[1;31mFAILED\033[0;39m] %s\n", msg);
}
