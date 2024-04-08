#include <stdio.h>

int main(){
    char * name1 = "John Smith"; //This method creates a string which we can only use for reading.

    char name2[] = "John Smith";  //This notation is different because it allocates an array variable so we can manipulate it.
    /* name2 is the same as name3 */
    char name3[11] = "John Smith"; // The reason the length is 11 and not 10 is because the last spot is for the string termination (value).

    // strlen is used for finding the length of a string. For example: strlen(name).
    // strncmp is used to compare to strings, returning 0 if they are equal. For example strncmp(name, "John", 4.
    // strncat is used to append strings. For example: strncat(<dest>, <src>, <amount_of_chars>);

    char * name = "Nikhil";
    printf("%d\n",strlen(name));

    if (strncmp(name, "John", 4) == 0) {
        printf("Hello, John!\n");
    } else {
        printf("You are not John. Go away.\n");
    }

    char dest[20]="Hello";
    char src[20]="World";
    strncat(dest,src,3);
    printf("%s\n",dest);
    strncat(dest,src,20);
    printf("%s\n",dest);

}