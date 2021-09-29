#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8005
char messages[500]; // to store the messages sent by the server

int main(int argc, char **argv)
{
    int socketfd;              // the socket file descriptor
    int connfd;                // the connection file descriptor
    struct sockaddr_in server; //Structure describing an Internet socket address. Found in netinet/in.h

    // Creating a socket
    /* socket() creates an endpoint for communication and returns a file descriptor that refers to that endpoint.  The file descriptor
       returned by a successful call will be the lowest-numbered file descriptor not currently open for the process.*/

    socketfd = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM is used for TCP connections
    if (socketfd == -1)
    {
        puts("Error! Failed to create a socket");
    }
    else
    {
        puts("Successfully created a socket");
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
    int bindStatus = bind(socketfd,(struct sockaddr *)(&server),sizeof(socket));
    if(bindStatus==0){
        puts("Socket binding successful");
    }
    else{
        puts("Socket binding failed");
    }

    // Listening
    int listenStatus = listen(socketfd,10);
    if(listenStatus==0){
        printf("Server listening on port %d",PORT);
    }
    else{
        puts("Oops, there was some error");
    }
    return 0;
}
