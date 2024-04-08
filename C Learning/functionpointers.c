#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void someFunction(int arg)
{
    printf("This is someFunction being called and arg is: %d\n", arg);
    printf("Whoops leaving the function now!\n");
}

int compare(const void* left, const void* right)
{
    return (*(int*)right - *(int*)left);
    // go back to ref if this seems complicated: http://www.cplusplus.com/reference/cstdlib/qsort/
}

void f1(int var)
{
        printf("this is f1 and var is: %d\n", var);
}

void f2(int var)
{
        printf("this is f2 and var is: %d\n", var);
}

void f3(int var)
{
        printf("this is f3 and var is: %d\n", var);
}

int main(){
    /*
    SYNTAX: void (*pf)(int);
    void is the return type of that function.
    *pf is the pointer to a function.
    int is the argument type of that function.
    TIPS:
    BETTER SYNTAX ---> <return-type-of-function> (*<name-of-pointer>)(<variable-types>)
    <type> (*pf)(<type>) = &<function> is equal to <type> (*pf)(<type>) = <function>
    (*pf)(<variables>) is equal to (pf)(<variable>) and is equal to pf(<variable)>;
    */
    void (*pf)(int);
    pf = &someFunction;
    printf("[+] We're about to call someFunction() using a pointer!\n");
    (*pf)(5);
    printf("[+] Wow that was cool. Back to main now!\n\n");

    int (*cmp) (const void* , const void*) = compare;
    int iarray[] = {1,2,3,4,5,6,7,8,9};
    qsort(iarray, sizeof(iarray)/sizeof(*iarray), sizeof(*iarray), cmp);
    int c = 0;
    while (c < sizeof(iarray)/sizeof(*iarray))
    {
        printf("%d \t", iarray[c]);
        c++;
    }
    printf("\n");
    // The usefulness of the function pointer is sorting function is that we can define the comparision,
    // so it will sort according to what we need (this reduces coding of if/else/case).
    // for example right now the function is sorting on a down order, but if we change the compare function to do left - right,
    // the sorting will be on an up order.

    // Another use for it may be an array of functions or some like that.

    void (*p[])(int) = {f1, f2, f3};

		int m = 0;
		while(m < 3)
		{
			p[m](m);
			++m;
		}
    return 0;
}