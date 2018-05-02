/**
 * Header file for progsrv.c
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/30/2018
 */

#ifndef _PROG4SRV_H
#define _PROG4SRV_H

#define LISTENQ 10  //number of client requests in the queue
#define SERV_PORT 9880   //default server port
#include <float.h>     //for max number of digits
#define MAX_N_DIGITS (3 + DBL_MANT_DIG - DBL_MIN_EXP)  //maximum number of digits in a double

//definition of the boolean type
typedef int bool;
#define true 1
#define false 0

#include "/home/cs631/common/config.h"

#include <sys/socket.h>  //for the socket support
#include <stdlib.h>      //for the NULL value
#include <stdio.h>       //for snprintf and fprintf, and file operators
#include <arpa/inet.h>   //for the htonl and htons, and INET_ADDRSTRLEN
#include <sys/select.h>  //for the select function
#include <math.h>        //for pow function
#include <ctype.h>       //for isdigit

//definition of a structure to handle all the operation for the server I/O multiplexing
typedef struct {
    int fd;
    double sum, exp;
    bool flag;
}Client;

//sum the numbers received from the client using the following formula:
//    - First number is the exponent
//    - Following numbers will be used to sum
//the sum is performed as: sum = num1^exp + num2^exp .... +numN^exp;
void sum_my_numbers(Client *, char* );

#endif /* _PROG4SRV_H */
