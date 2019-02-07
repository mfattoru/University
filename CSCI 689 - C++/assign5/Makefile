CC = g++
CCFLAGS = -g -Wall -Werror

assign5: String.o assign5.o
	$(CC) $(CCFLAGS) -o assign5 assign5.o String.o

assign5.o : assign5.cc
	$(CC) $(CCFLAGS) -c -o assign5.o assign5.cc

# assign5 : String.o
# 	$(CC) $(CCFLAGS) -o String  String.o

String.o : String.cc String.h
	$(CC) $(CCFLAGS) -c -o String.o String.cc


clean:
	-rm *.o assign5
