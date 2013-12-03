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

#include <QThread>
#include <QFuture>
 #include <QtCore>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chatText.h"


#define BUFSIZE 1024
#define UDP_PORT 32000


int textClientsockfd;
struct sockaddr_in servaddrReceivedText,textClientcliaddr;

char buf[BUFSIZE];

void init_socket_udp(int port)
{
	printf("Setup socket for listening...\n");

    textClientsockfd=socket(AF_INET,SOCK_DGRAM,0);


    bzero(&servaddrReceivedText,sizeof(servaddrReceivedText));
    servaddrReceivedText.sin_family = AF_INET;
    servaddrReceivedText.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddrReceivedText.sin_port=htons(port);

    bind(textClientsockfd,(struct sockaddr *)&servaddrReceivedText,sizeof(servaddrReceivedText));
	printf("Socket is ready to listen on port %d\n",port);
}


int receivedText()
{
    FILE *f;

    extern MainWindow *w;

    while(1)
    {
	//read data udp
	int r;
    if((r=recvfrom(textClientsockfd,buf,BUFSIZE,0,NULL,NULL)) <= 0) {
		//	printf("r=%d\n",r);
	} else { 
		if(strlen(buf)){
            printf("in my thread %s\n", buf);
            f=fopen("content.txt","a");
            fprintf(f,"%s",buf);
            fclose(f);

//            w->ui->textEdit->append(buf);
		}
	}
	bzero(&buf, BUFSIZE);
    }
}



//int main(int argc, char*argv[]) {
int init_to_received_text() {

    //std::thread threadReceivedText (receivedText);

//	char *host;
//	int port;

//    host="192.168.1.100";
//    port= 8885;

//	init_socket_udp(port);
//    QFuture<void> future = QtConcurrent::run(receivedText);

//    qDebug() << "hello from GUI thread " << QThread::currentThread();
    //future.waitForFinished();

    /*while(1) {
		receivedText();
    }*/
    //threadReceivedText.join();
}
