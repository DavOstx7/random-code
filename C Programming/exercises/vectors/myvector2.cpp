#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define EqualType(x, y) typeid(x) == typeid(y)

#define _debugg 0
#if _debugg == 1
	#define newArr(type, max) new type[max];\
	cout << "[+] allocated an array of size: " << sizeof(type) * (max) << " bytes, at line number: " << __LINE__ << endl

	#define delArr(array, max) delete []array;\
	cout << "[-] deallocated an array of size: " << sizeof(decltype(*array)) * (max) << " bytes, at line number: " << __LINE__ << endl
#else
	#define newArr(type, max) new type[max]
	#define delArr(array, max) delete []array
#endif

template <typename T1 = char, typename T2 = T1, typename T3 = T2>
class MyVector{
private:
	enum class IsValid {unvalid = 0, valid = 1} v1, v2, v3;
	int reserve;
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
	MyVector(int NumOfTypes, int reserve = 2)
	: count1(0), count2(0), count3(0), reserve(reserve), v1(IsValid::unvalid), v2(IsValid::unvalid), v3(IsValid::unvalid)
	{
		if(NumOfTypes < 1 || NumOfTypes > 3){
			cout << "Bad input - needs to be between 1 and 3\n";
			return; 
		}
		else{
			max1 = reserve;
			arr1 = newArr(T1, max1); 
			v1 = IsValid::valid;
		}
		if(NumOfTypes < 2){
			return;
		}
		else{
			max2 = reserve;
			arr2 = newArr(T2, max2); 
			v2 = IsValid::valid;
		}
		if(NumOfTypes < 3){
			return;
		}
		else{
			max3 = reserve;
			arr3 = newArr(T3, max3); 
			v3 = IsValid::valid;
		}
	}

	~MyVector(){
		if(v1 == IsValid::valid)
		{
			delArr(arr1, max1);
		}
		if(v2 == IsValid::valid)
		{
			delArr(arr2, max2);
		}
		if(v3 == IsValid::valid)
		{
			delArr(arr3, max3);
		}
	}

	void push1(T1 value){
		if(EqualType(value, void) || v1 == IsValid::unvalid){
			cout << "Cant push!\n";
			return;
		}
		if(v1 == IsValid::valid){
			if(count1 < max1){
				arr1[count1++] = value;
				return;
			}
			T1* n_t1 = newArr(T1, max1 + reserve);
			memcpy(n_t1, arr1, sizeof(T1) * max1);
			n_t1[count1++] = value;
			max1 += reserve;
			delArr(arr1, max1);
			arr1 = n_t1;
		}
	}

	T1 pop1(){
		if(v1 == IsValid::unvalid){
			cout << "Cant pop!\n";
			return 0;
		}
		T1 tmp = arr1[--count1];
		arr1[count1] = 0;
		return tmp;
	}

	void push2(T2 value){
		if(EqualType(value, void) || v2 == IsValid::unvalid){
			cout << "Cant push!\n";
			return;
		}
		if(v2 == IsValid::valid){
			if(count2 < max2){
				arr2[count2++] = value;
				return;
			}
			T2* n_t2 = newArr(T2, max2 + reserve);
			memcpy(n_t2, arr2, sizeof(T2) * max2);
			n_t2[count2++] = value;
			max2 += reserve;
			delArr(arr2, max2);
			arr2 = n_t2;
			return;
		}
	}

	T2 pop2(){
		if(v2 == IsValid::unvalid){
			cout << "Cant pop!\n";
			return 0;
		}
		T2 tmp = arr2[--count2]; //same as T2 tmp = arr[count2-1]; arr[count2-1] = 0, count--;
		arr2[count2] = 0;
		return tmp;
	}

	void push3(T3 value){
		if(EqualType(value, void) || v3 == IsValid::unvalid){
			cout << "Cant push!\n";
			return;
		}
		if(v3 == IsValid::valid){
			if(count3 < max3){
				arr3[count3++] = value;
				return;
			}
			T3* n_t3 = newArr(T3, max3 + reserve);
			memcpy(n_t3, arr3, sizeof(T3) * max3);
			n_t3[count3++] = value;
			max3 += reserve;
			delArr(arr3, max3);
			arr3 = n_t3;
			return;
		}
	}

	T3 pop3(){
		if(v3 == IsValid::unvalid){
			cout << "Cant pop!\n";
			return 0;
		}
		T3 tmp = arr3[--count3];
		arr3[count3] = 0;
		return tmp;
	}
	void PrintInstance(){
		if(v1 == IsValid::valid){
			cout << "arr1: ";
			for (int i = 0; i < count1; ++i)
			{
				cout << arr1[i] << " ";
			}
			cout << endl;
		}
		if(v2 == IsValid::valid){
			cout << "arr2: ";
			for (int i = 0; i < count2; ++i)
			{
				cout << this->arr2[i] << " ";
			}
			cout << endl;
		}
		if(v3 == IsValid::valid){
			cout << "arr3: ";
			for (int i = 0; i < count3; ++i)
			{
				cout << this->arr3[i] << " ";
			}
			cout << endl;
		}
	}
};
int main(){

	string b = "hey";
	MyVector<const char*, int> v(2);
	//v.push<string>(b);
	v.push1("hdsadada");
	v.push1("hedsad");
	v.push1("hedsad");
	v.push1("hedsad");
	v.push1("hedsad");
	v.push1("hedsad");
	v.push1("hedsad");
	
	v.push2(5);
	v.push2(12);
	v.push2(2);
	v.push2(4);
	v.push2(31);

	v.push3(31);
	v.push3(31);
	v.push3(31);

	/*
	
	*/
	v.PrintInstance();
	v.pop2();
	v.pop2();
	cout << v.pop1() << endl;
	v.PrintInstance();


	return 0;
}