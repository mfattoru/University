/**
 * Header file for the utility functions
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 04/17/2018
 */

#ifndef _UTIL5SRV_H
#define _UTIL5SRV_H

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"  //used to include readline and writen
#include "prog5srv.h"

#define SERVER_PORT 21
#define SERVER_PORT_STR "21"

#include <string.h>  //for strcmp
#include <stdio.h>
#include <stdlib.h>  // for atoi
#include <unistd.h>  //for chdir
#include <errno.h>        //To import errno
#include <wordexp.h>    //to include wordexp
#include "wrap5srv.h"

//enum variable, containing the list of all the commands available on the system.
typedef enum { NEG_ = -1, ZERO_, QM_, BYE_, CD_, CDUP_, CLOSE_, DISCONNECT_,HELP_, LCD_, OPEN_, PWD_, QUIT_ } cmd_id;
//declare the variable cmds as extersn, so the list of all the commans available to the system get propagated
//between all the client
extern const char* cmds[ ];
//number of commands available
#define NUM_OF_COMMANDS 12

//header of the change directory function
void cd(char* ,int );
//header for the find command id function
cmd_id find_id ( char* );
//header for the get argument function
cmd_id get_args ( char*, char* , char* , char* );
//header for the menu function
void menu(char* ,int );

#endif //_UTIL5SRV_H
