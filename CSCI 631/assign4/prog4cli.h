/**
 * Header file for prog1cli.c
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/06/2018
 */

#ifndef _PROG4CLI_H //avoid to execute those instructions more than once
#define _PROG4CLI_H

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"  //used to include readline and writen

//default server port
#define SERV_PORT 9880

//definition of the boolean type variable
typedef int bool;
#define true 1
#define false 0

//already header guarded in their source code
#include <stdio.h>
#include <stdlib.h>  // for atoi

//function to handle the client side of the read from standard input, writing on
//socket, reading the server response and then printing the response to standard
//output
void str_cli(FILE *, int);
int max(int , int );


#endif /* _PROG4CLI_H */
