#include "../libs/udp.h"


#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


//libs for pulse
#include <pulse/simple.h>
#include <pulse/error.h>

int sockfd;

struct sockaddr_in servaddr;
Message receivedMessage;
//char buffer[sizeof (receivedMessage)];  


void playback(int sockfd){
	
}

int main (int arcv, char* argv[]) {
	int playFromFile =0;
	int udpPort;

	//analyse arguments
	if(strcmp("-f", argv[1]) == 0) {	
		playFromFile = 1;	
	} else 
	if(strcmp("-r", argv[1]) == 0) {	
		playFromFile = 0;
	} else {
		printf("Use %s -f|-r port", argv[0]);
	}

	//init socket	
	udpPort = atoi(argv[1]);
	sockfd = udp_socket_init(argv[2], servaddr);


	printf("size of Message %d", sizeof(receivedMessage));
	//playback
	playback(sockfd);

	return 0;
}
