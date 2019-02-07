/**
 * Client application executed to perform the connect to an ftp remote server
 *
 * The current client function will receive as input two strings, representing
 * the server address and the port number of the server, and will perform a connect
 * to the server after all the proper setup. It will then execute the str_cli function,
 * that will take care of executing a new parser
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 04/17/2018
 * @return true if the program need just to close the connection,
 *          false, if we will need to close the whole program following a bye command,
 */
#include "prog5cli.h"
#include "wrap5cli.h"  //include wrapper functions


bool client ( char* arg1, char* arg2){
    //return value used to send information to the client
    int ret;
    //the current port is set as default as the default server port
    int server_port=SERV_PORT; //server port number
    //sockfd is the file descriptor for the socket
	int	sockfd;

    //Structure to hold the ip address,af family and port of the server
	struct sockaddr_in servaddr;

	if( arg2 ){ // if we have a port number as input use it, if not, use the default server port
 		server_port=atoi(arg2);
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
	if(Inet_pton( AF_INET, arg1, &servaddr.sin_addr )==-5){
        //exit but keep running the main console, if a conversion error happens
        return true;
    }

    //connect to the server
	if( (ret=Connect( sockfd, (SA *) &servaddr, sizeof(servaddr)) ) == -5 ){
        //return true if the connect fails, as we want to return to the main
        //parser, wuthout quitting the whole application
        Close(sockfd);
        return true;
    }
    printf("Connection with %s successful\n",arg1);
    //Infinite loop on standard input that parse all the commands received
    // from input. The loop ends when an end of file is found. In our
    //case, with standard input will be when CTRL+D is pressed on the keyboard.
    return str_cli(sockfd, arg1);
    //close the socket
//    Close( sockfd );
//	return(0);
}


/**
 * Read from standart input,parse the commands received, execute them and then
 * write the data on the socket and then wait to receive a response from the server.
 *
 * This function will take in input a file descriptor to a socket and a string containing the
 * address of the ftp server An Fgets is then executed on the standard input to
 * to read a line , the information is parsed and then sent to the  the server. The next
 * operation will be a read on the socket to read back the response from the
 * server.
 *
 * Usage: str_cli(int <socket_file_descriptor>,
 *                char* <server address>)
 *
 */
bool str_cli(int sockfd, char* saddr){
    //arrays of chars to send and receive information
    char sendline[MAXLINE], recvline[MAXLINE];
    //print the ftp prompt
    Fputs("ftp> ",stdout);
    //loop over standard input to receive commands
    while( Fgets(sendline,MAXLINE,stdin) != NULL){
        //reset the strings at each iteration, so we don't have problem
        //of residual memory
        char command[MAXLINE]="\0";
        char arg1[MAXLINE]="\0";
        char arg2[MAXLINE]="\0";

        //get the command id of the command received
        cmd_id flag=get_args(sendline,command,arg1,arg2);

        //choose a statement accordingly to the command receiver
        switch (flag){
            case NEG_:  //invalid command
                Fputs("?Invalid command ",stdout);
                Fputs(command,stdout);
                Fputs("\n",stdout);
                break;
            case ZERO_:  //no command received
                Fputs("ftp> ",stdout);
                continue;
            case HELP_: ;  //help and ? do the same thing, so they can be one case together
            case QM_:
                help(arg1);
                break;
            case QUIT_: ;  //quit and bye do the same thing, so they can be one case together
            case BYE_:
                //close the cocket
                Close(sockfd);
                Fputs("Goodbye!\n",stdout);
                //return false, as we want to quit the whole application
                return false;
            case CDUP_ : //change remote directory to father, will fallthrough in the CD_ command case
                strcpy(arg1,"../\n\0");
                __attribute__ ((fallthrough));
            case CD_:  //change remote directory to the one in input
                cd(arg1,sockfd);
                break;
            case CLOSE_: ;  //close and disconnect do the same thing, so they can be one case together
            case DISCONNECT_:
                //close the socket
                close(sockfd);
                //print a message to screen
                printf("Disconnected\n");
                //return true, as we don't want to quit the whole application
                return true;
                //break;
            case LCD_: //change local directory
                cd_local(arg1);
                break;
            case OPEN_:;
                //print a message, as we are already connected
                printf("Already connected to %s, use close first.\n",saddr);
                break;
            case PWD_:
                //ask to the server about his current working directory
                Writen(sockfd, sendline, strlen(sendline) );
                //receive the information
                Readline(sockfd,recvline,MAXLINE);
                //print the information on screen
                Fputs(recvline,stdout);
                break;
        }
        //print the ftp command prompt for each command
        Fputs("ftp> ",stdout);

    }
    //if we use ctrl+d, fgets receives an EOF, and so we want to completely close the program
    Close(sockfd);
    return false;
}
