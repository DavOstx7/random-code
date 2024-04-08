#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){

    //writing to file
    FILE *fptr = fopen("test.txt", "w");
    fprintf(fptr, "Hello World\n");
    fflush(fptr); //flush what's in the buffer to the pointer of the file.
    // we could also not use fflush, because when we close the file we automatically flush everything to there. but it's better to use it.
    fclose(fptr);

    //reading from file char by char    
    printf("Reading first time:\n");
    fptr = fopen("test.txt", "r");
    char c;
    while((c = fgetc(fptr)) != EOF){
        printf("%c", c);
    }
    fclose(fptr);

    //appending to file
    fptr = fopen("test.txt", "a");
    fprintf(fptr, "New Line\n");
    fflush(fptr); //flush what's in the buffer to the pointer of the file.
    // we could also not use fflush, because when we close the file we automatically flush everything to there. but it's better to use it.
    fclose(fptr);

    //reading line by line
    printf("Reading second time:\n");
    fptr = fopen("test.txt", "r");
    char current_line[500];
    while(fgets(current_line, 500, fptr) != NULL){
        printf("%s", current_line);
    }
    fclose(fptr);

    //error handling
    FILE *fp = fopen("noneexisting.txt", "r");
    if(fp == NULL){
        perror("Error: "); //perror prints what is the error
        printf("Error code %d\n", errno); //errno is the error number
    } else{
        char c;
        while((c = fgetc(fp)) != EOF){
            printf("%c", c);
        }
        fclose(fp);
    }

    int a = 5;
    int b = 2;
    /* a / b gives out an error */
    if( b == 0){
        exit(EXIT_FAILURE);
    }
    printf("result of division = %d\n", a / b);
    return 0;
}