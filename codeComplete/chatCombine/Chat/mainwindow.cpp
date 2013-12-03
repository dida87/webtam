#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatText.h"
#include "chatVideo.h"
#include "stdio.h"

#include <QThread>
#include <QFuture>
#include <QtCore>

#define BUFFSIZE 1024

void onTextReceived(MainWindow* mainWindow)
{
    char buf[BUFFSIZE];
    while(1)
    {
    //read data udp
    int r;
    if((r=recvfrom(mainWindow->sockfdReceivedText,buf,BUFFSIZE,0,NULL,NULL)) <= 0) {
        //	printf("r=%d\n",r);
    } else {
        if(strlen(buf)){
            printf("in my thread %s\n", buf);
            mainWindow->ui->textEdit->append(buf);
//            w->ui->textEdit->append(buf);
        }
    }
    bzero(&buf, BUFFSIZE);
    }
}

void startThreadSendAudio(MainWindow* mainWindows)
{
    /* The sample type to use */
        static const pa_sample_spec ss = {
            .format = PA_SAMPLE_S16LE,
            .rate = 44100,
            .channels = 2
        };

        pa_simple *s = NULL;
        int ret = 1;
        int error;

        /* Create the recording stream */
        if (!(s = pa_simple_new(NULL, "record_and_play", PA_STREAM_RECORD,
                        NULL, "record", &ss, NULL, NULL, &error))) {
            fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
            goto finish;
        }

        uint8_t buf[BUFFSIZE];
        int len;

        bzero(&buf,sizeof(buf));
        for (;;) {
            /* Record some data ... */
            if (len=pa_simple_read(s, buf, sizeof(buf), &error) < 0) {
                fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n",
                        pa_strerror(error));
                goto finish;
            }


        printf("len=%d  \n",len);
            // sent to server
        int nbSent = 0;
        nbSent = sendto(mainWindows->sockfdSendAudio,buf,sizeof(buf),0,(struct sockaddr *)&(mainWindows->servaddrSendAudio),sizeof(mainWindows->servaddrSendAudio));
        printf("audio send to %d\n", nbSent);
        }

        ret = 0;

    finish:
        if (s)
            pa_simple_free(s);

        return ;
}

void startThreadReceivedAudio (MainWindow* mainWindows)
{
    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = 44100;
    ss.channels = 2;

    pa_simple *s = NULL;
    int ret = 1;
    int error;

    /* Create a new playback stream */
    if (!(s = pa_simple_new(NULL, "play_recording", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        printf("cat not open stream");
        goto finish;
    }


    for (;;) {
        uint8_t buf[BUFFSIZE];
        ssize_t r;
#if 0
        pa_usec_t latency;
        if ((latency = pa_simple_get_latency(s, &error)) == (pa_usec_t) -1) {
            fprintf(stderr, __FILE__": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
            goto finish;
        }
        fprintf(stderr, "%0.0f usec \r", (float)latency);
#endif

        //read data udp
        if((r=recvfrom(mainWindows->sockfdReceivedAudio,buf,BUFFSIZE,0,NULL,NULL)) <= 0) {
            if (r == 0)
                break;
            fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
            printf("r=%d\n",r);
            goto finish;
        }

        /* ... and play it */
        if (pa_simple_write(s, buf, (size_t) r, &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
            goto finish;
        }
        bzero(&buf, sizeof(buf));
    }

    /* Make sure that every single sample was played */
    if (pa_simple_drain(s, &error) < 0) {
        fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));
        goto finish;
    }
    ret = 0;
finish:
    if (s)
        pa_simple_free(s);
    return ;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initSocketToChatText();

    ui->setupUi(this);
    initSocket();


    QFuture<void> futureReceivedText = QtConcurrent::run(onTextReceived, this);
    qDebug() << "start thread to received tex" << QThread::currentThread();
    QFuture<void> futureSendAudio = QtConcurrent::run(startThreadSendAudio, this);
    qDebug() << "start thread to send Audio" << QThread::currentThread();
    QFuture<void> futureReceivedAudio = QtConcurrent::run(startThreadReceivedAudio, this);
    qDebug() << "start thread to Received" << QThread::currentThread();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{

//    printf("hello");
//    char *str;
//    QByteArray ba;
//    ba = ui->lineEdit->text().toLatin1();
//    str = ba.data();
//    puts(str);

//    char buf[1024];
//    int i;

//    for(i = 0; i< strlen(str); i++)
//        buf[i] = str[i];
//    buf[i] = '\0';
//    printf("buf copy %s\n",buf);
//    send_text(buf);
    streamTextServer();
}

void MainWindow::on_pushButton_clicked()
{
    chatVideo();
}

void MainWindow::initSocket()
{
    ipAddressDestination="172.19.0.118";

    portSendText =  32000;
    portSendAudio=  33000;
//    portSendVideo=  34000;
    portSendVideo=  8888;

    portReceivedText=32100;
    portReceivedAudio=33100;
    portReceivedVideo=34100;
//Received
//1. Text
    sockfdReceivedText=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddrReceivedText,sizeof(servaddrReceivedText));
    servaddrReceivedText.sin_family = AF_INET;
    servaddrReceivedText.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddrReceivedText.sin_port=htons(portReceivedText);

    bind(sockfdReceivedText,(struct sockaddr *)&servaddrReceivedText,sizeof(servaddrReceivedText));
//2. Audio
    sockfdReceivedAudio=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddrReceivedAudio,sizeof(servaddrReceivedAudio));
    servaddrReceivedAudio.sin_family = AF_INET;
    servaddrReceivedAudio.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddrReceivedAudio.sin_port=htons(portReceivedAudio);

    bind(sockfdReceivedAudio,(struct sockaddr *)&servaddrReceivedAudio,sizeof(servaddrReceivedAudio));
//3. Video
    sockfdReceivedVideo=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddrReceivedVideo,sizeof(servaddrReceivedVideo));
    servaddrReceivedVideo.sin_family = AF_INET;
    servaddrReceivedVideo.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddrReceivedVideo.sin_port=htons(portReceivedVideo);

    bind(sockfdReceivedVideo,(struct sockaddr *)&servaddrReceivedVideo,sizeof(servaddrReceivedVideo));
//SEND
//1. text
    sockfdSendText=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddrSendText,sizeof(servaddrSendText));
    servaddrSendText.sin_family = AF_INET;
    servaddrSendText.sin_addr.s_addr=inet_addr(ipAddressDestination);
    servaddrSendText.sin_port=htons(portSendText);

//2.Audio
    sockfdSendAudio=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddrSendAudio,sizeof(servaddrSendAudio));
    servaddrSendAudio.sin_family = AF_INET;
    servaddrSendAudio.sin_addr.s_addr=inet_addr(ipAddressDestination);
    servaddrSendAudio.sin_port=htons(portSendAudio);

//2.Video
    sockfdSendVideo=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddrSendVideo,sizeof(servaddrSendVideo));
    servaddrSendVideo.sin_family = AF_INET;
    servaddrSendVideo.sin_addr.s_addr=inet_addr(ipAddressDestination);
    servaddrSendVideo.sin_port=htons(portSendVideo);
}

void MainWindow::streamTextServer()
{
        char buf[BUFFSIZE];
        int n;
        char *str;
        int i;

        QByteArray ba;
        ba = ui->lineEdit->text().toLatin1();
        str = ba.data();
        for(i = 0; i< strlen(str); i++)
            buf[i] = str[i];
        buf[i] = '\0';

        printf("buf copy %s\n",buf);

        if(buf)
        if(strlen(buf)>0)
        {
            n = sendto(sockfdSendText,buf,strlen(buf),0,(struct sockaddr *)&servaddrSendText,sizeof(servaddrSendText));
        }
        printf("\nnumber of bytes send = %d\n",n);
        printf("2");
        //bzero(&buf,sizeof(buf));
        //sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
        printf("3");
}


void MainWindow::streamTextClient()
{
    ui->textEdit->append("aaaaa\n");
}

void MainWindow::streamAudioServer()
{

}
void MainWindow::streamAudioClient()
{

}
