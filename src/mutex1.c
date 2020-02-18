#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* ====================================
 * Mutex demonstration through global
 * variable that gets incremented by
 * multiple threads
 * ====================================
 */

int g = 0;
int iterations = 100000;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg) {
	int i, loc;
	for (i = 0; i < iterations; i++) {
		pthread_mutex_lock(&mtx);
		loc = g;
		loc++;
		g = loc;
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

int main() {
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, increment, NULL);
	pthread_create(&tid2, NULL, increment, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("g=%d\n", g);
	return 0;
}