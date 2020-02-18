#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

/* =======================================================
 * Server implementation of the echo service using unix
 * internet sockets. Echo is a service that echos data
 * that it receives on a UDP socket.
 * Example (with complementary comments) from:
 * http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
 * =======================================================
 * REFERENCES
 * memset()       http://man7.org/linux/man-pages/man3/memset.3.html
 * getaddrinfo()  http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
 * socket()       http://man7.org/linux/man-pages/man2/socket.2.html
 * bind()         http://man7.org/linux/man-pages/man2/bind.2.html
 * close()        http://man7.org/linux/man-pages/man2/close.2.html
 * freeaddrinfo() http://man7.org/linux/man-pages/man3/freeaddrinfo.3p.html
 * recvfrom()     http://man7.org/linux/man-pages/man3/recvfrom.3p.html
 * sendto()       http://man7.org/linux/man-pages/man3/sendto.3p.html
 * getnameinfo()  http://man7.org/linux/man-pages/man3/getnameinfo.3.html
 * gai_strerror() http://man7.org/linux/man-pages/man3/gai_strerror.3p.html
 * =======================================================
 */

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
	// hints     := used to specify the bounds for getaddrinfo(),
	//              such as family, socktype and flags.
	// result    := will contain the result of getaddrinfo(), which is
	//              a linked list of possible addresses
	// rp        := will be used to iterate over the result linked list
	//              until a "bindable" address could be found
	// sfd       := socket file descriptor
	// s         := a variable to store function result values which is
	//              used to detect errors (i.e. if result was -1)
	// peer_addr := according to https://stackoverflow.com/questions/16010622/reasoning-behind-c-sockets-sockaddr-and-sockaddr-storage/34236231
	//              sockaddr_storage is generic for sockaddr_in or sockaddr_in6
	//              which means it can hold an ipv4 as well as an ipv6 address.
	// peer_addr_len := length of peer_addr
	// nread     := number of bytes received on socket sfd
	// buf       := buffer size of one recvfrom() call
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;
	ssize_t nread;
	char buf[BUF_SIZE];

	if (argc != 2) {
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	// int getaddrinfo(const char *node,
	// 				   const char *service,
	//                 const struct addrinfo *hints,
	//                 struct addrinfo **res)
	s = getaddrinfo(NULL, argv[1], &hints, &result);
	if (s != 0) {
		// gai_strerror() shall return a text string describing an
		// error value for the getaddrinfo() and getnameinfo() functions
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	   Try each address until we successfully bind(2).
	   If socket(2) (or bind(2)) fails, we (close the socket
	   and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
					 rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                  /* Success */

		close(sfd);
	}

	if (rp == NULL) {               /* No address succeeded */
		fprintf(stderr, "Could not bind\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);           /* No longer needed */

	/* Read datagrams and echo them back to sender */

	for (;;) {
		peer_addr_len = sizeof(struct sockaddr_storage);
		// cast the specific sockaddr_storage into the generic sockaddr which
		// is required by recvfrom()
		nread = recvfrom(sfd, buf, BUF_SIZE, 0,
						 (struct sockaddr *) &peer_addr, &peer_addr_len);
		if (nread == -1)
			continue;               /* Ignore failed request */

		char host[NI_MAXHOST], service[NI_MAXSERV];

		// convert the address back to human readable information
		s = getnameinfo((struct sockaddr *) &peer_addr,
						peer_addr_len, host, NI_MAXHOST,
						service, NI_MAXSERV, NI_NUMERICSERV);
		if (s == 0)
			printf("Received %zd bytes from %s:%s\n",
				   nread, host, service);
		else
			// gai_strerror() shall return a text string describing an
			// error value for the getaddrinfo() and getnameinfo() functions
			fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

		if (sendto(sfd, buf, nread, 0,
				   (struct sockaddr *) &peer_addr,
				   peer_addr_len) != nread)
			fprintf(stderr, "Error sending response\n");
	}
}