#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

clock_t t0;
clock_t t1;
struct tms buf;

void handler(int signal) {
	t1 = times(&buf);
	const long CLK_TCK = sysconf(_SC_CLK_TCK);
	printf("\n");
	printf("real: %lf\n", (double)(t1-t0)/CLK_TCK);
	printf("user: %lf\n", (double)buf.tms_utime/CLK_TCK);
}

int main() {
	t0 = times(&buf);
	printf("Press CTRL-C...\n");

	signal(SIGINT, handler);
	pause();

	return 0;
}