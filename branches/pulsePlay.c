
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

#include "udp.h"

Message receivedMessage;

void playback(int isRecord)
{
	static pa_sample_spec ss;

	if (isRecord) {
		ss.format = PA_SAMPLE_S16LE;
		ss.rate = 44100;
		ss.channels = 2;
	} else {
		ss.format =  PA_SAMPLE_ULAW;
		ss.rate = 8000;
		ss.channels = 1;
	}	

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
		uint8_t buf[BUFSIZE];
		ssize_t r;
#if 0
		pa_usec_t latency;
		if ((latency = pa_simple_get_latency(s, &error)) == (pa_usec_t) -1) {
			fprintf(stderr, __FILE__": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
			goto finish;
		}
		fprintf(stderr, "%0.0f usec \r", (float)latency);
#endif
		/* Read some data ... */
		/* if ((r = read(STDIN_FILENO, buf, sizeof(buf))) <= 0) {
		   if (r == 0) 
		   break;
		   fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
		   goto finish;
		   }*/

		//read data udpi
		/*if((r=recvfrom(sockfd,buf,BUFSIZE,0,NULL,NULL)) <= 0) {
		  if (r == 0) 
		  break;
		  fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
		  printf("r=%d\n",r);
		  goto finish;
		  }*/

		receivedMessage = received_message();

		memcpy(buf, receivedMessage.data, BUFSIZE);	

		//recvline[n]=0;
		printf("total byte read %d\n",r);
		/* ... and play it */
		if (pa_simple_write(s, buf, (size_t) r, &error) < 0) {
			fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
			goto finish;
		}
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
	return ret;

}


int main(int argc, char* argv[]) {
	char *host;
	char *port;
	host = argv[1];

	int isRecord = 1;

	if(strcmp(argv[1],"-f")) {
		isRecord = 0;
	} 
	if(strcmp(argv[1],"-r")) {
		isRecord = 1;
	}

	//host + port
	init_udp_socket(argv[2],atoi(argv[3]));
	
	playback(isRecord);

	/*    Message message;
	      strcpy(message.data,"hello");

	      init_udp_socket(argv[1],atoi(argv[2]));
	      while(1) {
	      send_message(message);
	      }
	 */  
}

