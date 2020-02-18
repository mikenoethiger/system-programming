#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* ==============================
 * This program starts several
 * threads who all increment a
 * global counter.
 * The global counter will be
 * printed every second to STDIN.
 * ==============================
 */

int counter = 0;

void *increment(void *arg) {
	pthread_t tid = pthread_self();
	printf("thread id: %ld\n", (long) tid);
	int i = *((int*) arg);
	while (1) {
		counter += i;
	}
	return NULL;
}

int main() {
	int i1 = 1, i2 = 2, i3 = -1, i4 = -2;
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, increment, &i1);
	pthread_create(&thread_id, NULL, increment, &i2);
	pthread_create(&thread_id, NULL, increment, &i3);
	pthread_create(&thread_id, NULL, increment, &i4);
	while (1) {
		printf("%d\n", counter);
		sleep(1);
	}
	return 0;
}