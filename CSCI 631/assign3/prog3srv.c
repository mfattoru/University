/**
 * Server application to run a server able to return the author of a book, by
 * receiving in input the title of the book.
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
 * @version 1.0 03/06/2018
 * @return 0 if the program is Successful
 */
#include "prog3srv.h"
#include "wrap3srv.h"

//Initialize the array to zeros,all the errors will not be skipped
int SKIP_ERROR[NUM_OF_FUNCTIONS] = { };


int main(int argc, char **argv){
    //variable to store the process identification number for the generated child
    pid_t child_pid;
    //Listening socket, connection socket and port number
    int listenfd,connfd,port_number=SERV_PORT;
    //structure to hold the address: IP/port number
    struct sockaddr_in serveraddr;
    //file descriptor for the database containing the data regatding the association
    //book name - author
    FILE* database;

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

    //opening database ad read only file
    database = Fopen(DB_PATH,"r");

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
            search_book(connfd, database);

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
  pid = Waitpid(-1,&child_status,WNOHANG);
  printf("Child %d terminated with exit status %d\n",pid, WEXITSTATUS(child_status));
}

/**
 * Loop over the requests from the client and send back the response. This function
 * actually call another function find_author, to actually make the comparison
 * from the received line, with the content of the database
 *
 * This function will take as input a pointer to a a socket file descriptor, that
 * in this case will be the socket to communicate with the client, and a file
 * descriptor to the database
 *
 * Usage: search_book( int <socket file descriptor>,
 *                     FILE * <database file description>)
 *
 */
void search_book(int sockfd, FILE *db){
    //variable used to store the strings received by the client and the string
    //returned by the search of the book and then to be sent back to the client
    char *sendline, recvline[MAXLINE]={};

    while(Readline(sockfd,recvline,MAXLINE) ){
        //Function to return the author of the book received from the client
        sendline=find_author(db,recvline);
        //write the found string to the socket, to send it to the client
        Writen(sockfd, sendline, strlen(sendline) );
    }
}


/**
 * Loop over the content of the database until it finds a book that matches the
 * title received in input from the client
 *
 * This function will take as input a pointer to a file descriptor, representing
 * the connection with the database, and a string, containing the string received
 * in input from the client.
 * The function will read line by line the content of the file and separate the
 * two fields by name of the book and author. The name of the book then is compared
 * with the string received in input by the client and if the string are the same,
 * then the author is returned by the function. If the book isn't found, then
 * Unknown is returned to the client.
 *
 * Usage: find_author(FILE * <database file description>,
 *                    char* <name of the book>)
 *
 *
 */
char* find_author(FILE *db,char* recvline){
    char buf[MAXLINE];      //buffer to save the line read from the file

    //variables declared as static, as they will be returned by the function,
    //so we need theyr memory location to be accessible even after the function
    //ended. I could have used a malloc to allocate dynamic memory in the heap,
    //but this is a prettier solution, and have the same final result.
    //it onl allocates MAXLINE memory no matter how big is the string to be saved.
    static char book[MAXLINE];  //variable used to contain the name of the book
    static char author[MAXLINE];  //variable used to contain the name of the author

    //loop over all the lines in the database
    while ( Fgets(buf,MAXLINE,db) != NULL ){

        //Parse the string read from the file
        sscanf(buf,"%[^:]:%[^:]",book,author);

        //add a newline to the book, as the fgets used in the client side keeps
        //the newline attached to the string
        strcat(book,"\n");

        //compare the name of the book read from the database with the string received
        //from the user (NOT case sensitive)
        if (strcasecmp(book,recvline) == 0 ){
            //if we found the book, bring the file position indicator at the beginning
            //of the file, and return the author
            Fseek(db, 0, SEEK_SET);
            //add a newline at the end of the string
            strcat(author,"\n");
            return author;
        }
    }
    //if after scanning the whole database we haven't found any book, bring the file
    //position indicator at the beginning of the file, and return the string "Unknown"
    //with a newline and a null terminator character
    Fseek(db, 0, SEEK_SET);
    return "Unknown\n\0";
}
