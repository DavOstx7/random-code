#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union intParts {
  int theInt;
  char bytes[sizeof(int)];
};

/*
struct operator {
    int intNum;
    float floatNum;
    int type;
    double doubleNum;
};
*/
// instead of the code above, we can use the code below to save memory // 

/*
struct operator {
    int type;
    union {
      int intNum;
      float floatNum;
      double doubleNum;
    } types;
};
An even better option is to use the code below. because then we can use <operator-obj>.intNum instead of <operator-obj>.types.intNum
*/

typedef struct operator {
    int type;
    union {
      int intNum;
      float floatNum;
      double doubleNum;
    };
} operator;

union Coins {
    struct {
        int quarter;
        int dime;
        int nickel;
        int penny;
    }; // anonymous struct acts the same way as an anonymous union, members are on the outer container
    int coins[4];
};

struct coin1{
    int quarter;
    int dime;
    int nickel;
    int penny;
};

typedef union IntChar {
        char chars[21];
        int nums[6]; 
} IntChar;

int main(){
    int arr[3] = {1,2,3};

    /*
    C Unions are essentially the same as C Structures,
    except that instead of containing multiple variables each with their own memory,
    a Union allows for multiple variables share the same memory.
    */   
    union intParts parts;
    parts.theInt = 5968145; // arbitrary number > 255 (1 byte)

    printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n",
        parts.theInt, parts.bytes[0], parts.bytes[1], parts.bytes[2], parts.bytes[3]);
    /*
    // vs

    int theInt = parts.theInt;
    printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n",
    theInt, *((char*)&theInt+0), *((char*)&theInt+1), *((char*)&theInt+2), *((char*)&theInt+3));

    // or with array syntax which can be a tiny bit nicer sometimes

    printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n",
    theInt, ((char*)&theInt)[0], ((char*)&theInt)[1], ((char*)&theInt)[2], ((char*)&theInt)[3]);
    */

    operator op;
    op.type = 0; // int, probably better as an enum or macro constant
    op.intNum = 352;
    printf("%d\n", op.doubleNum);

    /*
    union Coins change;
    printf("%d\n", change);
    for(int i = 0; i < sizeof(change) / sizeof(int); ++i)
    {
        scanf("%i", change.coins + i); // BAD code! input is always suspect!
    }
    printf("There are %i quarters, %i dimes, %i nickels, and %i pennies\n",
    change.quarter, change.dime, change.nickel, change.penny);
    */

    // initializer lists like this are assigned to the first member of the union/struct!
    // There are 6 ints here so...
    printf("Starting Exercise:\n");
    IntChar intCharacters = {.nums = {1853169737, 1936876900, 1684955508, 1768838432, 561213039, 0}};
    
    /* testing code */
    printf("[");
    // only go to 18 because 1 byte is for the terminating 0 and we don't print the last in the loop
    for(int i = 0; i < 19; ++i)
        printf("%c, ", intCharacters.chars[i]);
    printf("%c]\n", intCharacters.chars[19]);

    printf("%s\n", intCharacters.chars);

    return 0;
}