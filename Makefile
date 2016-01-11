#CPP is g++ compiler
C = gcc

#g++ compiler options
#	-c prevents linking
#	-std=c++11 allows <unordered_set> to be used
#	-I . specifies header file locations
CFLAGS = -c -std=c11
HDRLOC = -I .

#make targets
all: simpsh

simpsh: main.o
	$(C) main.o -o simpsh

main.o: main.c
	$(C) $(CFLAGS) main.c $(HDRLOC)
	
clean:
	rm *.o simpsh
