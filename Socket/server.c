#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
// #define PORT 8080

int createSocket();
void bindSocket();
void listenSocket(int sock);
int acceptSocket(int sock, int port);
int read(int sock, char buffer[1024], int number);
void printNumber(int number);
void printString(char* str);

struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[1024] = {0}; 
char *hello = "Hello from server";

void *myThreadFun(void *vargp)
{
	int valread, acceptSock, sock;
	sock = (int *)vargp;
	printf("Came");		
	acceptSock = acceptSocket(sock, 8080);
	printf("Came to thread\n");
    valread = read( acceptSock, buffer, 1024);
    printf("%s\n", buffer);
    send(acceptSock, hello, strlen(hello), 0);
    // return NULL;
}

int main(int argc, char const *argv[])
{
	// int sockdef = socket(AF_INET, SOCK_STREAM, 0);
	// int setsockopt(sockdef, int level, int optname, const void *optval, socklen_t optlen);

	int sock, valread;
	sock = createSocket(8080);
	// int acceptSock;
	pthread_t tid;
	pthread_create(&tid, NULL, myThreadFun, (void *)sock);
	// valread = read( acceptSock , buffer, 1024);
    // printf("%s\n",buffer );
    // send(acceptSock , hello , strlen(hello) , 0 );
    // printf("Hello message sent\n");
	return 0;
}

int createSocket(int port){
	int sockdef = socket(AF_INET,SOCK_STREAM,0);
	if (sockdef != 0){
		bindSocket(sockdef, port);
		listenSocket(sockdef);
		return sockdef;
	} else{
		perror("socket creation failed");
	}
}

void bindSocket(int sock, int port) {
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = port;
	int bindSock = bind(sock, (struct sockaddr *)&address, sizeof(address));
	if (bindSock < 0){
		perror("bind failed");
	}
}

void listenSocket(int sock) {
	int listenSock;
	listenSock = listen(sock, 3);
	if (listenSock < 0){
		perror("listen failed");
	}
}

int acceptSocket(int socket, int port) {
	int acceptSocket;
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = port;
	acceptSocket = accept(socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (acceptSocket < 0) {
		perror("accept failed");
	}
}

void printNumber(int number) {
	printf("%d\n", number);
}

void printString(char* str) {
	printf("%s\n", str);
}