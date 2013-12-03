#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include<arpa/inet.h>


#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
//video
    void streamVideoServer();
    void streamVideoClient();
//Audio
    void streamAudioServer();
    void streamAudioClient();
//Text
    void streamTextServer();
    void streamTextClient();
//init socket
    void initSocket();
//sys

    static void updateTextBoard(char buf[]);

    void videoStreaming();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

public:
    char* ipAddressDestination;
    int portSendVideo;
    int portReceivedVideo;
    int portSendAudio;
    int portReceivedAudio;
    int portSendText;
    int portReceivedText;

    struct sockaddr_in servaddrReceivedText,servaddrSendText;
    struct sockaddr_in servaddrReceivedVideo,servaddrSendVideo;
    struct sockaddr_in servaddrReceivedAudio,servaddrSendAudio;

    int sockfdSendText, sockfdReceivedText;
    int sockfdSendAudio, sockfdReceivedAudio;
    int sockfdSendVideo, sockfdReceivedVideo;

    friend void onTextReceived();

public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
