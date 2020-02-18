# Linux System Calls 3 IPC Sockets

IPC := Interprocess Communication

**Man Pages**

[Sockets](http://man7.org/linux/man-pages/man2/socket.2.html)

[UNIX Sockets](http://man7.org/linux/man-pages/man7/unix.7.html)

[Linux Sockets](http://man7.org/linux/man-pages/man7/socket.7.html)

[IP](http://man7.org/linux/man-pages/man7/ip.7.html)

**Internet Sockets**

[Linux IP Protocol](http://man7.org/linux/man-pages/man7/ip.7.html)

[Receiving UDP broadcast](https://stackoverflow.com/questions/12515005/receiving-udp-broadcast)

[Tutorialspoint Unix Sockets](https://www.tutorialspoint.com/unix_sockets/socket_quick_guide.htm)

[HTTP Specification](https://tools.ietf.org/html/rfc2616)

[socket](http://man7.org/linux/man-pages/man2/socket.2.html)

[bind](http://man7.org/linux/man-pages/man2/bind.2.html)

[listen](http://man7.org/linux/man-pages/man2/listen.2.html)

[accept](http://man7.org/linux/man-pages/man2/accept.2.html)

[connect](http://man7.org/linux/man-pages/man2/connect.2.html)

[sock_addr](http://man7.org/linux/man-pages/man2/bind.2.html) depends on the domain, unix domain sockets use filepaths, internet sockets use IP addresses and ports.

```C
struct sockaddr {
    sa_family_t sa_family; // AF_ Konstante 
    char sa_data[14];      // Länge variiert 
}
```

**Datagram Socket Specific Calls**

[recvfrom](http://man7.org/linux/man-pages/man3/recvfrom.3p.html)

[sendto](http://man7.org/linux/man-pages/man2/sendto.2.html)

**Byte Order Conversion**

Network to Host Byte Order:

uint32_t [ntohl](http://man7.org/linux/man-pages/man3/ntohl.3.html)(uint32_t netlong)

uint16_t [ntohs](http://man7.org/linux/man-pages/man3/ntohs.3.html)(uint16_t netshort)

Host to Network Byte Order:

uint32_t [htonl](http://man7.org/linux/man-pages/man3/htonl.3.html)(uint32_t hostlong)

uint16_t [htons](http://man7.org/linux/man-pages/man3/htons.3.html)(uint16_t hostshort)

**Loopback and Wildcard Addresses**

```C
INADDR_LOOPBACK // IPV4 Loopback 127.0.0.1
INADDR_ANY      // IPV4 Wildcard 0.0.0.0
IN6ADDR_LOOPBACK_INIT // IPV6 Loobpack ::1
IN6ADDR_ANY_INIT      // IPV6 Wildcard ::
```

**Internet Socket Address Conversion**

From Dot to Binary: [inet_pton](http://man7.org/linux/man-pages/man3/inet_pton.3.html)
From Binary to Dot: [inet_ntop](http://man7.org/linux/man-pages/man3/inet_ntop.3.html)

**Host Lookup**

[getaddrinfo](http://man7.org/linux/man-pages/man3/getaddrinfo.3.html)
[freeaddrinfo](http://man7.org/linux/man-pages/man3/freeaddrinfo.3.html)

**Structures**

```C
struct addrinfo {      // hint* u. result, Rest = 0
    int ai_flags*;     // Siehe Doku für AI_… Flags
    int ai_family*;    // AF_UNSPEC, AF_INET(6)
    int ai_socktype*;  // SOCK_STREAM, SOCK_DGRAM
    int ai_protocol*;         // 0
    socklen_t ai_addrlen;     // IP Adress-Länge
    struct sockaddr *ai_addr; // IP Adress-Struct
    char *ai_canonname;       // Kanonischer Name
    struct addrinfo *ai_next; // "next" od. NULL
};
```

```C
struct sockaddr {
   unsigned short   sa_family;   // AF_INET, AF_UNIX, AF_NS, AF_IMPLINK
   char             sa_data[14];
};
```

```C
struct sockaddr_in {
   short int            sin_family;  // AF_INET, AF_UNIX, AF_NS, AF_IMPLINK
   unsigned short int   sin_port;    // A 16-bit port number in Network Byte Order.
   struct in_addr       sin_addr;    // A 32-bit IP address in Network Byte Order.
   unsigned char        sin_zero[8]; // You just set this value to NULL as this is not being used.
};
```

```C
struct in_addr {
   unsigned long s_addr; // A 32-bit IP address in Network Byte Order.
};
```

**UNIX Domain Sockets**

Allow communication of two processes on the same host system. Provide Stream as well as datagram sockets. Access is managed by file permissions.

UNIX Domain Socket Address:

```C
struct sockaddr_un {
    sa_family_t sun_family; 
    char sun_path[108]; 
};
```