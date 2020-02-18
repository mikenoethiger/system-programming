#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include "libs/my_stdlib.c"

/* =============================
 * A program to create a message
 * queue.
 * =============================
 */

int main(int argc, char *argv[]) {
	mqd_t mqd;
	mode_t mode;
	int oflag;

	if (argc < 2) {
		printf("Usage: %s queue_name\nqueue_name must begin with a slash.\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* read and write permissions for the user */
	mode = S_IRUSR | S_IWUSR;
	/* O_CREAT creates a new queue,
	 * O_EXCL fails if the queue already exists */
	oflag = O_RDWR | O_CREAT | O_EXCL;
	mqd = mq_open(argv[1], oflag, mode, NULL);

	if (mqd == (mqd_t) -1) {
		perror("mq_open() failed");
		exit(EXIT_FAILURE);
	}

	printf("message queue created\n");

	return 0;
}