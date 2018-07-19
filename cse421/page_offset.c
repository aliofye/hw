#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *input = argv[1];

	// get address by converting input into long using atol()
	unsigned long address = atol(input);
	// page = address / 4KB
	unsigned long page = address / 4096;
	// offset = address % 4KB
	unsigned long offset = address % 4096;

	printf("The address %lu contains: ", address);
	printf("\n");
	printf("page number = %lu", page);
	printf("\n");
	printf("offset = %lu", offset);

	return 0;
}