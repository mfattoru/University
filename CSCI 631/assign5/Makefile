all: clean client server


test :
	gcc -Wall -Wextra prog5ftp.c wrap5cli.c util5cli.c in-out.c prog5cli.c -o test


client : client-util.o
	gcc -Wall -Wextra prog5cli.c wrap5cli.c in-out.c client-util.o -o client

server : #server-util.o
	gcc -Wall -Wextra prog5srv.c wrap5srv.c in-out.c util5srv.c -o server

# client-util.o:
# 	gcc -c -Wall -Wextra util5cli.c wrap5cli.c -o client-util

# server-util.o:
# 	gcc -c -Wall -Wextra util5srv.c -o server-util
clean :
	-rm client server test
