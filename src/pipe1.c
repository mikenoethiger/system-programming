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
	char *text = "Hello World!";
	char buf;
	int i;

	pipe(fd);
	pid_t pid = fork();

	if (pid == 0) {
		// child
		close(fd[1]); // close unused pipe end
		while (read(fd[0], &buf, sizeof(buf))) {
			printf("%c", buf);
		}
		printf("\n");
		close(fd[0]); // close other pipe end
	} else {
		close(fd[0]); // close unused pipe end
		// parent
		i = 0;
		while (text[i] != '\0') {
			write(fd[1], text+i, sizeof(char));
			i++;
		}
		close(fd[1]); // close other pipe end
	}
	return 0;
}