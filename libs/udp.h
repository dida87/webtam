#ifndef UDP_H
#define UDP_H

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

type struct {
	int id;
	char[12] destAddress;
} MessageHeader;

type struct {
	MessageHeader messageHeader;
	char data[BUFF_SIZE];
} Message;

int udp_socket_init(char * port);
int send_msg(int sockfd, Message message);
int received_msg(int sockfd, Message);

#endif



