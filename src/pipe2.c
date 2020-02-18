#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* ======================================
 * Create a pipe between parent and child
 * process and send the parent process ID
 * to the child process via pipe.
 * ======================================
 */

int main() {
	// fd[0] := read
	// fd[1] := write
	int fd[2];
	char text[5];
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) {
		close(fd[0]);
		write(fd[1], "hello", sizeof(char)*5);
		close(fd[1]);
	} else {
		close(fd[1]);
		read(fd[0], text, sizeof(char)*5);
		printf("%s\n", text);
		close(fd[0]);
	}
	return 0;
}