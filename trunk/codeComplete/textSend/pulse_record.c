#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <pulse/simple.h>
#include <pulse/error.h>

#define BUFSIZE 1024
#define UDP_PORT 32000

int sockfd,n;
struct sockaddr_in servaddr,cliaddr;
socklen_t len;
char mesg[1000];




void init_socket(const char* host, int port)
{
	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(host);
	servaddr.sin_port=htons(port);
}

void send_text()
{
	while(1){
		char buf[BUFSIZE];
		//scanf("%s", &buf);
		fflush(stdin);
		gets(buf);
	//	buf[strlen(buf)]='\0';
		printf("input is %s",buf);
		if(strlen(buf)>0)
		{
			n = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
//			printf("\n %d byte sent\n",n);
		}
		//bzero(&buf,BUFSIZE);
	}


}

int main(int argc, char**argv)
{
	char *host;
	int port;
	host = argv[1];
	port=atoi(argv[2]);

	char text[BUFSIZE];

	init_socket(host, port);
	
	send_text();

}

