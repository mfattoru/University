/**
 * Library function, used to execute utility commands for the client
 *
 * The current source code, represent a parser for an ftp client.
 * Once the client opens a connection with an ftp server, the client function in prog5cli.c
 * takes care of the handling of all the commands
 *
 * Usage: <programName>
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 04/17/2018
 * @return 0 if the program is Successful, 1 for wrong imputs,
 */

#include "util5cli.h"   //include utility header file


/**
 * Print to screen the helper
 *
 * This function will take in input a string, representing a command, and will print to screen
 * helper information about it. In case a command isn't passed to the function, it will print
 * a list of all the available commands
 *
 * Usage: help(char* <command>)
 *
 */
void help(char* command){
    //find the command id of the current command
    cmd_id flag = find_id(command);

    //switch statement to print the proper helper line
    switch (flag){
        case NEG_:  //the command doesn't exist
            Fputs("?Invalid help command ",stdout);
            Fputs(command,stdout);
            Fputs("\n",stdout);
            break;
        case ZERO_:  //no command received as input, print all the available commands
            Fputs("Commands may be abbreviated.  Commands are:\n",stdout);
            //loop over all the commands
            for(int i=1;i<NUM_OF_COMMANDS;i++){
                //print five commands for each line
                if( ((i-1)%5)==0){
                    Fputs("\n",stdout);
                }
                else if(i!=1){  //separate each command by a tab
                    Fputs("\t", stdout);
                }
                //and print each command in a 10 character field left aligned
                printf("%-10s", cmds[i]);
            }
            printf("\n\n");
            break;
        case QM_:  //question mark command
            Fputs("?\tprint local help information\n",stdout);
            break;
        case BYE_:  //bye command
            Fputs("bye\tterminate ftp session and exit\n",stdout);
            break;
        case CD_:  //change directory command
            Fputs("cd\tchange remote working directory\n",stdout);
            break;
        case CDUP_:  //change directory to the father directory
            Fputs("cdup\tchange remote working directory to parent directory\n",stdout);
            break;
        case CLOSE_:  //close command
            Fputs("close\tterminate ftp session\n",stdout);
            break;
        case DISCONNECT_:  //disconnect command
            Fputs("disconnect\tterminate ftp session\n",stdout);
            break;
        case HELP_:  //help command
            Fputs("help\tprint local help information\n",stdout);
            break;
        case LCD_:  //change local directory command
            Fputs("lcd\tchange local working directory\n",stdout);
            break;
        case OPEN_:  //open a connection to a remote ftp server
            Fputs("open\tconnect to remote ftp\n",stdout);
            break;
        case PWD_:  //print the remote working directory
            Fputs("pwd\tprint working directory on remote machine\n",stdout);
            break;
        case QUIT_:  //quit command
            Fputs("quit\tterminate ftp session and exit\n",stdout);
            break;
    }
}

/**
 * Change local directory
 *
 * This function will take in input a string, representing a path to a directory, and will try to
 * change the current directory, to the one specified. If no directory is received as input, the
 * function will consider the Home directory as the default one.
 *
 * The function will then print a message in case it was able ot nor to change directory
 *
 * Usage: cd_local(char* <directory>)
 *
 */
void cd_local(char* directory) {
    //variable where to store the current directory location
    char buffer[MAXLINE];
    if(strcmp(directory,"")==0) {
        directory=getenv("HOME");
    }
    //print two different mesages in case we were, or weren't able to change directory
    if (Chdir(directory) == -1) { //error
        fprintf(stderr, "local: %s : No such file or directory\n", directory);
    } else {
        //print the current directory path, when we change directory
        getcwd(buffer, sizeof(buffer));
        printf("Local directory now %s\n", buffer);
    }

}

/**
 * Change remote directory
 *
 * This function will take in input a string, representing a path to a directory, and will try to
 * change the remote directory, to the one specified. If no directory is received as input, the
 * function will consider the Home directory as the default one.
 *
 * The function will then print a message in case it was able ot nor to change directory
 *
 * Usage: cd(char* <directory>, int <socket file descriptor>)
 *
 */
void cd(char* directory,int sockfd) {
    //declare an empty string, where to temporary save the data, in case someone run the open command without
    //specifying the remote directory
    char input_line[MAXLINE];
    //contains the string received back from the server
    char ret[MAXLINE];
    //if the used didn't specify a directory, ask him again for one
    if(strcmp(directory,"")==0){
        Fputs("(remote directory) ",stdout);
        //get the content from standard input
        Fgets(input_line,MAXLINE,stdin);
        //remove the newline from the string, and replace it with a terminating character
        input_line[strcspn(input_line, "\n")]=0;
    }
    //if the now inserted a remote directory
    if(strcmp(input_line,"")!=0){
        //create the new command
        snprintf(ret,MAXLINE, "cd %s\n",input_line);
    }
    else{ //the user didn't insert a directory or the one inserted originally is not empty
        //create the new command
        if(strcmp(directory,"")==0){
            strcpy(directory,"~");
        }
        snprintf(ret,MAXLINE, "cd %s\n",directory);
    }
    //send the command to the server
    Writen(sockfd, ret, strlen(ret) );
    //receive the response
    Readline(sockfd,ret,MAXLINE);
    //replace the newline with a terminating character
    ret[strcspn(ret, "\n")]=0;
    //if the errornumber received from the server is zero, means that the change was successfull
    if(ret[0]=='0'){
        Fputs(ret,stdout);
        Fputs("\n",stdout);
    }
    else{  //unable to change remote folder
        Fputs(ret,stderr);
        Fputs(" Failed to change directory.\n",stderr);
    }

}

/**
 * Open a connection with a remote ftp server
 *
 * This function will take in input a string, representing the address of the ftp server, and a string
 * representing the port number of the server.
 *
 * the function after the necessary checks, will then execute the client function, that has the purpose of
 * administrating all the inputs from the clients.
 *
 * Usage: open(char* <server address>, char* <server port>)
 *
 */
void open(char* host,char* port){
    //declare an empty string, where to temporary save the data, in case someone run the open command without
    //specifying server address of port number
    char input_line[MAXLINE];

    //if the used didn't specify a server address, ask him again for one
    if(strcmp(host,"")==0){
        Fputs("(to) ",stdout);
        //get the content from standard input
        Fgets(input_line,MAXLINE,stdin);
        //parse the input string as a space separated string containing the address as first element
        // and optionally a port number as second
        sscanf(input_line,"%[^ ] %[^ ]",host,port);
        //remove the newline from the string, and replace it with a terminating character
        host[strcspn(host, "\n")]=0;
    }

    //if the server address is still empty, print a usage string to display
    if(strcmp(host,"")==0){  //if the user doesn't insert anything, just print the usage message as ftp does
        fprintf(stderr,"usage: open host-name [port]\n");
        return;
    }
    //if the used didn't insert a port number, then use the default port number
    if(strcmp(port,"") == 0) { //TODO check if the user inserted again also the port number, beside the address
        port = SERVER_PORT_STR;
    }
    //calls client function in prog5cli.c
    if( ! client(host,port) ){
        //Fputs("Terminating the program\n",stdout);
        exit(0);
    }
//    else{
//        Fputs("Disconnected from the server. Continuing execution\n",stdout);
//    }
}


/**
 * Find the command id
 *
 * This function will take in input a string, representing a command received from the user, and will search in the
 * available structures, for an equal command. If that specific command is found, then the function will return the
 * assocated command id
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