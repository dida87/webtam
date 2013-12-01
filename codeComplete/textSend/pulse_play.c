#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 1024
#define UDP_PORT 32000


int sockfd,n;
struct sockaddr_in servaddr,cliaddr;

char buf[BUFSIZE];

void init_socket_udp(int port)
{
	printf("Setup socket for listening...\n");

	sockfd=socket(AF_INET,SOCK_DGRAM,0);


	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(port);

	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	printf("Socket is ready to listen on port %d\n",port);
}


int receivedText()
{	
	//read data udp
	int r;
	if((r=recvfrom(sockfd,buf,BUFSIZE,0,NULL,NULL)) <= 0) {
		printf("r=%d\n",r);
	} else { 

		int i;
		printf("\nread=%d\n",r);
		printf("size of buff %d \n", sizeof(buf));
		if(buf)
			if(strlen(buf)){
				//buf[r]='\0';
				//printf("%s", buf);
				for (i=0; i< r; i++)
					printf("%c", buf[i]);
			}
	}
}


int main(int argc, char*argv[]) {
	char *host;
	int port;

	port = atoi(argv[1]);

	init_socket_udp(port);
	while(1) {
		receivedText();
	}
}
