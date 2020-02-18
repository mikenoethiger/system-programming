#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define THREADS_N 7

/* =============================================
 * Syspr13Assessment_4ibb1, 8)
 * Schreiben Sie ein Programm, das den Verkauf
 * von 99 Tickets durch 7 Verkäufer simuliert.
 * Verkäufe (parallel) dauern 1-3s, ein Semaphor
 * soll garantieren, dass es 99 sind.
 * =============================================
 */

int tickets = 0;
pthread_t threads[THREADS_N];
sem_t sem;

void *seller(void *arg) {
	int s;
	while (1) {
		s = sem_trywait(&sem);
		if (s == 0) {
			tickets++;
			printf("sold %d tickets\n", tickets);
			sleep((rand()%3)+1);
		} else {
			perror("sem_trywait() failed");
			break;
		}
	}
	return NULL;
}

int main() {
	int i;
	sem_init(&sem, 0, 99);

	for (i = 0; i < THREADS_N; i++) {
		pthread_create(threads + i, NULL, seller, NULL);
	}
	for (i = 0; i < THREADS_N; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("complete\n");

	return 0;
}