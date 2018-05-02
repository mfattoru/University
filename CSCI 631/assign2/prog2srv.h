/**
 * Header file for prog2srv.c
 *
 * Usage: <programName> [Port Number]
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/14/2018
 */

#ifndef _PROG2SRV_H
#define _PROG2SRV_H

#define MAXLINE 27  //buffer dimension
#define LISTENQ 10  //number of client requests in the queue
#define SERV_PORT 9880   //default server port

#include "/home/cs631/common/config.h"

#include <time.h>        //for time and ctime
#include <sys/socket.h>  //for the socket support
#include <stdlib.h>      //for the NULL value
#include <stdio.h>       //for snprintf and fprintf
#include <arpa/inet.h>   //for the htonl and htons, and INET_ADDRSTRLEN

#endif /* _PROG2SRV_H */
