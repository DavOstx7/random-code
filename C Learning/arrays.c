#include <stdio.h>

int main(){
    int numbers[10];
    /*  ~~~one-dimensional~~~ */
    // populate the array //
    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    numbers[3] = 40;
    numbers[4] = 50;
    numbers[5] = 55;
    numbers[6] = 60;

    printf("The number in the 6th index in the array is %d\n", numbers[6]); 
    printf("The number in the 9th index in the array is %d\n", numbers[9]); //automatically assigns zero's, but it's better to place zero's there.

    /*  ~~~multi-dimensional~~~ */
    // syntax: <type> <name> [size1][size2]...[sizeN]; //
    int foo[1][2][3];
    char vowels1 [1][5] = { {'a', 'e', 'i', 'o', 'u'} }; //1 = number of rows, 2 = number of colums

    //the compiler is smart enough to understand this too //
    char vowels2 [][5] = { 
    {'L', 'E', 'I', 'O', 'U'},
    {'a', 'e', 'i', 'o', 'u'}
    };
   
    char vowels3 [][3] = {'a', 'a', 'a', 'b', 'M'};
    printf("%c\n", vowels3[1][2]); // this will print undefined value which in this case is ''
    printf("%c\n", vowels3[1][1]); // this will print M
    printf("%c\n", vowels3[2][0]); // this is going to cause sliding to the vowels2[0][0] memory ('L').

    // the compiler can't understand this // 
    // char vowels3 [2][] = { 
    // {'A', 'E', 'I'},
    // {'a', 'e', 'i'}
    // };

     // both of the arrays below are equal //
    int nums1[2][3] = {1,2,3,4,5,6};
    int nums2[2][3] = {
        {1,2,3},
        {4,5,6}
    };

    // this is not allowed.
    // int num3[][2];

    // this is allowed.
    int nums3[][2] = {1};
    int nums4[][2] = {1,2,3};
    printf("%d and %d\n", nums3[0][0], nums3[0][1]); // print 1 and <undefined>
    printf("%d and %d and %d\n", nums4[0][0], nums3[1][0], nums3[1][1]); // print 1 and 1 and <undefined>
    int nums5[2][2];
    printf("%d and %d and %d\n", nums5[0][0], nums5[1][0], nums5[1][1]); // <undefinded> 3 times
    int nums6[2][2] = {1}; // set the first one to 1, and all of the others to 0. (if I used 0 instead, everything would get the value 0)
    printf("%d and %d and %d", nums6[0][0], nums6[0][1], nums6[1][1], nums6[3][1]); // will print 1 and 0 and 0
    return 0;
}