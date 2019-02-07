/**
 * Header file for prog2srv.c
 *
 * Usage: <programName> [Port Number]
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/06/2018
 */

#ifndef _PROG3SRV_H
#define _PROG3SRV_H

#define LISTENQ 10  //number of client requests in the queue
#define SERV_PORT 9880   //default server port
#define SERVER_DEBUG 0  //1 enable debug printing, 0 disable it

//macro used to get rid of the unused variable for the signal number
//in the handler function
#define UNUSED(x) (void)(x)


//location of the database file
#define DB_PATH "/home/cs631/common/books.d"  //used to contain the path of the database

#include "/home/cs631/common/config.h"

#include <time.h>        //for time and ctime
#include <sys/socket.h>  //for the socket support
#include <stdlib.h>      //for the NULL value
#include <stdio.h>       //for snprintf and fprintf, and file operators
#include <arpa/inet.h>   //for the htonl and htons, and INET_ADDRSTRLEN

char* find_author(FILE *, char*);  //Loop over the database and return the author of the book
void search_book(int , FILE *); //Makes a loop to handle all the queries from the client
void handler(int);    //function able to handle the termination of a child process

#endif /* _PROG2SRV_H */
