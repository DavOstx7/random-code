#include <iostream>
#include <cmath>

using namespace std;

int main(){

    cout << "The root of 9.5 is: " << sqrt(9.5) << endl;
    cout << "5 to the power of 3 is: " << pow(5, 3) << endl;

    cout << "The root to the power of 4 of 625 is: " << pow(625, 1.0/4) << endl; //this is not accurate with large numbers.

    return 0;
}