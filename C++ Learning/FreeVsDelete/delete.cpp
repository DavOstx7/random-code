#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;



int main(){
    unsigned long int *pa = new long unsigned int;
    unsigned long int *pb = new long unsigned int;
    cout << "[1] before free" << endl; 
    cout << "pa: " << pa << " pb: " << pb  << endl;
    delete pa;
    delete pb;
    cout << "[1] after free:" << endl;
    cout << "pa" << " has the value of: " << (unsigned long int *) (*pa);
    cout << " pb" << " has the value of: " << (unsigned long int *) (*pb) << endl;
    unsigned long int *pc = new long unsigned int;
    unsigned long int *pd = new long unsigned int;
    cout << "[2] before free:" << endl;
    cout << "pc: " << pc << " pd: " << pd  << endl;
    delete pc;
    delete pd;
    cout << "[2] after free:" << endl;
    cout << "pc" << " has the value of: " << (unsigned long int *) (*pc);
    cout << " pd" << " has the value of: " << (unsigned long int *) (*pd) << endl;
    unsigned long int *p1 = new unsigned long int;
    unsigned long int *p2 = new unsigned long int;
    unsigned long int *p3 = new long unsigned int;
    unsigned long int *p4 = new long unsigned int;
    cout << "[3] before free:" << endl;
    cout << "p1: " << p1 << " p2: " << p2 << " p3: " << p3 << " p4: " << p4 << endl;
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    cout << "[3] after free:" << endl;
    cout << "*p1: " << (unsigned long int *) (*p1) << " *p2: " << (unsigned long int *) (*p1);
    cout << " *p3: " << (unsigned long int *) (*p3) << " *p4: " << (unsigned long int *) (*p4) << endl;
    cout << "\n\n\n";

    unsigned long int *x1 = new long unsigned int;
    cout << "before: x1 = " << x1 << endl;
    delete x1;
    cout << "after: *x1 = " << (unsigned long int *) (*x1) << endl;
    unsigned long int *x2 = new long unsigned int;
    cout << "before: x2 = " << x2 << endl;
    delete x2;
    cout << "after: *x2 = " << (unsigned long int *) (*x2) << " (*x1 = " << (unsigned long int *) (*x1) << ")" << endl;

}   
