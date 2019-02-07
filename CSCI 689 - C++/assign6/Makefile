CC = g++
CCFLAGS = -g -Wall -Werror

assign6: assign6.o
	$(CC) $(CCFLAGS) -o assign6 assign6.o

assign6.o : assign6.cc
	$(CC) $(CCFLAGS) -c -o assign6.o assign6.cc

clean:
	-rm *.o assign6
