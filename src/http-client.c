#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "libs/my_stdlib.c"

#define NODE "tmb.gr"
#define SERVICE "80"
#define MSG_MAX 500

void fail(char *msg) {
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/*
 * Exercise:
 * Schreiben Sie einen Web Client my_http_client.c, der
 * folgenden HTTP Request an den Host tmb.gr, Port 80
 * sendet, die Antwort liest, und auf stdout ausgibt:
 * "GET /syspr HTTP/1.1\r\n"
 * "Host: tmb.gr\r\n"
 * "\r\n"
 */
int main(int argc, char *argv[]) {
	if (argc < 4) {
		printf("Usage: %s host port uri\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Vorgehen:
	// 1. socket()
	// 2. connect()
	// 3. write()
	// 4. read()
	// 5. close()
	int sfd, s;
	struct addrinfo hints, *res;
	char msg[MSG_MAX];
	char buf;

	// create socket
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1) fail("connect failed");

	// resolve address
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
//	s = getaddrinfo(NODE, SERVICE, &hints, &res);
	s = getaddrinfo(argv[1], argv[2], &hints, &res);
	if (s != 0) {
		printf("getaddrinfo failed: %s", gai_strerror(s));
		fail("");
	}
	// connect to tmb.gr:80
	s = connect(sfd, res->ai_addr, res->ai_addrlen);
	if (s != 0) printerrno("connect failed");

	// write request
	msg[0] = '\0';
	strcat(msg, "GET ");
	strcat(msg, argv[3]);
	strcat(msg, " HTTP/1.1\r\nHost: ");
	strcat(msg, argv[1]);
	strcat(msg, "\r\n\r\n");
//	msg = "GET /syspr HTTP/1.1\r\nHost: tmb.gr\r\n\r\n";
//	strcpy(msg, "GET /syspr HTTP/1.1\r\nHost: tmb.gr\r\n\r\n");
	s = write(sfd, msg, strlen(msg));
	if (s == -1) printerrno("write failed");

	// read response and write to stout
	while ((s = read(sfd, &buf, sizeof(buf)))) {
		if (s == -1) printerrno("read failed");
		printf("%c", buf);
	}

	s = close(sfd);
	if (s != 0) fail("close failed");
	return 0;
}