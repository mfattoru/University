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

#include "wrap2srv.h"

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
        if(!SKIP_ERROR[BIND])
            exit(1);
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
        if ( !SKIP_ERROR[LISTEN] )
            exit(1);
        return -5;
    }
    return 0;
}

/**
 * Accept a connection on a socket.
 *
 * This function will take as input a file descriptor,a pointer to a structure
 * containing fields of address,port and af familytype to be filled and an
 * integer containing the size of the structure,used for initialization and
 * return a file descriptor for the accepted socket
 *
 * Usage: Accept( int <file despriptor> ,
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
        perror("ERROR: Unable to accept a connection on the socket ");
        if ( !SKIP_ERROR[ACCEPT])
            exit(1);
        return -5;
    }
    return res;
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
 *               size_t <size of the buffer>)
 *
 * @return int containing the number of bites writted on the file descriptor.
 * @error Print a message and exit the program with exit code 1,or -5 if ignored
 */
ssize_t Write(int fd,const void *buff,size_t size){
    //reset errno to 0 in case some other system call modified it's value
    errno = 0;
    int count=0;

    if ( ( count=write(fd,buff,size) ) == -1 ){
        perror( "ERROR: Unable to write on file ");
        if( !SKIP_ERROR[WRITE])
            exit(1);
        return -5;
    }
    return count;
}
