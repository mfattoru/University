/**
 * Library containing wrapper function for the necessary system calls
 *
 * The current source code is to be used as library to import wrapper functions
 * for the used system calls. The code will perform all the necessary checks on
 * possible errors on the system calls and handle accordingly the errors, by
 * printing on standard error a user friendly message followed by the
 * description of the problem. Based on the value of the global variable
 * SKIP_ERROR, the wrapper functions will, in case of error, exit the program
 * or try to continue the execution respectively if SKIP_ERROR is equal to 0
 * or 1.
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 03/30/2018
 * @return:
 *          - exit code of the wrapped function
 *          - exit with code 1 in case the system call failed
 *          - -5 in case the system call failed but we decided to ignore the error
 */
#include "wrap4cli.h" //header file

/**
 * Create a socket and return it's file descriptor.
 *
 * This function will take as input the domain,type and protocol of the socket
 * to be created and return it's file descriptor
 *
 * Usage: Socket( int <domain type> ,
 *                int <socket type> ,
 *                int <protocol type>)
 *
 * @return int containing the file descriptor of the created socket.
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Socket( int domain, int type, int protocol ){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;
    int sockfd;

    //check if the creation of socket is successful
    if ( ( sockfd = socket( domain,  type,  protocol ) ) == -1 ){
        perror( "ERROR: error during the creation of a socket " );
        if ( !SKIP_ERROR[SOCKET] )
            exit(1);
        return -5;
    }
    //return the file descriptor of the socket
    return sockfd;
}

/**
 * Close a file.
 *
 * This function will take as input a file descriptor, and try to close the
 * associated file.
 *
 * Usage: Socket( int <file descriptor> )
 *
 * @return 0 on success
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Close(int fd){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;

    //check if the file was successfully closed
    if ( close( fd ) == -1 ){
        perror( "ERROR: Unable to close the file " );
        if ( !SKIP_ERROR[CLOSE] )
            exit(1);
        return -5;
    }

    return 0;
}

/**
 * Initiate a connection on a Socket .
 *
 * This function will take as input a socket file descriptor, a structure
 * containing the information of address,port and af family of the destination
 * and an integer to specify the size of the destination address, and try to
 * initiate a connection on the socket.
 *
 * Usage: Connect( int <Socket file descriptor>,
 *                 sockaddr <Address structure>,
 *                 socklen_t <address size> )
 *
 * @return 0 on success
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Connect( int sockfd, const struct sockaddr *addr, socklen_t addrlen ){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;

    //check if the connection was successful
    if ( connect( sockfd,addr, addrlen) == -1 ){
        perror( "ERROR: Unable to connect to the server " );
        if ( !SKIP_ERROR[CONNECT] ){
            Close(sockfd);
            exit(1);
        }
        return -5;
    }

    return 0;
}

/**
 * Write string to stream..
 *
 * This function will take as input a pointer to a character, and a pointer to a
 * stream, and print the content of the pointed character data to the stream.
 *
 * Usage: Fputs( const char* <pointer to char>,
 *                FILE <pointer to file stream> )
 *
 * @return 0 on success
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Fputs( const char *s, FILE *stream ){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;

    //check if the function was able to write on the stream
    if ( fputs( s, stream ) == EOF ){
        perror( "ERROR: Unable to write on stream " );
        if ( !SKIP_ERROR[FPUTS] )
            exit(1);
        return -5;
    }

    return 0;
}

/**
 * Convert IPv4 and IPv6 addresses from text to binary form
 *
 * This function will take as input the af family, a char pointer from where to
 * get the text address a pointer to a destination where to store the converted
 * address in binary form, and will return the
 * containingand the information of address,port and af family of the destination
 * and an integer to specify the size of the destination address.
 *
 * Usage: Inet_pton( int <af familyr>,
 *                   const char* <address source>,
 *                   void* <address destination> )
 *
 * @return 1 on success
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Inet_pton( int af, const char *src, void *dst ){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;

    int res = inet_pton( af, src , dst );

    //check if the conversion was successful, and not try to identify the problem
    if ( res == 0 ){ // not a valid network address
        fprintf( stderr,"ERROR: %s is not a valid network address\n", src );
        if ( !SKIP_ERROR[INET_PTON] )
            exit(1);
        return -5;
    }
    else if ( res == -1 ){ //syscall error
        perror( "ERROR: Not a valid af family " );
        if ( !SKIP_ERROR[INET_PTON] )
            exit(1);
        return -5;
    }

    return res;
}

/**
 * Readline - get a line from a user with editing.
 *
 * This function will take as input a file descriptor, a pointer to a buffer and
 * a size_t value representing the number of bytes to read, and will return a
 * signed size_t representing the number of bites read from the buffer.
 *
 * Usage: Readline( int <file descriptor>,
 *                  void* <buffer>,
 *                  ssize_t  <number of bytes to read> )
 *
 * @return number of bytes read on success
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
ssize_t Readline(int fd, void *buf, size_t count){
    errno = 0;
	ssize_t	n;

	if ( (n = readline(fd, buf, count)) == -1 ){
        perror("ERROR: Unable to read from buffer");
        if ( !SKIP_ERROR[READLINE] ){
            Close(fd);
            exit(1);
        }
        return -5;
    }
	return n;
}


/**
 * Write to a file descriptor.
 *
 * This function will take as input an integer representing a file descriptor,
 * a constant pointer representing the buffer from where to get the information
 * and the size of the buffer, and will write all the information from the
 * buffer to the file descriptor.
 *
 * Usage: Writen( int <file descriptor> ,
 *               const void * <source buffer> ,
 *               ssize_t <size of the buffer>)
 *
 * @return int containing the number of bites writted on the file descriptor.
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
ssize_t Writen(int fd, const void *ptr, ssize_t nbytes) {
    errno = 0;
    ssize_t n;

	if ( (n = writen(fd, ptr, nbytes)) != nbytes){
        //print how many bytes the function was able to write over the total of
        //bytes it was supposed to write
        fprintf( stderr,"ERRROR: Wrote %zu\\%zu bytes ",n,nbytes);
        if ( !SKIP_ERROR[WRITEN] ){
            Close(fd);
            exit(1);
        }
        return -5;
    }
    return n;
}


/**
 * Read string from stream.
 *
 * This function will take as input a pointer to a character,representing the
 * place where to store what is read, an integer representing the number of bytes-1
 * to be read at most, and a file descriptor pointing to the stream from where
 * you want the data to be read from.
 *
 * Usage: Fgets( const char* <pointer to char>,
 *               int <num of bytes>
 *               FILE* <pointer to file stream> )
 *
 * @return number of byte read on success
 * @error Print a message and exit the program with exit code 1.
 *        The function returns NULL when reading the EOF, so we added a check
 *        on errno to exit only if there's a system call error, and not just a
 *        simple EOF.
 */
char *Fgets(char *s, int size, FILE *stream){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;
    char* ret;

    //check if the function was able to read from the stream
    if ( ( ret=fgets( s,size, stream ) ) == NULL ){
        //if its in error condition and not just an EOF
        if ( !SKIP_ERROR[FGETS] && errno != 0){
            perror( "ERROR: Unable to get data from the stream " );
            exit(1);
        }
    }
    return ret;
}


/**
 * Select allow  a  program  to  monitor  multiple  file descriptors,  waiting
 * until one or more of the file descriptors become "ready" for some class of
 * I/O operation (e.g., input possible).  A file descriptor  is  considered
 * ready if it is possible to perform a corresponding I/O operation
 *
 * Usage: Select( int <highest-numbered file descriptor>,
 *                fd_set <set watched to see if there is space to read data>,
 *                fd_set <set watched to see if there is space to write data>,
 *                fd_set <This set is watched for "exceptional conditions">,
 *                timeval <This is the longest time select() may wait before returning>
 *               )
 *
 * @return number of file selector ready. 0 if timed out
 * @error A return value of -1 indicates an error, with errno being set
 *        appropriately.  In the case of an error, the contents of the returned
 *        sets and the struct timeout contents are undefined and should not be
 *        used.
 */
int Select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;
    int nfd;

    if( (nfd = select( nfds ,readfds ,writefds, exceptfds ,timeout)) == -1 ){
        //in case of error, if skip_error is false, then print an error and then exit
        if ( !SKIP_ERROR[SELECT] ){
            perror("ERROR: Error while checking the ready file descriptors ");
            exit(1);
        }
    }
    return nfd;
}

/**
 * The shutdown() function shall cause all or part of a full-duplex connection
 * on the socket associated with the file descriptor socket to be shut down.
 *
 * Usage: Shutdown( int <socket file descriptor>,
 *                  int <specified the type of shutdown>
 *                )
 *
 * @return 0 on success.
 * @error A return value of -1 indicates an error, with errno being set
 *        appropriately.
 */
int Shutdown(int socket, int how){
    //reset errno to 0 in case some other system call modified it's value
    errno=0;
    //check if we were successfully able to execute a shutdown
    if( shutdown(socket, how) == -1 ){
        //if there's an error and skip_error is false, then print an error and then exit
        if ( !SKIP_ERROR[SHUTDOWN] ){
            perror("ERROR: Error while checking shutting down the socket ");
            exit(1);
        }
    }
    return 0;
}
