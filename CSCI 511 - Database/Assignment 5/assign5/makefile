CC = g++
CCFLAGS = -Wall -O

all: queryMaker databaseLoader

databaseLoader : databaseLoader.o
	$(CC) -o databaseLoader $(CCFLAGS) -Werror databaseLoader.o -lpq
databaseLoader.o :
	$(CC) $(CCFLAGS) -c -Werror databaseLoader.cc

queryMaker : queryMaker.o
	$(CC) -o queryMaker $(CCFLAGS) -Werror queryMaker.o -lpq
queryMaker.o :
	$(CC) $(CCFLAGS) -c -Werror queryMaker.cc
clean :
	-rm *.o databaseLoader queryMaker
