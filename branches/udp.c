#include "udp.h"

void init_udp_socket(char* host, int port) {
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("cannot create socket"); 
        return;
    }

    memset((char *)&udpServerSocket, 0, sizeof(udpServerSocket)); 
    udpServerSocket.sin_family = AF_INET; 
    //if(host!=NULL)
    //    udpServerSocket.sin_addr.s_addr = inet_addr(host);
    //else
        udpServerSocket.sin_addr.s_addr = htonl(INADDR_ANY); 
    udpServerSocket.sin_port = htons(port); 


    if (bind(sockfd, (struct sockaddr *)&udpServerSocket, sizeof(udpServerSocket)) < 0) { 
        perror("bind failed"); 
        return; 
    }
}

void send_message(Message message) {
    
    char buffer[sizeof(message)];
    memcpy(buffer, &message, sizeof(message));
    int nbByteSent;

    printf("send Message %d\n", sizeof(message));

    /* send a message to the server */
    if ((nbByteSent=sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&udpServerSocket, sizeof(udpServerSocket)) < 0)) {
         perror("sendto failed"); 
         return; 
    }
}

Message received_message() {

    Message message;
    char buffer[sizeof(message)];
    int recvlen;
    int clientLen = sizeof(udpClientSocket);

    recvlen = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&udpClientSocket, &clientLen); 
    //recvlen = recvfrom(sockaddr, buffer, sizeof(buffer), 0, (struct sockaddr *)&remaddr, &addrlen); 
    printf("received %d bytes\n", recvlen); 
    if (recvlen > 0) { 
        memcpy(&message, buffer, sizeof(message));
    }
    return message;
}
 
