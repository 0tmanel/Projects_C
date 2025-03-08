#include "server.h"
#include <stdio.h>
#include <stdlib.h>

struct Server server_constructor (int protocol, int service, int domain, int port, u_long interface, int backlog, void (*lunch)(struct Server *server))
{
    struct Server server;
    server.protocol = protocol;
    server.service = service;
    server.domain = domain;
    server.port = port;
    server.interface = interface;
    server.backlog = backlog;
    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(domain,service, protocol);
    if(server.socket == 0)
    {
        perror("failed to connect..\n");
        exit(1);
    }
    if (bind(server.socket, (struct sockaddr *)& server.address, sizeof(server.address)) < 0)
    {
        perror("failed to bind the socket..\n");
        exit(1);
    }
    if(listen(server.socket, server.backlog) < 0)
    {
        perror("failed to listen ...\n");
        exit(1);
    }
    server.lunch = lunch;
    return server;

}