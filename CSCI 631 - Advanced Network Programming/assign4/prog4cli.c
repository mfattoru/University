/**
 * Client application to perform computation on a sequence of numbers.
 * The client sends a sequence of numbers to the server, and receives back the
 * sum of those numbers with a specific formula applied.
 *
 * The current application receives in input the ip address of a server, and
 * optionally the port number and create a tcp ip connection to connect to
 * a server on the port received in input, or no the default port defined by
 * the variable DEFAULT_PORT. Port 9880 is the default port for daytime servers
 *
 * Usage: <programName> <IP Address> [Port Number]
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/30/2018
 * @return 0 if the program is Successful, 1 for wrong inputs.
 */
#include "prog4cli.h"
#include "wrap4cli.h"

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
 * Read from standard input, write the data on the socket and then wait to receive
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
    //Structure used to perform checks on the file descriptors that are ready to be processed
    fd_set rset;
    //variables to be used to save the file descriptor and the maximum value of file descriptor
    int fd, maxfdp1;
    //bolean value to check if the user has finished inserting value in the stdin
    //or if the server terminated prematurely.
    bool stdineof=false;
    //variables containing the line to send and to receive
    char sendline[MAXLINE], recvline[MAXLINE];

    //set to zero all the bit of rset
    FD_ZERO(&rset);
    //converts file pointer to file descriptor
    fd = fileno(fp);
    //find the biggest file descriptor
    maxfdp1 = max(fd,sockfd) +1;

    //infinite loop to parse all the data that will be received in input from the client.
    //It will be possible for the user to stop inserting data, by using the keyboard
    //combination ctrl + d
    while(true){
        //If we didn't previously received the end of file from the stream (ctrl + d)
        if( !stdineof ){
            //turn on the bit for the file descriptor received as input
            FD_SET( fd, &rset);
        }
        //turn on the bit for the socket file descriptor
        FD_SET(sockfd, &rset);
        //Launch the select function on rset, to see when at least one of the
        //file descriptor will be ready
        Select ( maxfdp1 , &rset ,0 ,0 ,0);

        //if the socket file descriptor is ready
        if( FD_ISSET( sockfd, &rset )){
            //read the content of the socket
            if ( Readline(sockfd, recvline, MAXLINE) == 0 ){
                //if the readline returns zero, it means that readline  had encountered
                //an EOF on the socket.
                //If we encountered an EOF, and stdineof is true, this means that the workflow
                //was executed correctly, so we can return
                if(stdineof){
                    return;
                }
                //if stdineof is false, it means that the connection was interrupted while
                //the client was still sending information. this means that the server
                //terminated prematurely.
                else{
                    fprintf( stderr, "ERROR: Server terminated prematurely\n");
                    exit(1);
                }
            }
            //print to standard output the received information
            Fputs( recvline, stdout);
        }

        //if the standard input file descriptor is ready
        if (FD_ISSET( fd, &rset )){
            //get the information from the standard input, and save them in sendline
            if( !Fgets(sendline, MAXLINE, fp)){
                //if Fgets returns NULL, then it means it received an EOF
                //we set stdineof to true to mark the received EOF from the user
                stdineof = true;
                //We close the half write socket, as we don't need to send any more
                //information to the server
                Shutdown(sockfd, SHUT_WR);
                //we clear the previously set bit in rset, so it can be used by another
                //socket
                FD_CLR(fd, &rset);
                //we continue the iteration, so we will skip the call to writen
                //we don't have anything to write to the socket
                continue;
            }
            //write the information read from standard input to the socket, to send
            //it to the server
            Writen(sockfd, sendline, strlen(sendline) );
        }
    }
}


/**
 * Receives two integer in input and returns the bigger number between the two
 *
 */
int max(int x, int y){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}