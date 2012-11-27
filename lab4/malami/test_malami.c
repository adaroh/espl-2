#include <stdlib.h>
#include <stdio.h>

/*TODO: add signature for malami */
extern int malami(char* i);

int main(int argc, char **argv) {
	/* TODO: call malami */
	printf("%d\n", (malami(argv[1])));
	
	return 0;
}
