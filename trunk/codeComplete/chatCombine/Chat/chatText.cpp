#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include<arpa/inet.h>

#include "chatText.h"

int sockfd=-1,n;
struct sockaddr_in textServAddrSend,cliaddr;
socklen_t len;
char mesg[1000];

#define BUFSIZE 1024
#define UDP_PORT 32000


void init_socket(const char* host, int port)
{
    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&textServAddrSend,sizeof(textServAddrSend));
    textServAddrSend.sin_family = AF_INET;
    textServAddrSend.sin_addr.s_addr=inet_addr(host);
    textServAddrSend.sin_port=htons(port);
    printf("socket is ready at port %s and %d",host, port);

}

void send_text(char buf[])
{
    if(sockfd == -1)
        initSocketToChatText();

        printf("1");
        if(buf)
        if(strlen(buf)>0)
        {
            n = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&textServAddrSend,sizeof(textServAddrSend));
        }
        printf("2");
        //bzero(&buf,sizeof(buf));
        //sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
        printf("3");
}


char *hostToSendText = "192.168.1.100";
int portToSendText = 8885;
//int main(int argc, char**argv)
void initSocketToChatText()
{
    char *host;
    int port;

    host = hostToSendText;
    port = portToSendText;

    init_socket(host, port);
    //printf("init socket to send text");
}
