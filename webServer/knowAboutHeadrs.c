/*
1. #include <sys/socket.h>
This header file provides functions and structures needed for socket programming. It includes definitions for creating, managing, and using sockets for inter-process and network communication.

Common Functions from <sys/socket.h>:

socket(int domain, int type, int protocol): Creates a socket.
bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen): Binds a socket to an IP address and port.
listen(int sockfd, int backlog): Puts a socket into listening mode.
accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen): Accepts incoming connections (for TCP servers).
connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen): Connects a socket to a remote address (for clients).
send(int sockfd, const void *buf, size_t len, int flags): Sends data over a socket.
recv(int sockfd, void *buf, size_t len, int flags): Receives data from a socket.
close(int sockfd): Closes a socket.
shutdown(int sockfd, int how): Shuts down part or all of a socket connection.
2. #include <netinet/in.h>
This header file provides structures and constants related to Internet addresses, mainly used for working with IPv4 and IPv6 addresses.

Common Structures and Constants from <netinet/in.h>:

struct sockaddr_in: Represents an IPv4 socket address.
c
Copy
Edit
struct sockaddr_in {
    sa_family_t    sin_family;   // Address family (AF_INET for IPv4)
    in_port_t      sin_port;     // Port number (use htons() to convert)
    struct in_addr sin_addr;     // IPv4 address
};
struct in_addr: Used to store an IPv4 address.
c
Copy
Edit
struct in_addr {
    uint32_t s_addr;  // IPv4 address (use inet_addr() or inet_pton())
};
struct sockaddr_in6: Similar to sockaddr_in but for IPv6.
htonl(), htons(), ntohl(), ntohs(): Functions to convert values between host and network byte order.
*/