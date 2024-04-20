#include <iostream>

using namespace std;

struct Node{
	int value;
	Node* next;

	Node(int value): next(nullptr), value(value) {}
	Node(): value(0), next(nullptr) {}
	Node(int value, Node* next): value(value), next(next){}
};

struct QueueIterator{
private:
	Node* current;
public:
	QueueIterator(Node* pointer): current(pointer){}

	QueueIterator& operator++(){
		current = current->next;
		return *this;
	}

	QueueIterator operator++(int){
		QueueIterator tmp(current);
		current = current->next;
		return tmp;
	}

	Node& operator*(){
		return *(current);
	}

	bool operator==(const QueueIterator& other) const{
		return current == other.current;
	}
	
	bool operator!=(const QueueIterator& other) const{
		return current != other.current;
	}
};

class Queue{
public:
	Node* first;
	Node* last;

public:
	Queue(): first(nullptr), last(nullptr) {}

	void Add(int value){
		if(first == nullptr){
			last = new Node(value);
			first = last;
			return;
		}
		last->next = new Node(value);
		last = last->next;
	}

	int Pop(){
		if(first == nullptr)
			return -1;
		if(first->next == nullptr){
			int retval = first->value;
			delete first;
			first = last = nullptr;
			return retval;
		}
		int retval = first->value;
		Node* tmp = first;
		first = first->next;
		delete tmp;
		return retval;
	}

	void Print(){

		Node*current = first;
		cout << "<exit> ";
		while(current != nullptr){
			cout << current->value << " ";
			current = current->next;
		}
		cout << "<entrance>" << endl;
	}

	QueueIterator begin(){
		return QueueIterator(first);
	}

	QueueIterator end(){
		return QueueIterator(nullptr);
	}
};



int main(){
	Queue q;
	q.Add(5);
	q.Add(2);
	q.Add(3);
	q.Add(4);
	q.Add(5);
	q.Print();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Print();
	q.Add(31);
	q.Add(31);
	q.Add(31);
	q.Print();

	for(auto current: q){
		cout << current.value;
	}
	return 0;
}