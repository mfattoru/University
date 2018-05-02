/**
 * Client application to request the daytime to a server on the network
 *
 * The current application receives in imput the ip address of a server, and
 * create a tcp ip connection to connect to a server on the port 13 (defined
 * by the variable SERVER_PORT). Port 13 is the default port for daytime servers.
 *
 * Usage: <programName> <IP Address>
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 01/28/2018
 * @return 0 if the programi is Successful, 1 for wrong imputs,
 */
#include "prog1cli.h"
#include "wrap1cli.h"

//Initialize the array to zeros,all the errors will not be skipped
int SKIP_ERROR[NUM_OF_FUNCTIONS] = { };

int main( int argc, char **argv ){
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
	if ( argc != 2 ){
        fprintf( stderr,"usage: %s <IPaddress>\n", argv[0] );
        //Exit if the program doesn't have the proper number of parameters
        exit(1);
    }
    //Declare a socket
	sockfd = Socket( AF_INET, SOCK_STREAM, 0 );

    //Clean the structure from garbage bites in the memory
	bzero( &servaddr, sizeof( servaddr ) );
    //server address family on ipv4
	servaddr.sin_family = AF_INET;
    //server port
	servaddr.sin_port = htons( SERVER_PORT );

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
