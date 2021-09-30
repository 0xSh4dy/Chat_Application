#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define PORT 8000
#define MAX 200
void message(int socketfd);
int main(){
    int socketfd, connfd;
    struct sockaddr_in server;
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd==-1){
        puts("Failed to create a socket\n");
        exit(0);
    }
    else{
        puts("Created a socket\n");
    }
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);
    
    int connStatus = connect(socketfd,(struct sockaddr*)(&server),sizeof(server));
    if(connStatus==0){
        puts("Connected to the server\n");
    }
    else{
        puts("Connection failed\n");
        exit(0);
    }
    message(socketfd);
    close(socketfd);
    return 0;
}

void message(int socketfd){
    char buf[MAX];
    int n;
    while(1){
        bzero(buf,sizeof(buf));
        puts("Enter your mesage:");
        n = 0;
        while((buf[n++]=getchar())!='\n');
        write(socketfd,buf,sizeof(buf));
        bzero(buf,sizeof(buf));
        read(socketfd,buf,sizeof(buf));
        printf("Server: %s\n",buf);
        if(strncmp(buf,"exit",4)==0){
            puts("Connection closed\n");
            break;
        }

    }
}

