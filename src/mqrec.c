#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include "libs/my_stdlib.c"

#define MSG_LEN 8192

/* =============================
 * A program to receive messages
 * from a message queue.
 * =============================
 */

int main(int argc, char *argv[]) {
	mqd_t mqd;
	int msg_prio, s;
	size_t msg_len = MSG_LEN;
	char msg[MSG_LEN];

	if (argc < 2) {
		printf("Usage: %s queue_name\nqueue_name must begin with a slash.\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	mqd = mq_open(argv[1], O_RDONLY);

	if (mqd == (mqd_t) -1) {
		perror("mq_open() failed");
		exit(EXIT_FAILURE);
	}

	s = mq_receive(mqd, msg, msg_len, &msg_prio);
	if (s == -1) {
		perror("mq_send() failed");
		exit(EXIT_FAILURE);
	}

	printf("%d bytes received with prio %d: %s\n", s, msg_prio, msg);

	s = mq_close(mqd);
	if (s != 0) {
		perror("mq_close() failed");
		exit(EXIT_FAILURE);
	}

	return 0;
}