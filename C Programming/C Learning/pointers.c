#include <stdio.h>

typedef struct pointers
{
    int x;
    int y;
} point;

typedef struct people
{
    char * name;
    int age;
} person;

void addone(int *n) {
    // n is a pointer here which point to a memory-adress outside the function scope
    (*n)++; // this will effectively increment the value of n
}

/*
void move(point * p) {
    (*p).x++;
    (*p).y++;
}
*/

void move(point*  p){
    p->x++;
    p->y++;
}

void ageup(person * p){
    p->age ++;
}

int main(){
    char * name = "John";
    /* This does 3 things: */
    // It allocates a local (stack) variable called name, which is a pointer to a single character.
    // It causes the string "John" to appear somewhere in the program memory (after it is compiled and executed, of course).
    // It initializes the name argument to point to where the J character resides at (which is followed by the rest of the string in the memory).

    printf("%c\n", *(name+1));

    /* define a local variable a */
    int a = 1;

    /* define a pointer variable, and point it to a (variable named 'a')using the & operator */
    int * pointer_to_a = &a;

    printf("The value a is %d\n", a);
    printf("The value of a is also %d\n", *pointer_to_a);

    /* let's change the variable a */
    a += 1;

    /* we just changed the variable again! */
    *pointer_to_a += 1;

    /* will print out 3 */
    printf("The value of a is now %d\n", a);

    int n = 10;
    int* pointer_to_n = &n;
    n++;
    (*pointer_to_n)++;
    printf("n before %d\n", n);
    addone(pointer_to_n);
    printf("n after %d\n", n);


    person bro;
    bro.name = "brobro"; bro.age = 13;
    printf("age before %d\n", bro.age);
    ageup(&bro);
    printf("age after %d\n", bro.age);

    char vowels[] = {'A', 'E', 'I', 'O', 'U'};
    // vowels, &vowels[0], and vowels + 0 all point to the same location //
    

    return 0;
}