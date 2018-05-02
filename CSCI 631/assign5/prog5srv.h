/**
 * Header file for prog5srv.c
 *
 * Usage: <programName> [Port Number]
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 04/17/2018
 */

#ifndef _PROG5SRV_H
#define _PROG5SRV_H

#define LISTENQ 10  //number of client requests in the queue
#define SERV_PORT 9880   //default server port

//macro used to get rid of the unused variable for the signal number
//in the handler function
#define UNUSED(x) (void)(x)

#include "/home/cs631/common/config.h"

#include <time.h>        //for time and ctime
#include <sys/socket.h>  //for the socket support
#include <stdlib.h>      //for the NULL value
#include <stdio.h>       //for snprintf and fprintf, and file operators
#include <arpa/inet.h>   //for the htonl and htons, and INET_ADDRSTRLEN

#include "util5srv.h"


void receive_command(int); //Makes a loop to handle all the queries from the client
void handler(int);    //function able to handle the termination of a child process

#endif /* _PROG5SRV_H */
