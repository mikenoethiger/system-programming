#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libs/my_stdlib.c"

/* ========================================
 * This program creates a named pipe (FIFO)
 * and reads from it until EOF. Start fifo2
 * program to send text.
 * Terminate with CTRL-C.
 * ========================================
 */

int main() {
	char *path_name = "/tmp/fifo1";
	char buf;
	int mode = S_IRUSR | S_IRGRP | S_IROTH |
			     S_IWUSR | S_IWGRP | S_IWOTH;
	int res = mkfifo(path_name, mode);
	// 17=file already exists, which means the named pipe already exists
	if (res != 0 && errno != 17) printerrno("create named pipe failed");
	int fd = open(path_name, O_RDONLY);
	printf("waiting for input...\n");
	while (read(fd, &buf, sizeof(buf))) {
		printf("%c", buf);
	}
	printf("EOF reached\n");
	close(fd);
	remove(path_name);
}