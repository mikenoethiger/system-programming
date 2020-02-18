#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* ======================================
 * Synchronize parent child process using
 * a pipe.
 * ======================================
 */

int main() {
	// fd[0] := read
	// fd[1] := write
	int fd[2];
	char buf;
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) {
		close(fd[0]);
		printf("child: do some work\n");
		close(fd[1]);
	} else {
		close(fd[1]);
		read(fd[0], &buf, sizeof(char));
		printf("parent: do some work\n");
		close(fd[0]);
	}
	return 0;
}