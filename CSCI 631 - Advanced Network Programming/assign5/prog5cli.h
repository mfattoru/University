/**
 * Header file for prog5cli.h
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 04/17/2018
 */

#ifndef _PROG5CLI_H //avoid to execute those instructions more than once
#define _PROG5CLI_H

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"  //used to include readline and writen
#include "util5cli.h"                   //import utility functions

//default server port
#define SERV_PORT 9880

//define a boolean type
typedef int bool;
#define true 1
#define false 0

//already header guarded in their source code
#include <stdio.h>
#include <stdlib.h>  // for atoi

//function to handle the client side of the read from standard input, writing on
//socket, reading the server response and then printing the response to standard
//output
bool client ( char* arg1, char* arg2 );
bool str_cli(int sockfd, char* saddr);

#endif /* _PROG5CLI_H */
