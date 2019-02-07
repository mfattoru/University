/**
 * Client application for an ftp client
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
#include "wrap5cli.h"    //wrapper functions
#include "util5cli.h"    //Utility functions

//Initialize the array to zeros,all the errors will not be skipped
int SKIP_ERROR[NUM_OF_FUNCTIONS] = { };
//Initialize the array cmds, containing the list of all the available commands.
const char* cmds[ ]={ "", "?", "bye", "cd", "cdup", "close", "disconnect", "help", "lcd", "open", "pwd", "quit" };

int main( ) {
    //don't exit the program if inet_pton, connect or chdir fails
    SKIP_ERROR[INET_PTON]=1;
    SKIP_ERROR[CONNECT]=1;
    SKIP_ERROR[CHDIR]=1;
    //string used to contain the input line
    char input_line[MAXLINE];

    //print the ftp prompt
    Fputs("ftp> ", stdout);
    //loop unfil Fgets returns null, this is in case the user sends an EOF to the program
    //through a ctrl + D command
    while (Fgets(input_line, MAXLINE, stdin) != NULL) {
        //reset the content of the variables, so we can execute every time the loop with clean variables
        //variable used to save the current input command
        char command[MAXLINE] = "\0";
        //variable used to contain the first argument of the command
        char arg1[MAXLINE] = "\0";
        //variable used to contain the second argument of the command
        char arg2[MAXLINE] = "\0";

        //function called to convert the received string command, to a command id, so we can use it as
        //condition for the switch statement
        cmd_id flag = get_args(input_line, command, arg1, arg2);

        //switch statement to perform actions for all the available commands
        switch (flag) {
            case NEG_:  //command not valid
                Fputs("?Invalid command ", stdout);
                Fputs(command, stdout);
                Fputs("\n", stdout);
                break;
            case ZERO_:  //empty command,so we have to do nothing
                Fputs("ftp> ",stdout);
                continue;
            case HELP_:;  //help and ?  do the same thing, so they can be one case together
            case QM_:
                //call the help function, to help the user understand all the commands
                help(arg1);
                break;
            case QUIT_:;  //quit and bye do the same thing, so they can be one case together
            case BYE_:
                //exit the program, and return zero.
                return 0;
                break;
            case LCD_:  //change local directory
                cd_local(arg1);
                break;
            case OPEN_:; //open a  new connection with an ftp server
                open(arg1, arg2);
                break;
            default:  //PWD_ CLOSE_ DISCONNECT_ CDUP_ CD_ are not handled when the client is not connected
                printf("Not connected.\n");
                break;
        }
        //keep printing the ftp command prompt at each iteration
        Fputs("ftp> ", stdout);
    }
    return 0;
}