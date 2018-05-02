/**
 * Server application to run a server able to receive a sequence of numbers from
 * The client, and perform computation on them. The first number received from
 * input will be an exponent, and all the other numbers will be summed together
 * after having applied the power operator.
 *
 * The current application receives in input the port number and opens a
 * listening process accessible on the network through a tcp ip connection
 * on the port received in input, if the input is empty, the default port is
 * defined by the variable DEFAULT_PORT. Port 9880 is the default port for
 *  daytime servers
 *
 * Usage: <programName> [Port Number]
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/30/2018
 * @return 0 if the program is Successful
 */
#include "prog4srv.h"
#include "wrap4srv.h"

//Initialize the array to zeros,all the errors will not be skipped
int SKIP_ERROR[NUM_OF_FUNCTIONS] = { };


int main(int argc, char **argv){
    //variables to be used to handle the structure to contain the client file descriptor
    int i, maxi=-1, maxfd;
    //Listening socket, connection socket,accepted socket and port number
    int listenfd,connfd,sockfd,port_number=SERV_PORT;
    //number of file descriptors ready to be processed
    int nready;
    //Array of Client, used to hold the information about the file descriptor, sum total and flag to
    //recognize when is received an exponent or a value
    Client client[ FD_SETSIZE ];
    //structure to hold the address: IP/port number
    struct sockaddr_in serveraddr;

    //Structure used to perform checks on the file descriptors that are ready to be processed
    fd_set rset, allset;
    //string used to save the data read from the client
    char line [ MAXLINE ];

    //check if the number of argument passes in input is correct
    if ( argc > 2 ){
        fprintf( stderr,"usage: %s [Port Number]\n", argv[0] );
        //Exit if the program doesn't have the proper parameters
        exit(1);
    }

    //Left this as example on how I could allow the program to skip the error,
    //and continue the execution of the program in case of error of the wrapper
    //function. the syntax is:
    //			SKIP_ERROR[<name of function all capital letter>] = true.
    //E.g.  SKIP_ERROR[SOCKET]=true;

    //SKIP_ERROR[ACCEPT]=true; //skip the error if unable to accept the connection
    //SKIP_ERROR[WRITE]=true;  //skip the error if unable to write on socket

    //if a port number is received in input, use it as the port number to run
    // this application. Being received the input as a string, it needs to be
    //converted to an integer, and for that we use the function atoi of the
    //stdlib library, that converts a string to an integer.
    if (argv[1]){
        port_number=atoi(argv[1]);
    }

    //Declare a socket
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    //Clean the structure from garbage bites in the memory
    bzero(&serveraddr,sizeof(serveraddr));
    //server address family on ipv4
    serveraddr.sin_family = AF_INET;
    //Able to accept connections from any ip address
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //port number to open the service
    serveraddr.sin_port = htons(port_number);

    //bind the address to the socket
    Bind(listenfd,(SA *) &serveraddr,sizeof(serveraddr));


    //listen for connection on the socket, with a maximum queue of LISTENQ elements
    Listen(listenfd,LISTENQ);

    //set the maximum file descriptor as the listening socket
    maxfd = listenfd;
    //Initialize all the client array elements to -1 and all the flags to false
    for ( i = 0; i < FD_SETSIZE; i++ ){
        client[i].fd = -1;
        client[i].flag = false;
    }
    //set to zero all the bits of allset
    FD_ZERO( &allset );
    //set on the bit for the listening socket
    FD_SET( listenfd, &allset );

    //endless loop waiting for a client to make a connect request or to process his request
    while( true ){
        //align the two structures
        rset = allset;
        //wait for the file descriptors turned on in rset to be ready
        nready = Select ( maxfd + 1, &rset, NULL, NULL, NULL );

        //If the listening socket is ready
        if ( FD_ISSET ( listenfd, &rset ) ) {
            //Accept the connection
            connfd = Accept(listenfd, (SA *) NULL,NULL);

            //loop over the client array to find the first available position
            //A position is available when it's value is less than zero.
            //in our case we set it previously to -1.
            for ( i = 0; i < FD_SETSIZE && client[i].fd >= 0; i++ );

            //if the index returned is bigger than the max number of elements
            //print out an error and exit, if not, save the file descriptor in the structure
            if ( i < FD_SETSIZE ){
                client[i].fd = connfd;
            }
            else {
                fprintf ( stderr, "ERROR: Reached maximum number of allowed clients\n" );
                exit(1);
            }

            //turn on the bit for the accepted connection socket
            FD_SET ( connfd, &allset );
            //check and set the biggest file descriptor,used to execute the select
            if ( connfd > maxfd ){
                maxfd = connfd;
            }
            //check and select the biggest index in the client array structure
            if ( i > maxi ){
                maxi = i;
            }
            //as we handled the ready socket, decrease the number of ready by 1
            nready--;
        }

        //time to process the requests from the ready connected clients
        for ( i = 0; i <= maxi && nready > 0; i++ ) {
            //get the socket file descriptor of i-client
            sockfd = client[i].fd;
            //check if it's ready
            if ( sockfd >= 0 && FD_ISSET ( sockfd, &rset ) ) {
                //read from the socket. If the number of bites read from client
                //are zero, then it means that the client finished to send information
                //so we can send back the sum to the client
                if ( Readline ( sockfd, line, MAXLINE ) == 0 ){
                    //instantiate a string able to handle a the smallest and biggest double
                    char output[MAX_N_DIGITS];
                    //convert the double to a string, to handle possible conversion
                    //error during the network communication, in case of machines with different
                    //endianness
                    snprintf(output, MAX_N_DIGITS, "%f", client[i].sum);
                    //write the sum to the socket to send it to the client
                    Writen ( sockfd, output, sizeof(client[i].sum) );
                    //clear the bit in the structure
                    FD_CLR ( sockfd, &allset );
                    //reset the client element to -1 and false ( makes the location empty)
                    client[i].fd = -1;
                    client[i].flag=false;
                    //close the file descriptor
                    Close( sockfd );
                }
                else{
                    //use the received data to perform computation
                    sum_my_numbers(&client[i],line);
                }
                //we processed the file descriptor. decrease the number of file descriptors ready
                nready--;
            }
        }
    }
    //close the listening socket
    Close(listenfd);
    return 0;
}

/**
 *sum the numbers received from the client using the following formula:
 *    - First number is the exponent
 *    - Following numbers will be used to sum
 *the sum is performed as: sum = num1^exp + num2^exp .... +numN^exp;
 */
void sum_my_numbers(Client * cli, char* line) {
    //variable to temporarily save the converted string to double
    double tmp_var;

    //skip all the characters that are not digits. This condition handles the case
    //where the user accidentally insert a character in the number sent to the server.
    //This allows us to filter out the characters and receive just the number
    while(!isdigit(*line) && line[0]!='-'){
        line++;
    }

    //if flag is true, then we need to perform computation of this number
    if (cli->flag) {
        //convert the string to a double
        tmp_var=atof(line);
        //perform the exponential operation and add to the sum
        cli->sum += pow(tmp_var, cli->exp);

    }
    //if flag is false, then this is an exponent. we save the value as exponent
    else {//read exponent
        //convert the string to a double
        tmp_var = atof(line);
        //Set the sum as starting value zero
        cli->sum = 0;
        //set the exponent value
        cli->exp = tmp_var;
        //mark the structure as already set the exponent
        cli->flag = true;
    }
}
