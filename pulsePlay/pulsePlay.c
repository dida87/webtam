#ifdef UDP_H
#include "../libs/udp.h"
#endif


#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

//libs for pulse
#include <pulse/simple.h>
#include <pulse/error.h>

int sockfd;

void playback(int sockfd){
	
}

int main (int arcv, char* argv[]) {
	int playFromFile =0;
	int udpPort;

	//analyse arguments
	if(strcmp("-f", argv[1]) == 0) {	
		playFromFile = 1;	
	} else if {
		playFromFile = 0;
	} else {
		printf("Use %s -f|-r port", argv[0]);
	}

	//init socket	
	udpPort = atoi(argv[1]);
	sockfd = udp_socket_init(udpPort);

	//playback
	playback(sockfd);

	return 0;
}
