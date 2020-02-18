#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

/* ============================================
 * Syspr13Assessment_4ibb1, 9)
 * Schreiben Sie ein Programm, das misst, wie
 * lange (Echtzeit) ein Signal hat. Die Messung
 * soll beim Senden von SIGUSR1 starten und
 * direkt nach dem Eintreffen stoppen.
 * ============================================
 */

struct timespec t0;
struct timespec t1;

void stop(int sigval) {
	clock_gettime(CLOCK_REALTIME, &t1);
	printf("%ld 10^-9 sec\n", (t1.tv_sec-t0.tv_sec)*1000000000 + t1.tv_nsec - t0.tv_nsec);
}

int main() {
	signal(SIGUSR1, stop);
	clock_gettime(CLOCK_REALTIME, &t0);
	raise(SIGUSR1);

	return 0;
}