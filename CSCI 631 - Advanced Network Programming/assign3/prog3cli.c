/**
 * Client application to search the author of a book
 *
 * The current application receives in input the ip address of a server, and
 * optionally the port number and create a tcp ip connection to connect to
 * a server on the port received in input, or no the default port defined by
 * the variable DEFAULT_PORT. Port 9880 is the default port for daytime servers
 *
 * Usage: <programName> <IP Address> [Port Number]
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/06/2018
 * @return 0 if the program is Successful, 1 for wrong imputs,
 */
#include "prog3cli.h"
#include "wrap3cli.h"

//Initialize the array to zeros,all the errors will not be skipped
int SKIP_ERROR[NUM_OF_FUNCTIONS] = { };

int main( int argc, char **argv ){
    int server_port=SERV_PORT; //server port number
    //sockfd is the file descriptor for the socket
	int	sockfd;

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

    //Infinite loop on standard inpit that get the information and send the
    //data to the server. The loop ends when an end of file is found. In our
    //case, with standard input will be when CTRL+D is pressed on the keyboard.
    str_cli(stdin, sockfd);

    //close the socket
    Close( sockfd );
	return(0);
}


/**
 * Read from standart input, write the data on the socket and then wait to receive
 * a response from the server.
 *
 * This function will take in input a file descriptor to a file, and a file
 * descriptor to a socket. An Fgets is then executed on the file file descriptor
 * to read a line , and the information is then sent to the  the server. The next
 * operation will be a read on the socket to read back the response from the
 * server. Once received the information, it's printed to standard output.
 *
 * Usage: str_cli(FILE* <file stream>,
 *                int <socket_file_descriptor>)
 *
 */
void str_cli(FILE *fp, int sockfd){
    char sendline[MAXLINE], recvline[MAXLINE];
    //printf("What string do you want to search in the database? ")
    while( Fgets(sendline,MAXLINE,fp) != NULL){
        //write line read from stdin to the socket
        Writen(sockfd, sendline, strlen(sendline) );
        //read the server responsefrom the socket
        Readline(sockfd,recvline,MAXLINE);
        //Prints out the information received
        Fputs("Author: ", stdout);
        Fputs(recvline, stdout);
    }
}
