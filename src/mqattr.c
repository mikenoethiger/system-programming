#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include "libs/my_stdlib.c"

#define MSG_LEN 1024

/* =================================
 * A program to print the attributes
 * of a message queue
 * =================================
 */

int main(int argc, char *argv[]) {
	mqd_t mqd;
	int s;
	struct mq_attr attr;

	if (argc < 2) {
		printf("Usage: %s queue_name\nqueue_name must begin with a slash.\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	mqd = mq_open(argv[1], O_RDONLY);

	if (mqd == (mqd_t) -1) {
		perror("mq_open() failed");
		exit(EXIT_FAILURE);
	}

	s = mq_getattr(mqd, &attr);

	if (s != 0) {
		perror("mq_getattr() failed");
		exit(EXIT_FAILURE);
	}

	printf("mq_flags: %ld\n", attr.mq_flags);
	printf("mq_maxmsg: %ld\n", attr.mq_maxmsg);
	printf("mq_msgsize: %ld\n", attr.mq_msgsize);
	printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);

	s = mq_close(mqd);
	if (s != 0) {
		perror("mq_close() failed");
		exit(EXIT_FAILURE);
	}

	return 0;
}