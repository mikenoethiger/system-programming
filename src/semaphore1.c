#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N_CARS 7
#define N_SPACES 3

// Idee:
// 1. global variable sem_t sem
// 2. open: sem_init(&sem, 0, N_SPACES)
// 3. enter: sem_wait(&sem)
// 4. leave: sem_post(&sem)
// 5. close: sem_destroy(&sem)

sem_t sem;
int val;

void parking_garage_open() {
	sem_init(&sem, 0, N_SPACES);
} // TODO: implement

void parking_garage_enter() {
	sem_wait(&sem);
	sem_getvalue(&sem, &val);
	printf("%d cars in parking\n", N_SPACES-val);
} // TODO: implement

void parking_garage_leave() {
	sem_post(&sem);
	sem_getvalue(&sem, &val);
	printf("%d cars in parking\n", N_SPACES-val);
} // TODO: implement

void parking_garage_close() {
	sem_destroy(&sem);
} // TODO: implement

void *car_start(void *arg) {
	parking_garage_enter();
	int r = random() % 3;
	sleep(r); // 0-2s
	parking_garage_leave();
	pthread_exit(0);
}

void main() {
	pthread_t car_threads[N_CARS];
	parking_garage_open();
//	parking_garage_enter();
//	parking_garage_enter();
//	parking_garage_enter();
//	parking_garage_enter();
	for (int i = 0; i < N_CARS; i++) {
		pthread_create(&car_threads[i], NULL, car_start, NULL);
	}
	for (int j = 0; j < N_CARS; j++) {
		pthread_join(car_threads[j], NULL);
	}
	parking_garage_close();
}