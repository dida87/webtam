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



int record_and_send()
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

	uint8_t buf[BUFSIZE];

	for (;;) {
		/* Record some data ... */
		if (len=pa_simple_read(s, buf, sizeof(buf), &error) < 0) {
			fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", 
					pa_strerror(error));
			goto finish;
		}
	printf("len=%d\n",len);
		// sent to server
	sleep(100);
	sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
	}

	ret = 0;

finish:
	if (s)
		pa_simple_free(s);

	return ret;
}

void init_socket(const char* host)
{
	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(host);
	servaddr.sin_port=htons(32000);
}

void read_file_and_send()
{
	FILE *f = fopen("test.au","r");
	if(f==NULL){
		fprintf(stderr,"read file error");
		puts("read file error");
		return;                       
	}
	while(!feof(f))
	{
		uint8_t buf[BUFSIZE];
		ssize_t r;

		int byte_read = fread(buf,1,BUFSIZE,f);
		if(byte_read > 0)
		{
			n = sendto(sockfd,buf,byte_read,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
			printf("read byte = %d byte sent %d\n", byte_read,n);
		}
	}


}

int main(int argc, char**argv)
{

	init_socket(argv[1]);
	read_file_and_send();
	record_and_send();
}

