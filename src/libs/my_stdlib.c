#include <stdlib.h>
#include <errno.h>
#include <string.h>

void printerrno(char *msg) {
	char *error_msg = strerror(errno);
	if (msg == NULL) {
		printf("%s (%d)\n", error_msg, errno);
	} else {
		printf("%s: %s (%d)\n", msg, error_msg, errno);
	}
	exit(errno);
}

void printbits(long i, int size) {
	int k, j = 1;
	j = j << (size-1);
	for (k = 0; k < size; k++) {
		printf("%ld", ((i&j)>>(size-1))&1);
		i = i << 1;
	}
	printf("\n");
}

void printbitsi(int i) {
	printbits((long) i, sizeof(int)*8);
}

void printbitsc(char c) {
	printbits((long) c, sizeof(char)*8);
}