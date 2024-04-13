#include <iostream>

using namespace std;

int main(){
    string a;
    cout << "Please enter a string: ";
    cin >> a;
    cout << "Here is what you inputed: " << a << endl;

    int b = 10;
    cout << "Please enter a number: ";
    cin >> b; //If a bad input is given, a NULL value will be assigned (0).
    cout << "Here is what you inputed: " << b << endl;

    cout << "Please enter 3 numbers:\n"; // We can seperate the numbers by either space or enter (either a then enter then b..., or a b c)
    int c, d, e;
    cin >> c >> d >> e;
    cout << "The sum of these numbers is: " << c + d + e << endl;

    //example for good use of do-while loop.

    cout << "Please Enter Positive number" << endl;
    int value;
    do {
        cin >> value;
    } while (value < 0);
    cout << "Your positive number is: " << value << endl;

    return 0;

}