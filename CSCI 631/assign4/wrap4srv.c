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

#include "wrap4srv.h"

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
 * Bind a name to a socket.
 *
 * This function will take as input a socket file descriptor, a structure
 * containing the information of address,port and af family
 * and an integer to specify the size of the destination address, and try to
 * bind the name to the socket.
 *
 * int Bind(int <file descriptor>,
 *          const struct sockaddr <address structure>,
 *          socklen_t <address length>);
 *
 * @return 0 on success.
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Bind(int fd,const SA *addr,socklen_t len){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;

    if( bind(fd,addr,len) == -1){
        perror("ERROR: Unable to bind a name to the socket ");
        if(!SKIP_ERROR[BIND]){
            Close(fd);
            exit(1);
        }
        return -5;
    }
    return 0;
}

/**
 * Listen for connections on a socket.
 *
 * This function will take as input a socket file descriptor, and an integer
 * representing the size of the queue
 *
 * Usage: Listen( int <file descriptor> ,
 *                int <queue size> )
 *
 * @return 0 on success.
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Listen(int fd,int queue){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;

    if ( listen(fd,queue) == -1 ){
        perror("ERROR: Unable to listen for connection on the socket ");
        if ( !SKIP_ERROR[LISTEN] ){
            Close(fd);
            exit(1);
        }
        return -5;
    }
    return 0;
}

/**
 * Accept a connection on a socket.
 *
 * This function will take as input a file descriptor,a pointer to a structure
 * containing fields of address,port and af family type to be filled and an
 * integer containing the size of the structure,used for initialization and
 * return a file descriptor for the accepted socket
 *
 * Usage: Accept( int <file descriptor> ,
 *                struct sockarrd <address structure> ,
 *                socklen_t <size of the structure>)
 *
 * @return int containing the file descriptor of the created socket.
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
int Accept(int fd, SA *address,socklen_t *size){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;
    int res;

    if ( (res=accept (fd,address,size) ) == -1 ){
         //Handle the case where the accept function gets interrupted by a signal
        if(errno == EINTR){
            return Accept(fd, address, size);
        }
        perror("ERROR: Unable to accept a connection on the socket ");
        if ( !SKIP_ERROR[ACCEPT]){
            Close(fd);
            exit(1);
        }
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
        perror("ERROR: Unable to read from buffer ");
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
 * Usage: Write( int <file descriptor> ,
 *               const void * <source buffer> ,
 *               ssize_t <size of the buffer>)
 *
 * @return int containing the number of bites written on the file descriptor.
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
ssize_t Writen(int fd, const void *ptr, ssize_t nbytes) {
    errno = 0;
    ssize_t n;

	if ( (n = writen(fd, ptr, nbytes)) != nbytes){
        //print how many bytes the function was able to write over the total of
        //bytes it was supposed to write
        fprintf( stderr,"ERROR: Wrote %zu\\%zu bytes ",n,nbytes);
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
        if ( !SKIP_ERROR[FGETS] && errno != 0){  //if it's in error condition
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
    errno = 0;
    int nfd;

    if( (nfd = select( nfds ,readfds ,writefds, exceptfds ,timeout)) == -1 ){
        if ( !SKIP_ERROR[SELECT] ){
            perror("ERROR: Error while checking the ready file descriptors ");
            exit(1);
        }
    }
    return nfd;
}