#include "udp.h"


int udp_socket_init(char* port, struct sockaddr_in servaddr) {
	//code init socket here
	//return sockfd

	int sockfd;
	//struct sockaddr_in servaddr,cliaddr;

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(atoi(port));

	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(sockfd)
		printf("Socket is ready to listen on port %s\n",port);
	else {
		printf("error when bind socket");
	}

	return sockfd;
}


int send_msg(int sockfd, Message message, struct sockaddr_in servaddr){
	//send message via sockfd
	//return 1 if success, -1 if not

	char buffer[sizeof(message)];
   	memcpy(buffer, &message, sizeof(message));
	
	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

}


int received_msg (int sockfd, Message message) {
	//received message via sockfd
	// return 1 if success, -1 if not
	// check number of byte received and attribute dataLength in header
	int r;
	char buffer[sizeof(message)];

	if((r=recvfrom(sockfd,buffer,sizeof(buffer),0,NULL,NULL)) >= 0) {
		 memcpy(&message, buffer, sizeof(message));
	}
}



