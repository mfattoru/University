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
        if( !SKIP_ERROR[WRITE]){
            Close(fd);
            exit(1);
        }
        return -5;
    }
    return count;
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

    //check if the function was able to access and read from the buffer
    if ( (n = read( fd,  buf,  count ) ) == -1 ){
        perror( "ERROR: Unable to read from the file/buffer " );
        if ( !SKIP_ERROR[READ] ){
            Close(fd);
            exit(1);
        }
        return -5;
    }

    return n;
}


char* find_author(FILE *db,char* recvline){
    char buf[MAXLINE];      //buffer to save the line read from the file

    //variables declared as static, as they will be returned by the function,
    //so we need theyr memory location to be accessible even after the function
    //ended. I could have used a malloc to allocate dynamic memory in the heap,
    //but this is a prettier solution, and have the same final result.
    //it onl allocates MAXLINE memory no matter how big is the string to be saved.
    static char book[MAXLINE];  //variable used to contain the name of the book
    static char author[MAXLINE];  //variable used to contain the name of the author

    //int book_pos=0;    //used as index of book when splitting the parsed string
    //int auth_pos=0;  //used as index of author when splitting the parsed string
    //Flag that will work as an enabler to redirect the read characters to the
    //book array or to the author array. when enable is equal to zero, each
    //characted from the line read from the database will be saved in the book
    //array. when enable is equal to 1 each character from the line read from the
    //database will be saved in the author string.
    //int enable=0;

    //loop over all the lines in the database
    while ( Fgets(buf,MAXLINE,db) != NULL ){

        //reset the index of the array book and author, as we are going to read
        // a new complete value
//===========================
        // book_pos=0;
        // auth_pos=0;
//===========================
        //loop along all the character of the string read from the database, and
        //parse it character by character
        sscanf(buf,"%[^:]:%[^:]",book,author);

//------------------------------------------------------------------------------
        // for(int x=0;x<(int) strlen(buf)-1;x++){
        //     //skip this characted if it's a newline or a end of string
        //     if(buf[x]=='\n')
        //         continue;
        //
        //     //if we meet our separator caracter,alternate the string where
        //     //I'm saving character. If I was saving a book, save an author.
        //     //if I was saving n Author, now sava a book
        //     if(buf[x]==':' ){ //if I find a separator characted
        //         if(enable == 0){ //close the book string with a newline and a null terminating character
        //             book[book_pos]='\n';
        //             book[book_pos+1]='\0';
        //         }
        //         else{  //close the author string with a newline and a null terminating character
        //             author[auth_pos]='\n';
        //             author[auth_pos+1]='\0';
        //         }
        //         enable=!enable; //switch structure where to save
        //         continue;  //don't add the colon character to the book or author string
        //     }
        //
        //     if(enable==0){  //This is a character of a book
        //         book[book_pos]=buf[x];
        //         book_pos++;
        //     }
        //     else{  //this is a character of an author
        //         author[auth_pos]=buf[x];
        //         auth_pos++;
        //     }
        // }

//-----------------------------------------------------------------------------

        //compare the name of the book read from the database with the string received
        //from the user
        strcat(book,"\n");
        if (strcasecmp(book,recvline) == 0 ){
            //if we found the book, bring the file position indicator at the beginning
            //of the file, and return the author
            Fseek(db, 0, SEEK_SET);
            strcat(author,"\n");
            return author;
        }
    }
    //if after scanning the whole database we haven't found any book, bring the file
    //position indicator at the beginning of the file, and return the string "Unknown"
    //with a newline and a null terminator character
    Fseek(db, 0, SEEK_SET);
    return "Unknown\n\0";
}
