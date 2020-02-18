#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

void timer_handler(int val) {
	printf("timer %d expired\n", val);
}

int main() {
	int s;
	timer_t timerid;
	struct itimerspec timer_spec;

	signal(SIGALRM, timer_handler);

	/* Specifying sevp as NULL is equivalent to specifying a pointer to a
       sigevent structure in which sigev_notify is SIGEV_SIGNAL, sigev_signo
       is SIGALRM, and sigev_value.sival_int is the timer ID. */
	s = timer_create(CLOCK_REALTIME, NULL, &timerid);
	if (s == -1) {
		perror("timer_create() failed");
		exit(EXIT_FAILURE);
	}

	/* set timer_spec to 3 seconds, without interval */
	timer_spec.it_value.tv_sec = 3;
	timer_spec.it_value.tv_nsec = 0;
	timer_spec.it_interval.tv_sec = 0;
	timer_spec.it_interval.tv_nsec = 0;

	/* 0 (relative) */
	s = timer_settime(timerid, 0, &timer_spec, NULL);
	if (s == -1) {
		perror("timer_settime() failed");
		exit(EXIT_FAILURE);
	}

	/* wait for timer to dispatch signal */
	pause();

	return 0;
}