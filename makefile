all: all.o
	gcc -Wall -o pPlay udp.o pulsePlay/pulsePlay.c
all.o:
	cd libs
	gcc -Wall -c libs/udp.c
clean: 
	rm *.o pPlay
