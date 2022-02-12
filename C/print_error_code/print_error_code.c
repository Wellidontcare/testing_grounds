#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int error = atoi(argv[1]);
	fprintf(stdout, "%s\n", strerror(error));
	return 0;
	}
