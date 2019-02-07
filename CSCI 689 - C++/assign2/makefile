CC = g++
CCFLAGS = -Wall -O

assign2 : assign2.o
	$(CC) -o assign2 $(CCFLAGS) -Werror assign2.o
assign2.o :
	$(CC) $(CCFLAGS) -c -Werror assign2.cc

clean :
	-rm *.o assign2
