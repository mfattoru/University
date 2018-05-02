all: clean client server
	
client :
	gcc -Wall -Wextra prog3cli.c wrap3cli.c in-out.c -o client

server :
	gcc -Wall -Wextra prog3srv.c wrap3srv.c in-out.c -o server

clean :
	-rm client server
