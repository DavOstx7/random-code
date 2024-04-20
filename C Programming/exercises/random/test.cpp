#include <iostream>
using namespace std;

void test(auto x){
	cout << x;
}
int main(){
	test(5);
}