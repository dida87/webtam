#ifdef UDP_H
#include "udp.h"


int udp_socket_init(char* host, char*port) {
	//code init socket here
	//return sockfd
}


int send_msg(int sockfd, Message message){
	//send message via sockfd
	//return 1 if success, -1 if not
}


int received_msg (int sockfd, Message message) {
	//received message via sockfd
	// return 1 if success, -1 if not
	// check number of byte received and attribute dataLength in header
}



#endif
