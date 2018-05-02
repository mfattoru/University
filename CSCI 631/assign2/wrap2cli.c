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
 * @version 1.0 02/14/2018
 * @return:
 *          - exit code of the wrapped function
 *          - exit with code 1 in case the system call failed
 *          - -5 in case the system call failed but we decided to ignore the error
 */
#include "wrap2cli.h" //header file

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
        if ( !SKIP_ERROR[CONNECT] )
            exit(1);
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
 * Read from a file descriptor.
 *
 * This function will take as input a file descriptor, a pointer to a buffer and
 * a size_t value representing the number of bytes to read, and will return an
 * int representing the number of bites read from the buffer.
 *
 * Usage: Read( int <file descriptor>,
 *              void* <buffer>,
 *              size_t  <number of bytes to read> )
 *
 * @return number of bytes read on success
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Read( int fd, void *buf, size_t count ){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;
    int n = 0;

    //check if the function was able to access and reab from the buffer
    if ( (n = read( fd,  buf,  count ) ) == -1 ){
        perror( "ERROR: Unable to read from the file/buffer " );
        if ( !SKIP_ERROR[READ] )
            exit(1);
        return -5;
    }

    return n;
}
