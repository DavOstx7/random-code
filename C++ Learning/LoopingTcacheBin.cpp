#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long int* p1 = (unsigned long int *) malloc(10);
    unsigned long int* p2 = (unsigned long int *) malloc(10);
    unsigned long int* p3 = (unsigned long int *) malloc(10);
    
    free(p1);
    free(p2);
    free(p3);
    // p3 --> p2 --> p1 --> null;
    // I like to look at it like this tho: null <-- p1 <-- p2 <-- p3;
    unsigned long int* x = p3;
    while((void*)(*x) != NULL){
        x = (unsigned long int*)(*x);
    }
    
    printf("%p %p", p1, x);
    return 0;
}


/* Here Is A Code That Shows The Nodes In The CLib Tcache.

#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long int* p1 = (unsigned long int *) malloc(10);
    unsigned long int* p2 = (unsigned long int *) malloc(10);
    unsigned long int* p3 = (unsigned long int *) malloc(10);
    
    free(p1);
    free(p2);
    free(p3);
    // head --> p3 --> p2 --> p1 --> null (tail);
    
    unsigned long int* x = p3;
    printf("head --> ");
    while(x != NULL){
        printf("%p --> ", x);
        x = (unsigned long int*)(*x);
    }
    printf("null (tail)\n");
    // printf("%p %p", p1, x);
    return 0;
}

*/