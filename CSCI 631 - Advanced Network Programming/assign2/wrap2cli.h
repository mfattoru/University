/**
 * Header file for wrap1cli.c
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/14/2018
 */

#ifndef _WRAP2CLI_H //avoid to execute those instructions more than once
#define _WRAP2CLI_H

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
#define CONNECT 2
#define FPUTS 3
#define READ 4
#define INET_PTON 5

#include <sys/socket.h>   //To import the socket function,connect function
#include <unistd.h>       //To import the close function, read function
#include <stdio.h>        //To import the fputs fuction
#include <arpa/inet.h>    //To import the inet_pton function
#include <stdlib.h>       //To import the exit function
#include <string.h>       //To import strerror
#include <errno.h>        //To import errno

int Socket(int , int , int ); //Create a socket and return it's file descriptor.
int Close(int );              //Close a file.
int Connect(int , const SA *, socklen_t ); //Initiate a connection on a Socket .
int Fputs(const char *, FILE *);  // Write string to stream.
int Read(int , void *, size_t );  //Read from a file descriptor
int Inet_pton(int , const char *, void *); //Convert IPv4 and IPv6 addresses from text to binary form

#endif
