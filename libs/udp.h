
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFF_SIZE 1024

typedef struct {
	int id;
	char destAddress[12];
} MessageHeader;

typedef struct {
	MessageHeader messageHeader;
	char data[BUFF_SIZE];
} Message;

int udp_socket_init(char * port, struct sockaddr_in servaddr);
int send_msg(int sockfd, Message message, struct sockaddr_in servaddr);
int received_msg(int sockfd, Message);




