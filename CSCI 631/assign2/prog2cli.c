/**
 * Client application to request the daytime to a server on the network
 *
 * The current application receives in input the ip address of a server, and
 * optionally the port number and create a tcp ip connection to connect to
 * a server on the port received in input, or no the default port defined by
 * the variable DEFAULT_PORT. Port 9880 is the default port for daytime servers
 *
 * Usage: <programName> <IP Address> [Port Number]
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/14/2018
 * @return 0 if the program is Successful, 1 for wrong imputs,
 */
#include "prog2cli.h"
#include "wrap2cli.h"

//Initialize the array to zeros,all the errors will not be skipped
int SKIP_ERROR[NUM_OF_FUNCTIONS] = { };

int main( int argc, char **argv ){
    int server_port=SERV_PORT;
	int	sockfd, n;
    //array to store the received daytime string
	char recvline[MAXLINE + 1];
    //Structure to hold the ip address,af family and port of the server
	struct sockaddr_in servaddr;

	//Left this as example on how i could allow the program to skip the error,
	//and continue the execution of the program in case of error of the wrapper
	//function. the syntax is:
	//			SKIP_ERROR[<name of function all capital letter>] = true.
	//E.g.  SKIP_ERROR[CONNECT]=true;

    //Check that the user gave as input at least an additional field beside the
    //program name, the additional field should be the IP address of the server
	if ( argc < 2 || argc > 3 ){
        fprintf( stderr,"usage: %s <IPaddress> [Port Number]\n", argv[0] );
        //Exit if the program doesn't have the proper number of parameters
        exit(1);
    }
	if( argv[2]){
 		server_port=atoi(argv[2]);
	}
    //printf("port number: %d\n",server_port); TODO remove

	//Declare a socket
	sockfd = Socket( AF_INET, SOCK_STREAM, 0 );

    //Clean the structure from garbage bites in the memory
	bzero( &servaddr, sizeof( servaddr ) );
    //server address family on ipv4
	servaddr.sin_family = AF_INET;
    //server port
	servaddr.sin_port = htons( server_port );

    //convert the address structure to binary form
	Inet_pton( AF_INET, argv[1], &servaddr.sin_addr );

    //connect to the server
	Connect( sockfd, (SA *) &servaddr, sizeof(servaddr));

    //Loop the read on the socket, Up to the point where there's nothing more
    //to read, and print it to the screen
	while ( ( n = Read( sockfd, recvline, MAXLINE ) ) > 0) {
		recvline[n] = 0;
		Fputs( recvline, stdout );
	}

    //close the socket
    Close( sockfd );
	return(0);
}
