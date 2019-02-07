#ifndef H_IN_OUT
#define H_IN_OUT

#include "/home/cs631/common/config.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>       // inet(3) functions
#include <sys/socket.h>      // basic socket definitions
#include <sys/types.h>       // basic system data types
#include <sys/un.h>

// miscellanaous constants

#define ADDR_STR_SZ 128
#define PORT_STR_SZ 7
#define MAXLINE 4096         // max text length

ssize_t readline ( int, void*, size_t );
ssize_t readn ( int, void*, size_t );
ssize_t writen (int, const void*, size_t);

char* sock_ntop ( const struct sockaddr*, socklen_t );
char* sock_ntop_host ( const struct sockaddr*, socklen_t );

#endif
