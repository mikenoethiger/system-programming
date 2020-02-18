#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "libs/my_stdlib.c"

#define SERVICE "8080"
#define BACKLOG 10

/*
 * Exercise:
 * Schreiben Sie einen Web Server my_http_server.c,
 * der einkommende HTTP Requests auf Port 8080 liest
 * und folgende Antwort zum Client / Browser sendet:
 * "HTTP/1.1 200 OK\r\n"
 * "Connection: close\r\n"
 * "Content-Length: 5\r\n"
 * "\r\n"
 * "hello"
 */
int main() {
	// Vorgehen:
	// 1. sfd = socket()
	// 2. bind()
	// 3. listen()
	// 4. pfd = accept()
	// 5. write(pfd)
	int sfd, pfd, s;
	char *msg;
	struct addrinfo hints, *res;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1) printerrno("socket() failed");

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	s = getaddrinfo(NULL, SERVICE, &hints, &res);
	if (s != 0) {
		printf("getaddrinfo failed: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	s = bind(sfd, res->ai_addr, res->ai_addrlen);
	if (s != 0) printerrno("bind failed");

	s = listen(sfd, BACKLOG);
	if (s != 0) printerrno("listen failed");

	printf("listening...\n");

	msg = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 5\r\nHello World\r\n";
	for (;;) {
		pfd = accept(sfd, NULL, NULL);
		printf("connection accepted\n");
		if (pfd == -1) printerrno("accept failed");
		s = write(pfd, msg, strlen(msg));
		if (s == -1) printf("write failed");
	}
	return 0;
}