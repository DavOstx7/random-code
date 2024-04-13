#include <iostream>
using namespace std;

int main(){
    cout << "Hello World!" << endl;
    cout << "\\ \"Hello\" World\n";
    cout << 4 + 20 << endl;
    int x = 5;
    cout << x + 3 / 3 << endl;

    //
    cout    <<"sup"
    << endl;
    //

    // int x; - error, it was already declared.

    int y; //automatically assigned 0 in this case, but assentaily it's giving a memory space for y,
    // and it could have garbage value in there if this location has been used before;
    cout << y << endl;
    y = 10;
    cout << "Here is x: " << x << " Here is y: " << y << endl;

    cout << "int 5 / int 2 = " << 5/2 << ", The modulus = " << 5 % 2 << ", double 5 / int 2 = " << 5.0 / 2 << endl;

    double t = 3.4;
    // if you want to round numbers, use int <var + 0.5>. if the var's fraction is 0.5, it will round up,
    // so if you want to round down use like a 0.49999.

    int tint = t + 0.5;
    cout << "t is equal to: " << t << ", t rounded up is equal to: " << tint << endl; // could have used (int) (t + 0.5).

    string p1 = "string1";
    string p2 = "string2";

    cout << p1 + p2 + "\n"; // you could add string together (also store it in a variable). 
    string p3 = "Hello - " + p1 + p2 + "\n";
    cout << p3 << "the length of p3 is: " << p3.length() << " And the 3 last letters are: " << p3.substr(p3.length() - 4, 3) << endl;

    // substr = <var-name>.substr(<start-pos>, <amount>)
    string s = "abcdef";
    cout << "result of s substr: " << s.substr(5, 3) << endl; //it just ignores the invalid indexes.

    // reference variables - alias.
    int &z = x; // z and x are the same var. if I change x it will change z and the opposite (both in the same memory location).
    return 0;
}