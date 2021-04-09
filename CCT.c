#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int main(void)
{
    const char* ip = "143.110.211.139";
    const int port =  80;
    char msg[] = "HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html; charset=UTF-8\r\n\r\n"
       	"<!DOCTYPE html>"
	///INSERT HTML HERE\\\\;

    int sock = socket(AF_INET, SOCK_STREAM, 0), one = 1;
    if (sock == -1)
    {
        printf("Could not create the socket!\n");
        return 1;

    }
    printf("Socket created\n");

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

    struct sockaddr_in server, client; // sock address in inet, needs to be cast to sockaddr before use

    server.sin_family = AF_INET; // Internet protocol for web
    server.sin_port = htons(port); // htons is used to convert the port for the struct
    server.sin_addr.s_addr = inet_addr(ip); // address you are connecting to or displaying

    if ( bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) // bind the port and address to the socket, they are now in its structure
    {
        printf("Could not bind to port!\n");
        return 1;
    }

    printf("Socket bound to port %i and address %s\n", port, ip);
    listen(sock, 4); // listen on this socket for a connection, int to determine backlog of people able to connect
    while (1)
    {
        int sock_size = sizeof(struct sockaddr_in);
        int sock_client = accept(sock, (struct sockaddr *)&client, (socklen_t*)&sock_size);
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client.sin_addr.s_addr, str, INET_ADDRSTRLEN);
        if (sock_client < 0)
        {
            printf("Client unable to connect!\n");
            return 1;
        }

        printf("Client connected from address: %s\n", str);
        send(sock_client, msg, sizeof(msg), 0);
	close(sock_client);

    }
}
