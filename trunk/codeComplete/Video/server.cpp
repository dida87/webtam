#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <cv.h>
#include <highgui.h>
#include<vector>
#define UDP_PORT 8888





/* Encoder l'image avant de tranmettre au recepteur
   Entre : le frame qui est capturé par le web cam
   Sorti : une buffe encode sous form jpg.
*/
std::vector<unsigned char> encode(cv::Mat frame){
     int b;
     std::vector<unsigned char> buf;
     std::vector<int> params(1, 95);
     b= cv::imencode(".jpg",frame,buf,params);
     return buf;
    
}

int main(int argc, char** argv)
{
	int key;
	struct sockaddr_in server;
	int sock, length, n;
	struct hostent *host_address;
	sock= socket(AF_INET, SOCK_DGRAM, 0);
   	if (sock < 0) printf("socket error");
	server.sin_family = AF_INET;
	if(argc!=2){
	printf("Utilisation ./emetteur <adress du recepteur>\n");
	}
	else
	{
	host_address = gethostbyname(argv[1]);
	server.sin_port = htons(UDP_PORT);
	if (host_address==0) printf("Unknown host");

  	 bcopy((char *)host_address->h_addr, (char *)&server.sin_addr, host_address->h_length);
	
	//Initialisation du capteur

	cv::VideoCapture cap(0);
	cv::Mat frame;
	cv::Mat frame1;
	
	cvNamedWindow("stream_server", CV_WINDOW_AUTOSIZE);
	printf("Press 'q' to quit \n");
	while(key != 'q') {
		//Capturer le frame de webcam
		cap >> frame;
		cv::resize(frame,frame1,cv::Size(0,0),0.25,0.25);
			
		//Encoder le frame avant d'envoyer

                std::vector<unsigned char> encode_data;
		encode_data=encode(frame1);
		int data_len = encode_data.size();
	        uchar data[data_len];
		for (int i = 0; i < data_len; ++i) {
			data[i] = encode_data[i];
	        }
		
		//Envoyer au recepteur
		n=sendto(sock,data,data_len,0,(struct sockaddr*)&server,sizeof(server));
		
		//Afficher a l'ecran
		cv::imshow("stream_server",frame);

		//delais 30 milisecond
		key = cvWaitKey(40);
	}

	
 	
	/* free memory */
	cvDestroyWindow("stream_server");
	}
	//quit(NULL, 0);
	return 0;
}






