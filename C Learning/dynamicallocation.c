#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char * name;
    int age;
} person;

int main(){
    person * myperson = (person *) malloc(sizeof(person));
    /*
    This tells the compiler that we want to dynamically allocate just enough to hold a person struct in memory
    and then return a pointer of type person to the newly allocated data.

    To access the person's members, we can use the -> notation:
    */
    myperson-> name = "John";
    myperson-> age = 30;

    free(myperson);
    /*
    Note that the free does not delete the myperson variable itself, it simply releases the data that it points to.
    The myperson variable will still point to somewhere in the memory, but after calling myperson
    we are not allowed to access that area anymore. We must not use that pointer again until we allocate new data using it.
    */


   // Allocate memory to store five characters
    int n = 5;
    char *pvowels = (char *) malloc(n * sizeof(char));
    int i;

    pvowels[0] = 'A';
    pvowels[1] = 'E';
    *(pvowels + 2) = 'I';
    pvowels[3] = 'O';
    *(pvowels + 4) = 'U';

    for (i = 0; i < n; i++) {
        printf("%c ", pvowels[i]);
    }

    printf("\n");
    free(pvowels);
    // remember that pvowels actually is a pointer. Pointers and arrays, in general, are not the same thing //

    /*
    int var = 789;
  
    // pointer for var
    int *ptr2;
  
    // double pointer for ptr2
    int **ptr1;
  
    // storing address of var in ptr2
    ptr2 = &var;
      
    // Storing address of ptr2 in ptr1
    ptr1 = &ptr2;
      
    // Displaying value of var using
    // both single and double pointers
    printf("Value of var = %d\n", var );
    printf("Value of var using single pointer = %d\n", *ptr2 );
    printf("Value of var using double pointer = %d\n", **ptr1);

    result:
    Value of var = 789
    Value of var using single pointer = 789
    Value of var using double pointer = 789
    */
    int nrows = 2;
    int ncols = 5;
    int j; i = 0;

    // Allocate memory for nrows pointers
    char **ppvowels = (char **) malloc(nrows * sizeof(char *));

    // For each row, allocate memory for ncols elements
    ppvowels[0] = (char *) malloc(ncols * sizeof(char));
    ppvowels[1] = (char *) malloc(ncols * sizeof(char));

    ppvowels[0][0] = 'A';
    ppvowels[0][1] = 'E';
    ppvowels[0][2] = 'I';
    ppvowels[0][3] = 'O';
    ppvowels[0][4] = 'U';

    ppvowels[1][0] = 'a';
    ppvowels[1][1] = 'e';
    ppvowels[1][2] = 'i';
    ppvowels[1][3] = 'o';
    ppvowels[1][4] = 'u';

    for (i = 0; i < nrows; i++) {
        for(j = 0; j < ncols; j++) {
            printf("%c ", ppvowels[i][j]);
        }

        printf("\n");
    }

    // Free individual rows
    free(ppvowels[0]);
    free(ppvowels[1]);

    // Free the top-level pointer
    free(ppvowels);

    return 0;
}