/**
 * Server application to run a server able to reply to ftp commands received from the user
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
 * @version 1.0 04/17/2018
 * @return 0 if the program is Successful
 */
#include "prog5srv.h"
#include "wrap5srv.h"

//Initialize the array to zeros,all the errors will not be skipped
int SKIP_ERROR[NUM_OF_FUNCTIONS] = { };
//Initialize the array cmds, containing the list of all the available commands.
const char* cmds[ ]={ "", "?", "bye", "cd", "cdup", "close", "disconnect", "help", "lcd", "open", "pwd", "quit" };



int main(int argc, char **argv){
    //variable to store the process identification number for the generated child
    pid_t child_pid;
    //Listening socket, connection socket and port number
    int listenfd,connfd,port_number=SERV_PORT;
    //structure to hold the address: IP/port number
    struct sockaddr_in serveraddr;

    //check if the number of argument passes in input is correct
    if ( argc > 2 ){
        fprintf( stderr,"usage: %s [Port Number]\n", argv[0] );
        //Exit if the program doesn't have the proper parameters
        exit(1);
    }
    //Function used to accept the SIGCHLD signal sent from the child to the father.
    //this signal is sent every time a child terminate it's execution.
    Signal(SIGCHLD, handler);

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
        connfd = Accept(listenfd, (SA *) NULL,NULL);

        //Fork the process,so to delegate the computational side of the search to
        // a client, while the father focuses on listening for incoming connections
        //pid == 0 represent the child process just forked
        if ( ( child_pid = Fork() ) == 0){ //If i'm a child do this
            //close the listening socket as the child doesn't need to be listening
            //for new client requesting to connect.
            Close(listenfd);

            //lunch the function to search for the book in the database
            receive_command(connfd);

            //close the connection file descriptor, as we are done with the
            //connection with the client
            Close(connfd);
            //Exit with a successful state
            exit(0);
        }
        //print a statement to log with what PID value the child has been created

        //close the connection
        Close(connfd);
    }
    //close the listening socket
    Close(listenfd);
    return 0;
}


/**
 * handler function that gets called by the signal function once a SIGCHLD is
 * received.
 *
 * This function receives as input an integerm representing the signalnumber, and
 * calls the Waitpid function to wait for the children in order to remove any
 * zombie process left in the system.
 *
 * Usage: Fgets(int <signal number> )
 *
 */
void handler(int sig){
    pid_t pid;
    int child_status;
    //remove the warning of unused variable
    UNUSED(sig);
    //check if there's at least one  child processes terminated,if so clal the waitpid
    //function and cleat the zombie processes left in the system.
    pid=Waitpid(-1,&child_status,WNOHANG);
    printf("Child %d terminated with exit status %d\n",pid, WEXITSTATUS(child_status));
}

/**
 * Loop over the requests from the client and send back the response.
 *
 * This function will take as input a file descriptor, representing the connected socket,
 * and will interpret the commands received from the user
 *
 * Usage: receive_command( int <socket file descriptor> )
 *
 */
void receive_command(int sockfd){
    //variable used to store the strings received by the client and the string
    //returned by the search of the book and then to be sent back to the client
    char recvline[MAXLINE];

    //loop over all the input received
    while(Readline(sockfd,recvline,MAXLINE) ){
        menu(recvline,sockfd);
    }
}