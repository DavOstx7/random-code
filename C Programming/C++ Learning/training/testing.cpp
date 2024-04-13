#include <iostream>

using namespace std;

struct Test{
    int a;
    int b;

    Test(){
        cout << "init\n";
    }
    Test(const Test& other){
        cout << "copy init\n";
    }
};


int main(){
    struct Test t();
    cout << t.a;
}