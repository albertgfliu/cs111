#CPP is g++ compiler
C = gcc

#gcc compiler options
#	-c prevents linking
#	-std=c++11 allows <unordered_set> to be used
#	-I . specifies header file locations
CFLAGS = -c -std=c99
HDRLOC = -I .

#make targets
all: simpsh

simpsh: main.o
	$(C) main.o -o simpsh

main.o: main.c
	$(C) $(CFLAGS) main.c $(HDRLOC)
	
clean:
	rm *.o simpsh *.tar.gz *~

check:
	./test.sh

dist:
	make check
	mkdir lab1-albertliu-zixuanfan
	cp main.c Makefile README.md test.sh ./lab1-albertliu-zixuanfan
	tar -cvf lab1-albertliu-zixuanfan.tar.gz ./lab1-albertliu-zixuanfan
	rm -rf lab1-albertliu-zixuanfan
	echo "make dist successful"
