#include <iostream>
#include "map"
#include <functional>
#include <typeinfo>

using namespace std;

typedef void (*HelloWorldMethod)(void);

struct HelloWorld {  
    map<string, function<void(void)>> test;

    HelloWorld() {
        this->test["hello"] = bind(&HelloWorld::printHello, this);
        this->test["world"] = bind(&HelloWorld::printWorld, this);
        cout << typeid(&HelloWorld::printHello);
    }

    void printHello() {
        cout << "hello" << endl;
    }

    void printWorld() {
        cout << "world" << endl;
    }
};

int func(float);

int (*fp1)(float) = &func; 
// equivalent to
int (*fp2)(float) = func;

int main() {
    HelloWorld c;
    c.test["hello"]();
    c.test["world"]();
    bool a = (int) fp1 == (int) fp2;
    cout << a;
}