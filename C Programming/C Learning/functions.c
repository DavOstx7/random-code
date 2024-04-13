#include <stdio.h>

int foo(int bar) {
    /* do something */
    bar = bar * 2;
    return bar;
}

void printBig(int x); //better to declare, then later implement.

int main(){

    //  the power of functions is a bit limited in C.
    // 1) Functions receive either a fixed or variable amount of arguments.
    // 2) Functions can only return one value, or return no value.

    // In C, arguments are copied by value to functions, which means that we cannot change the arguments to affect their value outside of the function.
    int bar = 5;
    printf("bar is equal to %d\n", bar);

    int a = foo(bar);
    printf("bar is equal to %d\n", bar);
    printBig(13);
    return 0;
}

void printBig(int x){
    if(x > 10){
        printf("%d is big\n", x);
    }
}