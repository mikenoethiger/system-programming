#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	// Idee:
	// 1. Pipe erstellen
	// 2. Fork
	// 3. In Child nochmals forken
	// 4. Unbenutze pipe enden schliessen
	// 5. Nachricht senden

	// 1. pipe()
	// 2. fork()
	// 3. if (pid == 0) fork()
	// 4. close() unbenutzte enden
	// 5. write(fd[1], "hi", 2);
	// 6. read(fd[0])

	int fd[2], s;
	char buf[10];
	pid_t fork1, fork2;

	pipe(fd);
	fork1 = fork();
	if (fork1 == 0) {
		fork2 = fork();
		if (fork2 == 0) {
			close(fd[0]);
			write(fd[1], "hi", 2);
			close(fd[1]);
		} else {
			close(fd[1]);
			read(fd[0], &buf, 2);
			printf("%s\n", buf);
			close(fd[0]);
		}
	} else {
		close(fd[0]);
		close(fd[1]);
		wait(&s);
		wait(&s);
	}

	return 0;
}