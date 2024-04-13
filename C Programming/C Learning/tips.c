#include <stdio.h>
#include <stdlib.h>

void superFree(void **pptr) //this function helps prevent UAF vulnerability (use-after-free)//
{
    // If the address of the pointer is NULL or
    // the pointer itself is already NULL, do
    // nothing.
 
    if (pptr && *pptr)
    {
        free(*pptr);
        *pptr = NULL; //the pointer will point to 0, which points to nothing.
    }
}
 
// ...
 
// Then, when we want to free a block of allocated memory,
// pointed to by the p pointer variable, we can say:
 
int main(){

    return 0;
}