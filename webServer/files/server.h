#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
typedef struct Server{

    int protocol; // Protocol (e.g., TCP or UDP)
    int service; // Type of service (SOCK_STREAM for TCP, SOCK_DGRAM for UDP)
    int domain; // Address family (AF_INET for IPv4, AF_INET6 for IPv6)
    int port;  // Port number the server will listen on
    u_long interface;   // Network interface (e.g., INADDR_ANY for all available interfaces)
    int backlog;  // Max number of queued connections (for listen())
    struct  sockaddr_in address; // Server's address struct
    void (*lunch) (struct Server *server); // Function pointer to a method that starts the server
    int socket;
    
}Server;

struct Server server_constructor (int protocol, int service, int domain, int port, u_long interface, int backlog, void (*lunch)(struct Server *server));

#endif