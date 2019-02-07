all: clean client server
	
client :
	gcc -Wall -Wextra prog4cli.c wrap4cli.c in-out.c -o client

server :
	gcc -Wall -Wextra prog4srv.c wrap4srv.c in-out.c -lm -o server

clean :
	-rm client server
