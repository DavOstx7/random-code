#include <stdio.h>
#include <string.h>

enum Today{Sun = 1, Mon = 2, Tue = 3, Wed = 4, Thu = 5, Fri = 6, Sat = 7};
// If we dont specifiy a value, it will go in 0, 1, 2 ...
// If we declared for example that Tue = 13, then Wed is gonna be equal to 14, and so forth.
// 2 or more variables can have the same value.
// we can also use define, but it's a pre-preprocessor directive,
// executed before the compiler sees the code, and therefore is not a language element of C itself.

// It's better to use enum.

#define NUM 15
#define NAME "DAVID"

// You can do: typedef enum Today Today; but sometimes it's better to see that it's an enum.

typedef enum{
    false = 0,
    true = 1,
} bool;

int main(){
    enum Today today = Fri;
    if (today == Fri || today == Sat){
        printf("Its the weekend! :D\n");
    } else {
        printf("It ain't the weekend D:\n");
    }

    char name[] = "DAVID";
    if(strcmp(name, NAME) == 0){
        printf("equal name. 1) %s 2) %s\n", name, NAME);
    } else {
        printf("not an equal name. 1) %s 2) %s\n", name, NAME);
    }

    int n = 3;
    if(n == NUM){
        printf("equal nums\n");
    } else {
        printf("not equal nums\n");
    }

    //When something is true, it returns 1 (usually), when something is false, it returns 0.
    // * It's better to use 0 as a comparision, because any number other than 0 mean true. and only 0 means false.
    // TIP: always check in the documentary what number represents what solution.
    /* for example */
    bool x = 5;

    if(x == true){ //this if only works for if x == 1, which is most of the times the case, but still better to use x == 0.

        printf("bad implementation --> x is true\n");
    } else {
        printf("bad implementation --> x is false\n");
    }

    x = 5 < 5;
    if(x == false){
        printf("good implementation x is false\n");
    } else {
        printf("good implementation --> x is true\n");
    }

    x = 3 > 1;
    if(!(x == false)){ //the same is if x == true, but we use the 0 to check it.
        printf("good implementation --> x is true\n");
    } else {
        printf("good implementation --> x is true\n");
    }
    return 1;   
}