/**
 * Header file for wrap1srv.c
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/06/2018
 */


#ifndef _WRAP3SRV_H
#define _WRAP3SRV_H

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
#define NUM_OF_FUNCTIONS 13
#define SOCKET 0
#define CLOSE 1
#define BIND 2
#define LISTEN 3
#define ACCEPT 4
#define READLINE 5
#define WRITEN 6
#define FGETS 7
#define FORK 8
#define FSEEK 9
#define WAITPID 10
#define SIGNAL 11
#define FOPEN 12

#include <sys/socket.h>   //To import the socket function,accept,listen,bind
#include <unistd.h>       //To import the close function, write function
#include <stdlib.h>       //To import the exit function
#include <string.h>       //To import strerror
#include <stdio.h>        //for perror
#include <errno.h>        //To import errno
#include <sys/wait.h>    //for waitpid
#include "/home/cs631/common/in-out.h"   //To import readline and writen
#include <signal.h>      //To handle the signals



int Socket(int , int , int ); //Create a socket and return it's file descriptor.
int Close(int );              //Close a file.
int Bind(int ,const SA * ,socklen_t );  //Bind a name to a socket.
int Listen(int ,int );              //Listen for connections on a socket.
int Accept(int ,SA * ,socklen_t *); //Accept a connection on a socket.

//Wrapper finction to handle the errors thrown by readline, which gets a line from
//a file descriptor and saves it on a buffer
ssize_t Readline ( int, void*, size_t );
//Wrapper finction to handle the errors thrown by writen, which writes the content
//pointed by the void pointer to a file descriptor
ssize_t Writen (int, const void*, ssize_t);
char *Fgets(char *, int , FILE *); //write the content of the pointed chat to FILE
pid_t Fork(void);  //function used to create a child process
pid_t Waitpid(pid_t, int *, int);  //function used to wait for a child process
int Fseek(FILE *, long, int);  //reposition the file position indicator
FILE *Fopen(const char *, const char *);  //function used to open a file

//definition of a type to reduce the long definition
//of the signal function, that is as follow:
//void (*signal(int signo, void (*func )(int)))(int);
typedef void Sigfunc(int);
Sigfunc *signal(int, Sigfunc*);  //fignal function
Sigfunc *Signal(int, Sigfunc *);  //wrapper for the signal finction

#endif /* _WRAP3SRV_H */
