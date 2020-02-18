#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* ====================================
 * This program starts a threads and
 * prints its thread id, arguments as
 * well as the threads retval.
 * ====================================
 */

int counter = 0;

void *multiply(void *arg) {
	int *a = (int*) arg;
	int *b = (a+1);
	int *c = (a+2);
	printf("Thread args: [%d,%d]\n", *a, *b);
	*c = *a * *b;
	return c;
}

int main() {
	int args[3] = {2,3,0};
	pthread_t tid;
	pthread_create(&tid, NULL, multiply, args);
	printf("Thread ID: %ld\n", (long) tid);
	void *retval;
	pthread_join(tid, &retval);
	printf("Thread retval: %d\n", *((int*)retval));
	return 0;
}