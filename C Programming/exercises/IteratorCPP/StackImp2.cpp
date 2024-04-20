#include <iostream>
#include <cstring>
#include <chrono>
#include <ctime> 

using namespace std;

namespace Resources{
	size_t allocated = 0;
	size_t deallocated = 0;

	size_t GetCurrentAllocated(){
		return allocated - deallocated;
	}
}

void* operator new(size_t size){
	using namespace Resources;
	allocated+= size;
	return malloc(size);
}

void operator delete(void *ptr, size_t size){
	using namespace Resources;
	deallocated+=size;

	free(ptr);
}


struct Timer{
private:
	using Time = std::chrono::time_point<std::chrono::system_clock>;
	Time start;
	Time finish;
public:
	Timer(): start( std::chrono::system_clock::now()){
		cout << "[+] starting timer...\n";
	}


	~Timer(){
		finish =  std::chrono::system_clock::now();
		cout << "[-] finishing timer...\n";
		auto duration = finish - start;
		auto time = duration.count();
		cout << "Time took: " << time << endl;
	}

};
struct Entity{
	static int objects;
	int x;
	int y;
	int* z;
	int numOrder;
	Entity(): x(10), y(20) {
		numOrder = ++objects;
		z = new int;
		cout << "Constructed\n";
	}

	Entity(int x, int y): x(x), y(y) {
		numOrder = ++objects;
		z = new int;
		cout << "Constructed\n";
	}

	Entity(const Entity& other): x(other.x), y(other.y) {
		numOrder = ++objects;
		z = new int;
		memcpy(z, other.z, sizeof(int));
		cout << "Copy Constructor\n";
	}

	Entity(Entity&& tmp): x(tmp.x), y(tmp.y) {
		numOrder = ++objects;
		z = tmp.z;
		tmp.z = nullptr;

		cout << "Move Constructor\n";
	}

	Entity& operator=(const Entity& other){
		x = other.x;
		y = other.y;
		memcpy(z, other.z, sizeof(int));
		cout << "Copied operator!\n";
		return *this;
	}

	Entity& operator=(Entity&& tmp){
		if(this == &tmp) //can't move ourself to ourself.
			return *this;
		x = tmp.x;
		y = tmp.y;

		delete z; //avoid memory leak before re assigning our array to tmp's.
		z = tmp.z;
		tmp.z = nullptr;
		cout << "Moved operator!\n";
		return *this;
	}

	void Print(){
		cout << "x = " << x << " y = " << y << endl;
	}
	~Entity(){
		//cout << "Destroyed\n"; //this is too much spam
		delete z;

	}
};
int Entity::objects = 0;
template<typename T, int maxSize>
class Stack{
private:
	T s_Arr[maxSize];
	u_int current_size;

public:
	//I actually changed it so I deleted the objects before inserting (because it makes the array full of objects
	//but that causes double free(once when we call here the destructor, and another when out of scope).
	Stack(): current_size(0) {
		/*
		for (int i = 0; i < maxSize; ++i)
		{
			s_Arr[i].~T();
		}
		*/
	} 
	void Push(T& value){
		if(current_size >= maxSize){
			cout << "Stack full!\n";
			return;
		}
		s_Arr[current_size++] = value;
	}

	void Push(T&& tmpValue){
		if(current_size >= maxSize){
			cout << "Stack full!\n";
			return;
		}
		s_Arr[current_size++] = move(tmpValue);
	}

	template<typename ... Args>
	T& PushConstructor(Args&& ... args){
		if(current_size >= maxSize){
			cout << "Stack full! exiting\n";
			exit(1);
		}
		s_Arr[current_size] = T(forward<Args>(args) ...); //no need to use move(), because it's already creating a temporary.
		return s_Arr[current_size++];
	}
/*
	T& Pop(){ 
	//this means that if someone uses a refernce to this, they will reference the array at the position of the return.
	//IMO this is better than copying, because a stack is like a store.
	//The user should know not to create a reference to this return reference, and if he pops it to nothing it's more effecient than copying.
		if(current_size <= 0){
			cout << "Can't pop! stack is empty ... exiting\n";
			exit(1);
		}
		return s_Arr[--current_size];
	}
*/


	T&& Pop(){ 
		//this forces not to take references, but it does enable using rvalue references(&&).
		//this allows
		if(current_size <= 0){
			cout << "Can't pop! stack is empty ... exiting\n";
			exit(1);
		}
		return move(s_Arr[--current_size]);
	}




/* can't use manually destuctor on stack variables!!!!! REMEMEBER
	void PopDelete(){
		//this might be useful if we want to delete the object (we shouldn't use it after).
		if(current_size <= 0){
			cout << "Can't pop! stack is empty ... exiting\n";
			exit(1);
		}
		current_size--;
		cout << "CURRENT SIZE! " << current_size << endl;
		s_Arr[current_size].~T(); //this causes a double free! 
	}
*/
	u_int CurrentSize(){
		return current_size;
	}

	bool IsEmpty(){
		return current_size == 0;
	}

	void PrintStack(){
		u_int it = current_size - 1;
		while(it != - 1){
			cout << "| " << s_Arr[it--] << " |";
		}
		cout << endl;

	}

};
int main(){

	//T&&
	Stack<Entity, 5>s; //20 bytes
	s.PushConstructor(); 
	s.PushConstructor(); 
	s.PushConstructor();
	//now it's at 32. //12 deallocation because of the move.
	Timer t;

	cout << "~~~Poping entity into another entity reference\n";
	Entity&& x = s.Pop(); //this just uses the lcoation of the array it was popped from (nothing happens).

	cout << "~~~Poping entity into another entity (no reference)\n";
	Entity x1 = s.Pop(); //Calling move constructor - no new allocation: stealing the pointer from tmp and setting him to null.

	cout << "~~~Creating empty entity\n";
	Entity z; //Calling constructor - new allocation + 4 
	cout << "~~~Assigning a pop to the entity\n";
	z = s.Pop(); //Calling move operator - deleting our pointer //4 deallocation, and stealing the other's pointer, then setting him to null.
	

	cout << "Resources::: Allocated: " << Resources::allocated << " | Deallocated: " << Resources::deallocated << " | Currently used: " << Resources::GetCurrentAllocated() << endl;
	return 0;
}