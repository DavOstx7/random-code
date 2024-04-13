#include <iostream>

using namespace std;

//A1 has to functions - it's valid because they have different amount of variables (called function overloading).
int A1(int x){
    return x;
}

int A1(int x, int y){
    return x + y;
}

/*
double A1(int){
    return x;
}
*/

// increaments value of x by returning it.
int A2(int x){
    x++;
    return x;
}

// increaments value of x by reference.
void A3(int &x){
    x++;
}

// using a pointer to x to increament its value.
void A4(int *x){
    (*x)++;
}
// using a double pointer to change a pointer's value.
void A5(int **x, int *y){
    *x = y;
}

// using a reference to change a pointer.
void A6(int*& x, int *y){
    x = y;
}
int main(){
    
    int x = 2;
    int y = 10;
    cout << A1(x) << endl;
    cout << A1(x, y) << endl;
    cout << A2(x) << endl;
    A3(x);
    cout << x << endl;
    A4(&x);
    cout << x << endl;

    int *a;
    cout << a << endl;
    int *b;
    A5(&a, b);
    cout << a << endl;
    int *c;
    A6(a, c);
    cout << a << endl;
    return 0;
}
