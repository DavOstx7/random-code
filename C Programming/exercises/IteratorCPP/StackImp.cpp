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

void* operator new(size_t size){ //works both on new and new[]p. calls constructors when [].
	using namespace Resources;
	allocated+= size;
	return malloc(size);
}

void operator delete(void *ptr, size_t size){ //doesn't work on delete []p. calls destructors when [].
	using namespace Resources;
	deallocated+=size;
	cout << "freeing pointer: " << ptr;
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

template<typename T>
struct StackIterator{
private:
	using Type = T;
	using TypePointer = T*;
	using TypeReference = T&;

	TypePointer _Pointer;
public:
	StackIterator(T* ptr): _Pointer(ptr) {}

	StackIterator& operator++(){ //prefix
		_Pointer++;
		return (*this);
	}

	StackIterator operator++(int){ //post fix //can not return StackIterator&& and then do move(tmp), because it's goign to return
	//a reference to an object that will be destroyed when function ends (dangling pointer), and not allow RVO.
		StackIterator tmp = _Pointer;
		_Pointer++;
		return tmp;
	}

	StackIterator& operator--(){ //prefix
		_Pointer--;
		return (*this);
	}

	StackIterator operator--(int){ //post fix
		StackIterator tmp = _Pointer;
		_Pointer--;
		return tmp;
	}

	TypeReference operator*(){
		return *_Pointer;
	}

	TypePointer operator->(){
		return _Pointer;
	}

	bool operator==(const StackIterator& other){
		return _Pointer == other._Pointer;
	}

	bool operator!=(const StackIterator& other){
		return _Pointer != other._Pointer;
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
		z = new int[50];
		cout << "Constructed\n";
	}

	Entity(int x, int y): x(x), y(y) {
		numOrder = ++objects;
		z = new int[50];
		cout << "Constructed\n";
	}

	Entity(const Entity& other): x(other.x), y(other.y) {
		numOrder = ++objects;
		z = new int[50];
		memcpy(z, other.z, sizeof(int) * 50);
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
		memcpy(z, other.z, sizeof(int) * 50);
		cout << "Copied operator!\n";
		return *this;
	}

	Entity& operator=(Entity&& tmp){
		if(this == &tmp) //can't move ourself to ourself.
			return *this;
		x = tmp.x;
		y = tmp.y;

		delete []z; //avoid memory leak before re assigning our array to tmp's.
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
		delete []z;

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
	//when someone uses a refernce to this, if later an rvalue is pushed, it's going to effect the reference (because a move cosntructor is applied)
	//when someones uses a reference to this, if later an lvalue is pushed, it's not going to effect the reference (because a copy constructor is appleid).
	//IMO this is better than copying, because a stack is like a store.
	//The user should know not to create a reference to this return reference, and if he pops it to nothing it's more effecient than copying.
	//After doing some test, this is the fastest (by a little over the T&&, even though it allocates more memory)
		if(current_size <= 0){
			cout << "Can't pop! stack is empty ... exiting\n";
			exit(1);
		}
		return s_Arr[--current_size];
	}
*/


	T&& Pop(){ 
		//this forces not to take lvalue references, but it does enable using rvalue references(&&).
		//when someone uses a refernce to this, if later an rvalue is pushed, it's going to effect the reference (because a move cosntructor is applied)
		//when someones uses a reference to this, if later an lvalue is pushed, it's not going to effect the reference (because a copy constructor is appleid).
		//this is more effecient (look at StackImp2 and StackImp3), weirdly StackImp3 is faster (maybe because I tried first the StackImp2).
		if(current_size <= 0){
			cout << "Can't pop! stack is empty ... exiting\n";
			exit(1);
		}
		return move(s_Arr[--current_size]);
	}




	T PopCopy(){ //we shoudln't use a copy to return, but the compiler optimizes this to create only one copy!
	//it uses this copy to straight initilize the other object (instead of copy then use copy constructor, it would just copy to the object).
	//if we pop to nothing, it's wasting a copy constructor.
	//the compiler doesn't optimize when we assign the pop to an existing object (unlike the copy constructor initilization)
	//using this will avoid the rvalue push effecting our varaible.
		return s_Arr[--current_size];
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

	void PrintStack(){ //this won't work on classes unless they overloaded the << operator.
		u_int it = current_size - 1;
		while(it != - 1){
			cout << "| " << s_Arr[it--] << " |";
		}
		cout << endl;

	}

	StackIterator<T> begin(){
		return StackIterator<T>(&s_Arr[0]);
	}

	StackIterator<T> end(){
		return StackIterator<T>(&s_Arr[current_size]);
	}



};
int main(){
	//to see performance difference between returning a Pop of T&& and T&, check StackImp2 and StackImp3.
	Stack<Entity, 10>s;
	Timer t;


	cout << "~~~Push constructor\n";
	s.PushConstructor(1,2);
	cout << "~~~Push Temp\n";
	s.Push(Entity());

	cout << "~~~Poping entity into another entity reference\n";
	Entity&& x = s.Pop();

	cout << "~~~First state\n";
	x.Print();
	cout << "~~Pushing tmp value\n";
	s.Push(Entity(23,34));
	cout << "~~~Second state\n"; 
	x.Print();
	Entity y;
	cout << "~~~Pushing lvalue\n";
	s.Push(y);
	cout << "~~~Third state\n";
	x.Print();

	cout << "\n~~~~~~~~\n\n";
	Entity&& x1 = s.PopCopy(); //if we were to do Entity x1 = s.PopCopy, it would do rvo optimization so it would stil look like the only copy is from PopCopy.

	cout << "~~~First state\n";
	x1.Print();
	cout << "~~Pushing tmp value\n";
	s.Push(Entity(23,34));
	cout << "~~~Second state\n";
	x1.Print();
	Entity y1;
	cout << "~~~Pushing lvalue\n";
	s.Push(y1);
	cout << "~~~Third state\n";
	x1.Print();

	cout << "~~TEST~~\n";
	Entity x3;
	x3 = s.PopCopy(); //it first uses copy constructor to copy, then move operator to move rvalue;

	cout << "~~~\n~~~\n~~~\n";

	for (auto i = s.begin(); i != s.end(); i++)
	{
		i->Print();
	}

	for (auto value : s)
	{
		value.Print();
	}
	cout << "Resources Allocated: " << Resources::allocated << endl;
	return 0;
}