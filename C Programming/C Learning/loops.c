#include <stdio.h>

int main(){

    for (int i = 0; i < 10; i++) {
    printf("%d ", i);
    }
    printf("\n");

    int i = 5;
    printf("i = %d\n", i);
    for (i; i < 10; i++) {
    printf("%d ", i);
    }
    printf("\n");

    for (int i = i; i < 8; i++) {
    printf("%d ", i);
    }
    printf("\n");

    printf("i = %d\n", i);

    int array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // could also use this.
    int sum = 0;
    i = 0;

    for (i = 0; i < 10; i++) {
        sum += array[i];
    }

    /* sum now contains a[0] + a[1] + ... + a[9] */
    printf("Sum of the array is %d\n", sum);


    int n = 0;
    while (n < 10) {
        printf("%d ", n);
        n++;
    }
    printf("\n");

    n = 0;
    while (1) {
        if (n == 10) {
            break;
        }
        printf("%d ", n);
        n++;
    }
    printf("\n");
    n = -1;
    while (n < 10) {
        n++;
        /* check that n is odd */
        if (n % 2 == 1) {
            /* go back to the start of the while block */
            continue;
        }

        /* we reach this code only if n is even */
        printf("The number %d is even.\n", n);
       
    }
    printf("finished!\n");
    return 0;
}