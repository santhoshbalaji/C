#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int createSocket();
int read(int sock, char buffer[1024], int number);
int connectSocket(int sock, int port);

struct sockaddr_in address;
int sock = 0, valread;
struct sockaddr_in serv_addr;
char *hello = "Hello from client";
char buffer[1024] = {0};

int main(int argc, char const *argv[])
{

	sock = createSocket();
	int connectSoc = connectSocket(sock, 8080);
	send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
	return 0;
}

int createSocket(){
	int sockdef = socket(AF_INET,SOCK_STREAM,0);
	if (sockdef != 0){
		return sockdef;
	} else{
		perror("socket creation failed");
	}
}

int connectSocket(int sock, int port) {
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = port;
    int inetCheck = inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    if (inetCheck <= 0) {
    	perror("Invalid Address");
    }
   	int connectSocket = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
   	if (connectSocket < 0){
   		perror("error in connecting socket");
   	}else{
   		return connectSocket;
   	}	
}