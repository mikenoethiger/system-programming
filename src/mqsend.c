#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include "libs/my_stdlib.c"

/* ===========================
 * A program to send messages
 * to a message queue.
 * ===========================
 */

int main(int argc, char *argv[]) {
	mqd_t mqd;
	int prio, s;

	if (argc < 3) {
		printf("Usage: %s queue_name msg <prio>\nqueue_name must begin with a slash.\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	prio = argc > 3 ? atoi(argv[3]) : 1;
	mqd = mq_open(argv[1], O_WRONLY);

	if (mqd == (mqd_t) -1) {
		perror("mq_open() failed");
		exit(EXIT_FAILURE);
	}

	s = mq_send(mqd, argv[2], strlen(argv[2]), prio);
	if (s != 0) {
		perror("mq_send() failed");
		exit(EXIT_FAILURE);
	}

	printf("message sent with prio %d\n", prio);

	s = mq_close(mqd);
	if (s != 0) {
		perror("mq_close() failed");
		exit(EXIT_FAILURE);
	}

	return 0;
}