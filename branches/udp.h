#include <sys/socket.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <netdb.h>
#include <stdio.h> /* for fprintf */ 
#include <string.h> /* for memcpy */

#define PORT 1153 
#define BUFSIZE 1024



int sockfd;
struct sockaddr_in udpServerSocket, udpClientSocket;

typedef struct {
        
        char data[BUFSIZE];
 } Message;

void init_udp_socket(char* host,int port);
void send_message(Message message);
Message received_message();

