#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define EqualType(x, y) typeid(x) == typeid(y)
#define _debug OFF
#if _debugg == ON
	#define newArr(type, amount) new type[amount];\
	cout << "allocated an array of size: " << sizeof(type) * amount << " at line number: " << __LINE__ << endl
#else
	#define newArr(type, amount) new type[amount]
#endif

template <typename T1 = void, typename T2 = void, typename T3 = void>
class MyVector{
private:
	unsigned int reserve;
	T1* arr1;
	int count1;
	int max1;
	T2* arr2;
	int count2;
	int max2;
	T3* arr3;
	int count3;
	int max3;

public:
	MyVector(unsigned int reserve = 3)
	: count1(0), count2(0), count3(0), reserve(reserve)
	{
		if(EqualType(T1, void)){
			arr1 = new T1[0]; 
		}
		else{
			max1 = reserve;
			arr1 = new T1[max1]; 
		}
		if(EqualType(T2, void)){
			arr2 = new T2[0]; 
		}
		else{
			max2 = reserve;
			arr2 = new T2[max2]; 
		}
		if(EqualType(T3, void)){
			arr3 = new T3[0]; 
		}
		else{
			max3 = reserve;
			arr3 = new T3[max3]; 
		}
	}

	~MyVector(){
		delete []arr1;
		delete []arr2;
		delete []arr3;
	}

	template<typename T>
	void push(T value){
		if(EqualType(T, T1)){
			if(count1 < max1){
				arr1[count1++] = value;
				return;
			}
			T1* n_t1 = new T1[max1 + reserve];
			memcpy(n_t1, arr1, sizeof(T) * max1);
			n_t1[count1++] = value;
			max1 += reserve;
			delete arr1;
			arr1 = n_t1;
			return;
		}

		if(EqualType(T, T2)){
			if(count2 < max2){
				arr2[count2++] = value;
				return;
			}
			T2* n_t2 = new T2[max2 + reserve];
			memcpy(n_t2, arr2, sizeof(T) * max2);
			n_t2[count2++] = value;
			max2 += reserve;
			delete arr2;
			arr2 = n_t2;
			return;
		}

		if(EqualType(T, T3)){
			if(count3 < max3){
				arr3[count3++] = value;
				return;
			}
			T3* n_t3 = new T3[max3 + reserve];
			memcpy(n_t3, arr3, sizeof(T) * max3);
			n_t3[count3++] = value;
			max3 += reserve;
			delete arr3;
			arr3 = n_t3;
			return;
		}

		cout << "The type you tried to push is none existed in this object" << endl;

	}

	void PrintInstance(){
		cout << "arr1: ";
		for (int i = 0; i < count1; ++i)
		{
			cout << arr1[i] << " ";
		}
		cout << endl;

		cout << "arr2: ";
		for (int i = 0; i < count2; ++i)
		{
			cout << this->arr2[i] << " ";
		}
		cout << endl;

		cout << "arr3: ";
		for (int i = 0; i < count3; ++i)
		{
			cout << this->arr3[i] << " ";
		}
		cout << endl;
	}
};
int main(){

	MyVector<int, string, char> v(3);
	v.push<int>(5);
	v.push<int>(12);
	v.push<int>(2);
	v.push<int>(4);
	v.push<int>(31);
	v.push<char>('c');
	v.push<char>('m');
	v.push<char>('}');
	v.push<char>('*');
	v.PrintInstance();


	return 0;
}