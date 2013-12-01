#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cv.h>
#include <highgui.h>
#include <sys/types.h>
#define UDP_PORT 8888
#define SIZE 128
#define RECEIVE_ADDR "172.19.0.15"
#define MAX_PACK_SIZE 65000
#define MAX_BUFFER_SIZE 100000



//Decoder des donnees recoits
cv::Mat decode(std::vector<uchar> buf){
    cv::Mat image_frame;
    
    //uchar* frame_data;  
    image_frame=cv::imdecode(buf,1);
    return image_frame;
}

int main(int argc, char** argv)
{
	cv::Mat img;
	cv::Mat imgResize;
	char* 	  server_ip;
	struct sockaddr_in server;
	int	width, height, key;
	int     sock, length, fromlen, n;
	// Creer le socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0) printf("error opening socket");
	length = sizeof(server);
	bzero(&server,length);
	server.sin_family=AF_INET;
        server.sin_addr.s_addr=INADDR_ANY;
    	server.sin_port=htons(UDP_PORT);
	// Attendre
        if (bind(sock,(struct sockaddr *)&server,length)<0) printf("error binding");
        fromlen = sizeof(struct sockaddr_in);
	printf("Press 'q' to quit\n");
	cvNamedWindow("stream_client", CV_WINDOW_AUTOSIZE);
	while(key != 'q') {
                uchar data[MAX_BUFFER_SIZE];
                int data_length;
                data_length = recvfrom(sock,data,MAX_BUFFER_SIZE,0,(struct sockaddr *)&server,(socklen_t*)&fromlen);
                std::vector<uchar> encode_data(data, data + data_length);
                img = decode(encode_data);
                if (img.empty()) printf("Decode failed");
		cv::resize(img,imgResize,cv::Size(0,0),4,4);
             	imshow("stream_client", imgResize);
		key = cvWaitKey(30);
	
	}
	/* free memory */
	cvDestroyWindow("stream_client");
	return 0;

}





