/**
 * Server application to run a daytime server on the network.
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
 * @version 1.0 02/14/2018
 * @return 0 if the program is Successful
 */
#include "prog2srv.h"
#include "wrap2srv.h"

//Initialize the array to zeros,all the errors will not be skipped
int SKIP_ERROR[NUM_OF_FUNCTIONS] = { };


int main(int argc, char **argv){
    int listenfd,connfd,port_number=SERV_PORT;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    char buff[MAXLINE];
    char clientName[INET_ADDRSTRLEN]; //array of dimension of INET_ADDRSTRLEN
    uint client_len;
    time_t ticks; //store number of ticks from 01/01/1970 (to calculate date)
    FILE* output;

    if ( argc > 2 ){
        fprintf( stderr,"usage: %s [Port Number]\n", argv[0] );
        //Exit if the program doesn't have the proper parameters
        exit(1);
    }

    //Left this as example on how i could allow the program to skip the error,
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

    //listen for connection on the socket, with a aximum queue of LISTENQ
    //elements
    Listen(listenfd,LISTENQ);

    //endless loop waiting for a client to make a connect request
    while( true ){
        //accept a connection on the socket
        //client_len=sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *) NULL,NULL);

        /* Code if you want to make the server log the requests to the server/
        connfd = Accept(listenfd, (SA *) &clientaddr,&client_len);
        if( inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientName, sizeof(clientName) )!=NULL ){
            output = fopen("connections.log","a+");
            fprintf(output,"New connection from: %s:%d\n",clientName,ntohs(clientaddr.sin_port));
            fclose(output);
        } else {
            fprintf(output,"ERROR: Unable to get connected client address\n"); // i just fixed this to printf .. i had it as print before
        }
        */

        //returns  the  time  as  the  number of seconds since the Epoch,
        //1970-01-01 00:00:00 +0000 (UTC).
        ticks = time(NULL);
        //print on buffer the time converted in human readable format
        snprintf(buff,sizeof(buff), "%.24s\r\n", ctime(&ticks));
        //write the buffer on the socket
        Write(connfd,buff,strlen(buff));
        //close the connection
        Close(connfd);
    }

    return 0;
}
