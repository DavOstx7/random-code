#include <iostream>

using namespace std;

struct Student{
    string name;
    double average;
    char letterGrade;
};

int main(){

    Student boy;
    boy.name = "John", boy.average = 84.3, boy.letterGrade = 'A';
    Student girl = {.name = "Jenna", .average = 84.5, .letterGrade = 65};
    cout << girl.letterGrade << endl;

    struct HomeAddress{
        string streetName;
        int streetNumber;
    };

    // HomeAddress h = {10, "Name"};  - this will produce error.
    HomeAddress h = {"Name", 10};
    return 0;
}

