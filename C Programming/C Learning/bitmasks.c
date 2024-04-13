#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Finish initializing the flags */

const short FLAG_ON          = 1 << 0; // 1  (0x01)
const short FLAG_MOVEMENT    = 1 << 1; // 2  (0x02)
const short FLAG_TRANSPARENT = 1 << 2; // 4  (0x04)
const short FLAG_ALIVE       = 1 << 3;
const short FLAG_BROKEN      = 1 << 4;
const short FLAG_EDIBLE      = 1 << 5; // 32 (0x20)

void bin(unsigned n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
}

int main(){
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    short attributes = 0;
    /* Set the attributes ON, TRANSPARENT, and BROKEN */

    attributes |= (FLAG_ON + FLAG_TRANSPARENT + FLAG_BROKEN); //This works but the other solution is more safe imo
    assert(attributes == (FLAG_ON | FLAG_TRANSPARENT | FLAG_BROKEN)); //The | part in the insert is connecting the bits like |=

    /* Modify (set/clear/toggle) so the only attributes are ON and ALIVE */

    attributes &= ~(FLAG_TRANSPARENT + FLAG_BROKEN);
    attributes |= FLAG_ALIVE;
    assert(attributes == (FLAG_ON | FLAG_ALIVE));

    /* Check if the ALIVE flag is set */
    assert(attributes & FLAG_ALIVE);

    /* Check if the BROKEN flag is not set */
    //THIS IS FALSE!!! assert(attributes & ~FLAG_BROKEN); 
    assert(!(attributes & FLAG_BROKEN)); //if the number is 0 (false) it turns it to 1(true), if the number is >0 it turns it to 0.
    /* Modify so only the EDIBLE attribute is set */

    attributes ^= attributes; //reseting.
    attributes |= FLAG_EDIBLE;
    assert(attributes == FLAG_EDIBLE);

    printf("Done!");
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



    /* Set the attributes ON, TRANSPARENT, and BROKEN */
    attributes = 0;
    attributes |= FLAG_ON;
    attributes |= FLAG_TRANSPARENT;
    attributes |= FLAG_BROKEN;
    // possible solution(s):
    // attributes |= FLAG_ON | FLAG_TRANSPARENT | FLAG_BROKEN;
    // attributes = FLAG_ON | FLAG_TRANSPARENT | FLAG_BROKEN;

    assert(attributes == (FLAG_ON | FLAG_TRANSPARENT | FLAG_BROKEN));

    /* Modify (set/clear/toggle) so the only attributes are ON and ALIVE */
    attributes &= ~FLAG_TRANSPARENT;
    // possible: attributes ^= FLAG_TRANSPARENT;
    attributes ^= FLAG_BROKEN;
    // possible: attributes &= ~FLAG_BROKEN;
    attributes |= FLAG_ALIVE;

    assert(attributes == (FLAG_ON | FLAG_ALIVE));

    /* Check if the ALIVE flag is set */
    assert(attributes & FLAG_ALIVE);

    /* Check if the BROKEN flag is not set */
    assert(!(attributes & FLAG_BROKEN));

    /* Modify so only the EDIBLE attribute is set */
    attributes = FLAG_EDIBLE;

    assert(attributes == FLAG_EDIBLE);

    printf("Done!");

/*
~~~ Setting bit n ~~~

Setting bit n is as simple as ORing the value of the storage variable with the value 2^n.

storage |= 1 << n;

As an example, here is the setting of bit 3 where storage is a char (8 bits):

01000010 OR 00001000 == 01001010

The 2^n logic places the '1' value at the proper bit in the mask itself, allowing access to that same bit in the storage variable.

~~~ Clearing bit n ~~~

Clearing bit n is the result of ANDing the value of the storage variable with the inverse (NOT) of the value 2^n:

storage &= ~(1 << n);

Here's the example again:

01001010 AND 11110111 == 01000010

~~~ Flipping bit n ~~~
Flipping bit n is the result of XORing the value of the storage variable with 2^n:

storage ^= 1 << n;

01000010 01001010 XOR XOR 00001000 00001000 == == 01001010 01000010

~~~ Checking bit n ~~~
Checking a bit is ANDing the value of 2^n with the bit storage:

bit = storage & (1 << n);

01000010 01001010 AND AND 00001000 00001000 == == 00000000 00001000
    */
}