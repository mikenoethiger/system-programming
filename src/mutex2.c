#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_ITEMS 100

/* ====================================
 * Mutex demonstration with producer
 * consumer threads.
 * Exercise 2 of Assessment 2, Jan 2019
 * ====================================
 */

// n := number of produced items
int n;

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buf_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buf_not_empty = PTHREAD_COND_INITIALIZER;

void *producer_start(void *arg) {
	while (1) {
		pthread_mutex_lock(&buf_mutex);
		while (n >= MAX_ITEMS) {
			pthread_cond_wait(&buf_not_full, &buf_mutex);
		}
		n++;
		pthread_mutex_unlock(&buf_mutex);
		pthread_cond_signal(&buf_not_empty);
	}
}

void *consumer_start(void *arg) {
	while (1) {
		pthread_mutex_lock(&buf_mutex);
		while (n <= 0) {
			pthread_cond_wait(&buf_not_empty, &buf_mutex);
		}
		n--;
		pthread_mutex_unlock(&buf_mutex);
		pthread_cond_signal(&buf_not_full);
	}
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, NULL, producer_start, NULL);
	pthread_create(&t2, NULL, consumer_start, NULL);
	while (1) {
		printf("%d\n", n);
	}
	return 0;
}