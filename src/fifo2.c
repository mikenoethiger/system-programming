#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libs/my_stdlib.c"

/* =======================================
 * This program opens the write end of a
 * named pipe (FIFO), then starts reading
 * from STDIN and writes all bytes to the
 * named pipe. Terminate with CTRL-C.
 * =======================================
 */

int main(int argc, char *argv[]) {
	char *path_name = "/tmp/fifo1";
	int fd = open(path_name, O_WRONLY);
	char buf;
	printf("enter text...\n");
	while (read(STDIN_FILENO, &buf, sizeof(buf))) {
		write(fd, &buf, sizeof(buf));
	}
	close(fd);
	return 0;
}