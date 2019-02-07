CC = g++
CCFLAGS = -g -Wall -Werror

assign4: assign4.o DataBlock.o
	$(CC) -o assign4 $(CCFLAGS) assign4.o DataBlock.o

assign4.o : assign4.cc assign4.h
	$(CC) -c -o assign4.o $(CCFLAGS) assign4.cc

DataBlock.o: DataBlock.cc
	$(CC) -c $(CCFLAGS) DataBlock.cc

clean :
	-rm -rf assign4 *.o
