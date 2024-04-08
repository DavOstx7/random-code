#include <iostream>

using namespace std;

struct Child{
    virtual void print(){
        cout << "ima child\n";
    }
};

struct Parent: Child{
    void print() override{
        cout << "imma parrent\n";
    }
};

struct Weird{
    Parent p;
};

void TestObj(Child* p){
    p->print();
}

int main(){

    Parent p;
    Parent* p2 = &p;
    (*p2).print();
    p2->print();
    Weird w;
    w.p.print();
    p2 = &w.p;
    p2->print();
    return 0;
}