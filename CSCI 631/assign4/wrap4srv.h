/**
 * Header file for wrap4srv.c
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/30/2018
 */


#ifndef _WRAP4SRV_H
#define _WRAP4SRV_H

#define SA struct sockaddr

typedef int bool;
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
#define NUM_OF_FUNCTIONS 9
#define SOCKET 0
#define CLOSE 1
#define BIND 2
#define LISTEN 3
#define ACCEPT 4
#define READLINE 5
#define WRITEN 6
#define FGETS 7
#define SELECT 8

#include <sys/socket.h>   //To import the socket function,accept,listen,bind
#include <unistd.h>       //To import the close function, write function
#include <stdlib.h>       //To import the exit function
#include <string.h>       //To import strerror
#include <stdio.h>        //for perror
#include <errno.h>        //To import errno
#include "/home/cs631/common/in-out.h"   //To import readline and writen
#include <sys/select.h>   //To import the select function


int Socket(int , int , int ); //Create a socket and return it's file descriptor.
int Close(int );              //Close a file.
int Bind(int ,const SA * ,socklen_t );  //Bind a name to a socket.
int Listen(int ,int );              //Listen for connections on a socket.
int Accept(int ,SA * ,socklen_t *); //Accept a connection on a socket.

//Wrapper function to handle the errors thrown by readline, which gets a line from
//a file descriptor and saves it on a buffer
ssize_t Readline ( int, void*, size_t );
//Wrapper function to handle the errors thrown by writen, which writes the content
//pointed by the void pointer to a file descriptor
ssize_t Writen (int, const void*, ssize_t);
char *Fgets(char *, int , FILE *); //write the content of the pointed chat to FILE

//Select allow  a  program  to  monitor  multiple  file descriptors,  waiting
//until one or more of the file descriptors become "ready" for some class of
//I/O operation (e.g., input possible).  A file descriptor  is  considered
//ready if it is possible to perform a corresponding I/O operation
int Select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);

#endif /* _WRAP4SRV_H */
