#include "server.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
void lunch(struct Server *server)
{
    char buffer[30000];
    int address_size = sizeof(server->address);
    int new_socket;
char *http_response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"  // Change content type to HTML
    "Content-Length: 52\r\n"  // Adjust content length
    "\r\n"
    "<html><body><h1>Hello, World!</h1></body></html>\n";
    while (1)
    {

    printf("======WAITING FOR CONNECTION=====\n");
    new_socket = accept(server->socket, (struct sockaddr *) &server->address, (socklen_t *)&address_size);
    read(new_socket, buffer, 30000);
    printf("%s\n", buffer);
        char method[10], request_path[100];
        sscanf(buffer, "%s %s", method, request_path);

        // **Handle /favicon.ico request (Return 404)**
        if (strcmp(request_path, "/favicon.ico") == 0)
        {
            char *not_found_response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Length: 0\r\n"
                "\r\n";
            write(new_socket, not_found_response, strlen(not_found_response));
            close(new_socket);
            continue; // Skip to the next connection after handling /favicon.ico
        }

    write(new_socket, http_response, sizeof(http_response));
    close(new_socket);
    }

}
int main ()
{
    struct Server server = server_constructor(0, SOCK_STREAM, AF_INET, 80, INADDR_ANY, 10, lunch);
    server.lunch(&server);
}