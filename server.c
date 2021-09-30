#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<stdlib.h>
#include<string.h>
#define MAX 200
#define PORT 8000
char messages[500]; // to store the messages sent by the server

void message(int socketfd);
int main(int argc, char **argv)
{
    int socketfd;              // the socket file descriptor
    int connfd;                // the connection file descriptor
    struct sockaddr_in server,cli; //Structure describing an Internet socket address. Found in netinet/in.h

    // Creating a socket
    /* socket() creates an endpoint for communication and returns a file descriptor that refers to that endpoint.  The file descriptor
       returned by a successful call will be the lowest-numbered file descriptor not currently open for the process.*/

    socketfd = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM is used for TCP connections
    if (socketfd == -1)
    {
        puts("Error! Failed to create a socket\n");
        exit(0);
    }
    else
    {
        puts("Successfully created a socket\n");
    }

    // void bzero(void *s, size_t n);
    /* The bzero() function erases the data in the n bytes of the memory
       starting at the location pointed to by s, by writing zeros (bytes
       containing '\0') to that area.*/
    bzero(&server,sizeof(server));
    
    // Now, assign the IP address and Port
    server.sin_family = AF_INET;
    // The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
    // When INADDR_ANY is specified in the bind call, the socket will be bound to all local interfaces. 
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    // The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
    server.sin_port = htons(PORT);


    // Binding the socket to IP and PORT
    int bindStatus = bind(socketfd,(struct sockaddr *)(&server),sizeof(server));
    if(bindStatus==0){
        puts("Socket binding successful\n");
    }
    else{
        puts("Socket binding failed\n");
        exit(0);
    }

    // Listening
    int listenStatus = listen(socketfd,10);
    if(listenStatus==0){
        printf("Server listening on port %d\n",PORT);
    }
    else{
        puts("Oops, there was some error\n");
        exit(0);
    }

    // Accept
    int len = sizeof(cli);
    connfd = accept(socketfd,(struct sockaddr*)(&cli),&len);
    if(connfd<0){
        puts("Accept failed\n");
    }
    else{
        puts("Received message\n");
    }
    message(connfd);
    close(socketfd);
    return 0;
}

void message(int socketfd){
    char buf[MAX];
    int n;
    while(1){
        n = 0;
        bzero(buf,MAX);
        read(socketfd,buf,sizeof(buf));
        printf("Client: %s",buf);
        bzero(buf,MAX);
        while((buf[n++]=getchar())!='\n');
        write(socketfd,buf,sizeof(buf));
        if(strncmp(buf,"exit",4)==0){
            puts("Server left the chat\n");
            break;
        }
    }
}
