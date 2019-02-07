#include "in-out.h"

ssize_t my_read ( int fd, char* ptr )
{
    static int read_cnt = 0;
    static char* read_ptr;
    static char read_buf [ MAXLINE ];

    if ( read_cnt <= 0 ) {
        again:
            if ( ( read_cnt = read ( fd, read_buf,
                sizeof ( read_buf ) ) ) < 0 ) {
                if ( errno == EINTR ) goto again;
                return -1;
            }
            else if ( read_cnt == 0 ) return 0;
            read_ptr = read_buf;
    }

    read_cnt--; *ptr = *read_ptr++;
    return 1;
}

ssize_t readline ( int fd, void* vptr, size_t maxlen )
{
    size_t n, rc;
    char c, *ptr;

    ptr = vptr;
    for ( n = 1; n < maxlen; n++ ) {
        if ( ( rc = my_read ( fd, &c ) ) == 1 ) {
            *ptr++ = c;
            if ( c == '\n' ) break;
        }
        else if ( rc == 0 ) {
            if ( n == 1 ) return 0;
            else break;
        }
        else return -1;
    }

    *ptr = 0;
    return n;
}

ssize_t readn ( int fd, void* vptr, size_t n )
{
    ssize_t nread;
    size_t nleft = n;
    char* ptr = vptr;

    while ( nleft > 0 ) {
        if ( ( nread = read ( fd, ptr, nleft ) ) < 0 ) {
            if ( errno == EINTR ) nread = 0;  //will call read again
            else return -1;
        }
        else if ( nread == 0 ) break;  //EOF

        nleft -= nread; ptr += nread;
    }

    return ( n - nleft );  //return n>=0
}

ssize_t writen ( int fd, const void* vptr, size_t n )
{
    size_t nleft;
    ssize_t nwritten;
    const char* ptr;

    ptr = vptr; nleft =n;
    while ( nleft > 0 ) {
        if ( ( nwritten = write ( fd, ptr, nleft ) ) <= 0 ) {
            if ( errno == EINTR ) nwritten = 0;
            else return -1;
        }

        nleft -= nwritten;
        ptr += nwritten;
    }

    return n;
}

char* sock_ntop ( const struct sockaddr* sa, socklen_t salen )
{
    char portstr [ PORT_STR_SZ ];
    static char str [ ADDR_STR_SZ ];

    switch( sa->sa_family ) {
        case AF_INET: {
            struct sockaddr_in* sin = ( struct sockaddr_in* ) sa;

            if ( ! inet_ntop ( AF_INET, &sin->sin_addr, str,
                sizeof ( str ) ) ) return 0;
            if ( ntohs ( sin->sin_port ) ) {
                snprintf ( portstr, sizeof ( portstr ), ".%d",
                    ntohs ( sin->sin_port ) );
                strcat ( str, portstr );
            }
        }
    }

    return str;
}

#ifdef HAVE_SOCKADDR_DL_STRUCT
#include <net/if_dl.h>
#endif

char* sock_ntop_host ( const struct sockaddr* sa, socklen_t salen )
{
    char portstr [ PORT_STR_SZ ];
    static char str [ ADDR_STR_SZ ];

    switch ( sa->sa_family ) {
    case AF_INET: {
        struct sockaddr_in* sin = ( struct sockaddr_in* ) sa;

        if ( ! inet_ntop ( AF_INET, &sin->sin_addr, str,
            sizeof ( str ) ) ) return 0;
        if ( ntohs ( sin->sin_port ) ) {
            snprintf ( portstr, sizeof ( portstr ), ".%d",
                ntohs ( sin->sin_port ) );
            strcat ( str, portstr );
        }

        return str;
    }

#ifdef IPV6
    case AF_INET6: {
        struct sockaddr_in6* sin6 = ( struct sockaddr_in6* ) sa;

        if ( ! inet_ntop ( AF_INET6, &sin6->sin6_addr, str,
            sizeof ( str ) ) ) return 0;
        if ( ntohs( sin6->sin6_port ) ) {
            snprintf ( portstr, sizeof ( portstr ), ".%d",
                ntohs ( sin6->sin6_port ) );
            strcat ( str, portstr );
        }

        return str;
    }
#endif

#ifdef AF_UNIX
    case AF_UNIX: {
        struct sockaddr_un* unp = ( struct sockaddr_un* ) sa;

        // OK to have no pathname bound to the socket: happens on
        // every connect unless client calls bind first.

        if ( unp->sun_path [ 0 ] == 0 )
            strcpy ( str, "( no pathname bound )" );
        else
            snprintf ( str, sizeof ( str ), "%s", unp->sun_path );

        return str;
    }
#endif

#ifdef HAVE_SOCKADDR_DL_STRUCT
    case AF_LINK: {
        struct sockaddr_dl* sdl = ( struct sockaddr_dl* ) sa;

        if ( sdl->sdl_nlen > 0 )
            snprintf ( str, sizeof ( str ), "%*s", sdl->sdl_nlen,
                &sdl->sdl_data [ 0 ] );
        else
            snprintf( str, sizeof ( str ), "AF_LINK, index=%d",
                sdl->sdl_index );

        return str;
    }
#endif
    default:
        snprintf ( str, sizeof ( str ),
            "sock_ntop_host: unknown AF_xxx: %d, len %d",
            sa->sa_family, salen );

        return str;
    }

    return 0;
}
