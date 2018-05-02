/**
 * Libary function, used to execute utility commands for the server
 *
 * The current source code, represent a parser for an ftp server.
 * Once the server receive a client, and opens a connection, it will have to handle
 * all the requested queries
 *
 * Usage: <programName>
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 04/17/2018
 * @return 0 if the program is Successful, 1 for wrong imputs,
 */


#include "util5srv.h"   //include the utilities header

/**
 * Change local directory
 *
 * This function will take in input a string, representing a path to a directory, and will try to
 * change the current directory, to the one specified. If no directory is received as input, the
 * function will consider the Home directory as the default one.
 *
 * The function will return to the client, the errno variable, representing the final status of the operation
 *
 * Usage: cd(char* <directory>)
 *
 */
void cd(char* directory,int sockfd) {
    //return variable to save the errornumber to send to the client
    char ret[MAXLINE];
    char buffer[MAXLINE];
    //reset the error number
    errno = 0;
    //expand possible ~ in the directory path
    wordexp_t exp_result;
    wordexp(directory, &exp_result, 0);
    //copy the value to the directory string
    strcpy(directory,exp_result.we_wordv[0]);
    //release the memory
    wordfree(&exp_result);
    //if the directory received as input is empty, then use the home directory ad destination folder
    if(strcmp(directory,"")==0) {
        directory=getenv("HOME");
    }
    //change directory
    chdir(directory);
    //get current working directory
    getcwd(buffer, sizeof(buffer));
    //return to the client the error number or he chdir
    //snprintf(ret,MAXLINE, "%d %s\n", errno,buffer);
    if(errno == 0) {
        snprintf(ret, MAXLINE, "%d %s\n", errno, buffer);
    }
    else{
        snprintf(ret, MAXLINE, "%d\n", errno);
    }
    Writen(sockfd,ret,strlen(ret));

}

/**
 * Find the command id
 *
 * This function will take in input a string, representing a command received from the user, and will search in the
 * available structures, for an equal command. If that specific command is found, then the function will return the
 * associated command id
 *
 * Usage: find_id(char* <command> )
 *
 */
cmd_id find_id ( char* command ){
    //initialize the default return value as incorrect commadn, in case we are not able to find it
    cmd_id flag = NEG_;
    //loop over all the available commands in cmds[]
    for(int i=0; i < NUM_OF_COMMANDS ; i++){
        //if we find a command that is equal
        if(strcmp(command,cmds[i])==0){
            //return the index of that command, that will be the same as the one in the cmd_id enum type
            return i;
        }
    }
    return flag;
}

/**
 * Parse the input string, and separate it in command and arguments
 *
 * This function will take in input four strings, representing a command received from the user, and tree additional
 * fields, representing a command, and two additional arguments. The function will parse the buffer string, extract the
 * informations, and save it in the input variables
 *
 * it then will return the command id of the input command
 *
 * Usage: get_args(char* <buffer>,
 *                 char* <command>,
 *                 char* <first argument>,
 *                 char* <second argument )
 *
 */
cmd_id get_args ( char* buf, char* cmd, char* arg1, char* arg2){
    //parse the buffer and fill the memory location of the other tree strings
    sscanf(buf,"%[^ ] %[^ ] %[^ ]",cmd,arg1,arg2);
    //terminate the tree strings with a null terminating character
    cmd[strcspn(cmd, "\n")]=0;
    arg1[strcspn(arg1, "\n")]=0;
    arg2[strcspn(arg2, "\n")]=0;
    //return the command id
    return find_id(cmd);
}


/**
 * Menu for handling all the commands the server received
 *
 * This function will take in input a string, representing a command, and will parse and
 * act accordingly with each command it receives from the client
 *
 * Usage: menu(char* <command>,int <socked file descriptor>)
 *
 */
void menu(char* input_line,int sockfd){
    //reset the content of the variables, so we can execute every time the loop with clean variables
    char command[MAXLINE]="\0";
    //variable used to save the first argument
    char arg1[MAXLINE]="\0";
    //variable used to save the second input argument
    char arg2[MAXLINE]="\0";
    //buffer variable
    char buffer[MAXLINE];
    //return buffer
    char ret[MAXLINE]="\0";

    //find the command id of the current command
    cmd_id flag=get_args(input_line,command,arg1,arg2);

    //switch statement to execute the proper command
    switch (flag){
        case CD_:
            //calling the change directory function
            cd(arg1,sockfd);
            break;
        case CDUP_:
            //calling the change directory function
            cd("../",sockfd);
            break;
        case PWD_:
            errno=0;
            //get the current working directory of the server
            getcwd(buffer, sizeof(buffer));
            //send it to the client
            snprintf(ret,MAXLINE, "%d %s\n",errno , buffer);
            Writen(sockfd, ret,strlen(ret));
            break;
        default: //_NEG LCD_ OPEN_ HELP ZERO_ CLOSE_ DISCONNECT_ QUIT_ BYE_ those command will never be received, as they are executed on the client side
            break;
    }
}