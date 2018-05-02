/**
 * Header file for the utility functions
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 04/17/2018
 */

#ifndef _UTIL5CLI_H
#define _UTIL5CLI_H

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"  //used to include readline and writen
#include "prog5cli.h"

//default server port for the ftp client
#define SERVER_PORT 9880
#define SERVER_PORT_STR "9880"

#include <string.h>  //for strcmp
#include <stdio.h>
#include <stdlib.h>  // for atoi
#include <unistd.h>  //for chdir
#include <errno.h>        //To import errno
#include <wordexp.h>    //to import wordexp
#include "wrap5cli.h"  //to import the wrapper functions

//enum variable, containing the list of all the commands available on the system.
typedef enum { NEG_ = -1, ZERO_, QM_, BYE_, CD_, CDUP_, CLOSE_, DISCONNECT_,HELP_, LCD_, OPEN_, PWD_, QUIT_ } cmd_id;
//declare the variable cmds as extersn, so the list of all the commans available to the system get propagated
//between all the client
extern const char* cmds[ ];
//number of commands available
#define NUM_OF_COMMANDS 12


//header for the help function
void help(char* command);
//header for the change local directory function
void cd_local(char* directory);
//header for the open connection function
void open(char* host,char* port);
//header for the find_id function,that takes care of finding the value of the switch statement condition
cmd_id find_id ( char* command );
//header for the get_args function
cmd_id get_args ( char* buf, char* cmd, char* arg1, char* arg2);
//header fot the menu function, that takes care of printing the parser
void menu(char* ,int );
//change directory on the remote machine
void cd(char* ,int );

#endif // _UTIL5CLI_H
