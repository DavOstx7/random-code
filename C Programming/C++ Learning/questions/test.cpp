#include <iostream>
#include "map"

using namespace std;

typedef void (*HelloWorldMethod)(void);


map<string, HelloWorldMethod> test;

struct HelloWorld {  
    void printHello() {
        cout << "hello" << endl;
    }

    void printWorld() {
        cout << "world" << endl;
    }
};

