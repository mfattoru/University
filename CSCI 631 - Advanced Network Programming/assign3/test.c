#include <stdio.h>
#include <string.h>

int main()
{
    FILE* db=fopen("books.d","r");
    char buf[1024];
    char book[1024];
    char author[1024];
    int enable=0;

    // char *book = NULL;
    // char* author =NULL;
    // char* ptr=NULL;
    // int res=0;
    char tested[]="A First Course in Probability";
    // size_t len;
    // size_t len2;
    // int n;
    //while (  res != -1){
    while ( fgets(buf,1024,db) ){
        sscanf(buf,"%[^:]:%[^:]",book,author);

        //char* tmp = strdup(buf);
        // book_pos=0;
        // auth_pos=0;
        // for(int x=0;x<strlen(buf)-1;x++){
        //     if(buf[x]=='\n')
        //         continue;
        //
        //     if(buf[x]==':' ){
        //         if(enable == 0)
        //             book[book_pos]='\0';
        //         else
        //             author[auth_pos]='\0';
        //         enable=!enable;
        //         continue;
        //     }
        //
        //     if(enable==0){
        //         book[book_pos]=buf[x];
        //         book_pos++;
        //     }
        //     else{
        //         author[auth_pos]=buf[x];
        //         auth_pos++;
        //     }
        // }
        //book=get_field(1,tmp);
        //author=get_field(2,tmp);
        printf("BOOK: %s - AUTH: %s\n",book,author);

        if (strcmp(book,tested) == 0 ){
            printf("Found\n");
            printf("%s---%s\n",book,tested);
        }
    }

        // res= getdelim(&book,&len,':',db);
        // res = getdelim(&author,&len2,':',db);
        //
        // if (book[strlen(book)-1] == ':')
        //     book[strlen(book)-1] = '\0';
        // if (author[strlen(author)-1] == ':')
        //     author[strlen(author)-1] = '\0';
        //
        // if ((n=strcmp(book,tested)) == 0 ){
        //     printf("Found\n");
        //     printf("%s---%s\n",book,tested);
        //
        // }
        // else{
        //     printf("%d",n);
        //     printf("%s---%s\n",book,tested);
        // }
        // if( (ptr = strchr(author, '\n')) != NULL)
        //     *ptr = '$';
        //     if( (ptr = strchr(book, '\n')) != NULL)
        //         *ptr = '$';
        //printf("%s\n",author);

    //}
    return 0;
}
//
// char* get_field(int pos, char* input_string){
//     char *tok = NULL;
//     for (tok = strtok(line, ":");
// }





// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// const char* getfield(char* line, int num)
// {
//     const char* tok;
//     for (tok = strtok(line, ":");
//             tok && *tok;
//             tok = strtok(NULL, ":\n"))
//     {
//         if (!--num)
//             return tok;
//     }
//     return NULL;
// }
//
// int main()
// {
//     FILE* stream = fopen("books.d", "r");
//
//     char line[1024];
//     while (fgets(line, 1024, stream))
//     {
//         char* tmp = strdup(line);
//         printf("Field 3 would be %s\n", getfield(tmp, 1));
//         // NOTE strtok clobbers tmp
//         free(tmp);
//     }
// }
//
// int main(){
//     printf("-----%.*s-----\n",sizeof("\n\0")-3,"\n\0");
// }
