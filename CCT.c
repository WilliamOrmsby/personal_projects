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
	"<html>"
	"<head>"
	"<title>The Rock</title>"
	"</head>"
	"<style>"
	".otext{ text-align: center; position: relative; font-family: Verdana, sans-serif; font-size: 20px;}"
	"h1{text-align: center; color: #FFFFFF;text-shadow: 0 1px 0 #CCCCCC, 0 2px 0 #c9c9c9, 0 3px 0 #bbb, 0 4px 0 #b9b9b9, 0 5px 0 #aaa, 0 6px 1px rgba(0,0,0,.1), 0 0 5px rgba(0,0,0,.1), 0 1px 3px rgba(0,0,0,.3), 0 3px 5px rgba(0,0,0,.2), 0 5px 10px rgba(0,0,0,.25), 0 10px 10px rgba(0,0,0,.2), 0 20px 20px rgba(0,0,0,.15);}"
	".tracking-in-expand{animation:tracking-in-expand 2.1s cubic-bezier(.215,.61,.355,1.000) both}"
	"@keyframes tracking-in-expand{0%{letter-spacing:-.5em;opacity:0}40%{opacity:.6}100%{opacity:1}}"
	"@keyframes rotate-center{0%{transform:rotate(0)}100%{transform:rotate(360deg)}}"
	".rotate-center{animation:rotate-center .6s ease-out both}"
	"body { background: linear-gradient(268deg, #a6bb29 0%, #00ffc5 100%);}"
	".container{ position: relative; height:640; width:960; background-image: url(https://specials-images.forbesimg.com/imageserve/5f5ebdfe1a1834b803586841/960x0.jpg) height=320px width=480px;}"
	"</style>"
	"<body><div class=""tracking-in-expand"">"
	"<h1 style =""color: #FFFFFF;text-shadow: 0 1px 0 #CCCCCC, 0 2px 0 #c9c9c9, 0 3px 0 #bbb, 0 4px 0 #b9b9b9, 0 5px 0 #aaa, 0 6px 1px rgba(0,0,0,.1), 0 0 5px rgba(0,0,0,.1), 0 1px 3px rgba(0,0,0,.3), 0 3px 5px rgba(0,0,0,.2), 0 5px 10px rgba(0,0,0,.25), 0 10px 10px rgba(0,0,0,.2), 0 20px 20px rgba(0,0,0,.15);color: #FFFFFF; text-align: center;"">Do You Smell What He is Cooking?</h1></div>"
	"<h3 style = ""text-align: center; font-family;Monaco"">The Rock</h3>"
	"<p style = ""text-align: center; text-indent: 15px;"">The Rock is the 8th in A line of great men that includes<br> the like of Abraham Lincoln, Paddington Bear, and Magneto.</p>"
	"<img src=""https://static.wikia.nocookie.net/prowrestling/images/a/ad/Wwe_the_rock_png_by_double_a1698_day9ylt-pre_%281%29.png"">"
	"<h4 style=""text-align: center; font: 10px Verdana; transition: all 4s linear;"">Hi I am the Rock, and I am cooking.</h4>"
	"<h3 style=""text-align: center;"">Fun Facts about the Rock</h3>"
	"<ul><li> He is not Actually a Rock, He is a Meteorite</li><li> He Cooks with Food Normal Humans Can't Smell</li><li> Yes</li></ul>"
	"<div class=""container"">Hello I am cooking!</div>"
	"</body></html>";

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
