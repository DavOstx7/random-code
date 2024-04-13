#include <stdio.h>

int main(){
    /* this works, but the other option is better
    struct point { 
    int x;
    int y;
    };

    struct point p;
    p.x = 10;
    p.y = 5;

    printf("x = %d, y = %d\n", p.x, p.y); */

    typedef struct {
        int x;
        int y;
    } point;

    point p;
    p.x = 11, p.y = 6;
    printf("x = %d, y = %d\n", p.x, p.y);

    typedef struct {
        char * name;
        int age;
    } person;

    person jon;
    jon.name = "johnn";
    jon.age = 32;
    printf("name = %s, age = %d", jon.name, jon.age);
    return 0;


}