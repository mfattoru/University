/**
 * Header file for wrap1srv.c
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/14/2018
 */


#ifndef _WRAP2SRV_H
#define _WRAP2SRV_H

#define SA struct sockaddr

#define true 1
#define false 0

//Declare a global variable accessible from both source files,so it's possible
//to manipulate the actions of the wrapper functions. Now with SKIP_ERROR set
//equal to 'false' the wrapper functions terminate the program, for the value
//'true',the functions will try to continue as nothing happened, returning -5
//as return value. The user checking the return value of the wrapper function
//could decide the course of action, like trying again the command, or just
//quitting the program. This leaves space for further improvement.
extern int SKIP_ERROR[];

//defining the number of functions which I will control the errors
#define NUM_OF_FUNCTIONS 6
#define SOCKET 0
#define CLOSE 1
#define BIND 2
#define LISTEN 3
#define ACCEPT 4
#define WRITE 5

#include <sys/socket.h>   //To import the socket function,accept,listen,bind
#include <unistd.h>       //To import the close function, write function
#include <stdlib.h>       //To import the exit function
#include <string.h>       //To import strerror
#include <stdio.h>        //for perror
#include <errno.h>        //To import errno

int Socket(int , int , int ); //Create a socket and return it's file descriptor.
int Close(int );              //Close a file.
int Bind(int ,const SA * ,socklen_t );  //Bind a name to a socket.
int Listen(int ,int );              //Listen for connections on a socket.
int Accept(int ,SA * ,socklen_t *); //Accept a connection on a socket.
ssize_t Write(int ,const void* ,size_t); //Write to a file descriptor.

#endif /* _WRAP2SRV_H */
