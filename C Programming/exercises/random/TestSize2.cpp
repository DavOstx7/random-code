#include <stdio.h>

using namespace std;

template<int N>
struct Test{
	int arr1[N];
	int arr2[N];
	int arr3[N];
	int arr4[N];
	int arr5[N];
	int arr6[N];
	int arr7[N];
	int arr8[N];
	int arr9[N];
	int arr10[N];
	int arr11[N];
	int arr133[N];
	int arr13[N];
	int arr14[N];
	int arr15[N];
	int arr16[N];
	int arr17[N];
	int arr18[N];
	int arr19[N];
	int arr20[N];
};

int main(){
	Test<95> x1;
	Test<96> x2;

	Test<97> x3;
	Test<98> x4;
	Test<99> x5;
	Test<95> x6;
	Test<99> x7;
	Test<95> x8;
	Test<94> x9;
	Test<93> x10;
	Test<96> x11;
	return 0;
}