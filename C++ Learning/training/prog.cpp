#include <iostream>

using namespace std;

class Integer{
public:
    int value;
    Integer(int value): value(value){
        cout << "constructor" << endl;
    }

    Integer(const Integer& other){
        this->value = other.value;
        cout << "copied" << endl;
    }

    Integer(const Integer&& tmp){
        this->value = tmp.value;
        cout << "moved" << endl;
    }

    void operator=(const Integer& other){
        this->value = other.value;
        cout << "copy operator" << endl;
    }

    void operator=(const Integer&& tmp){
        this->value = tmp.value;
        cout << "move operator" << endl;
    }
};

template<typename T>
struct Node{
    Node<T>* previous;
    T value;
    Node<T>* next;

    Node(T value): value(value), previous(nullptr), next(nullptr) {}
    Node(T value, Node<T>* previous, Node<T>* next): value(value), previous(previous), next(next) {}
};

template<typename T>
class DoubleLinkedListIterator{
public:
    DoubleLinkedListIterator(Node<T>* start): currentPointer(start) {}

    T operator*(){
        return this->currentPointer->value;
    }

    Node<T>* operator->(){
        return this->currentPointer;
    }

    DoubleLinkedListIterator& operator++(){
        this->currentPointer = this->currentPointer->next;
        return *this;
    }

    DoubleLinkedListIterator operator++(int){
        auto tmp = *this;
        this->currentPointer = this->currentPointer->next;
        return tmp;
    }

    bool operator!=(DoubleLinkedListIterator other){
        return this->currentPointer != other.currentPointer;
    }
private:
    Node<T>* currentPointer;
};

template<typename T>
class DoubleLinkedList{
private:
    Node<T>* first;
    Node<T>* last;

public:
    DoubleLinkedList(): first(nullptr), last(nullptr) {}

    ~DoubleLinkedList(){
        this->factoryReset();
    }

    Node<T>* getHead(){
        return this->first;
    }

    Node<T>* getTail(){
        return this->last;
    }

    void addEnd(T value){
        if (this->first == nullptr && this->last == nullptr){
            this->first = this->last = new Node<T>(value);
            return;
        }
        Node<T>* newLast = new Node<T>(value, this->last, nullptr);
        this->last->next = newLast;
        this->last = newLast;
    }

    void addBeggining(T value){
        if (this->first == nullptr && this->last == nullptr){
            first = last = new Node<T>(value);
            return;
        }
        Node<T>* newFirst = new Node<T>(value, nullptr, this->first);
        this->first->previous = newFirst;
        this->first = newFirst;
    }

    T removeEnd(){
        if (this->first == nullptr && this->last == nullptr)
            return T();

        Node<T>* toRemove = this->last;
        if (this->first == this->last)
            this->first = this->last = nullptr;
        else {
            this->last = this->last->previous;
            this->last->next = nullptr;
        }
        T retval = toRemove->value;
        delete toRemove;
        return retval;
    }

    T removeBeggining(){
        if (this->first == nullptr && this->last == nullptr)
            return T();
        Node<T>* toRemove = this->first;;
        if (this->first == this->last)
            this->first = this->last = nullptr;
        else {
            this->first = this->first->next;
            this->first->previous = nullptr;
        }
        T retval = toRemove->value;
        delete toRemove;
        return retval;
    }

    void printList(){
        if (this->first == nullptr && this->last == nullptr){
            cout << "null" << endl;
            return;
        }

        if (this->first == this->last){
            Node<T>* singleNode = this->first;
            cout << "null<-" << singleNode->value << "->null" << endl;
            return;
        }

        cout << "null<-";
        Node<T>* currentNode = this->first;
        while(currentNode->next != nullptr){
            cout << currentNode->value << "<->";
            currentNode = currentNode->next;
        }
        cout << currentNode->value << "->null" << endl;
    }

    void factoryReset(){
        Node<T>* currentNode = this->first;

        while (currentNode != nullptr){
            Node<T>* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
        this->first = this->last = nullptr;
    }

    DoubleLinkedListIterator<T> begin(){
        return DoubleLinkedListIterator<T>(this->first);
    }

    DoubleLinkedListIterator<T> end(){
        return DoubleLinkedListIterator<T>(nullptr);
    }
};

template<typename T>
class Vector{
public:
    int currentSize;
    int maxSize;

    Vector(int maxSize = 2): currentSize(0), maxSize(maxSize){
        this->dataPtr = (T*)::operator new(this->maxSize * sizeof(T));
    }

    void realloc(){
        int newMaxSize = this->calculateNextMaxSize();
        T* tmpNewDataPtr = (T*)::operator new(newMaxSize * sizeof(T));
        memcpy(tmpNewDataPtr, this->dataPtr, this->currentSize * sizeof(T));
        ::operator delete(this->dataPtr);
        this->dataPtr = tmpNewDataPtr;
    }

    void push(T& value){
        if (this->currentSize == this->maxSize){
            this->realloc();
        }
        // this->dataPtr[this->currentSize++] = value;
        new(this->dataPtr + currentSize) T(value);
        this->currentSize++;
    }

    void push(T&& value){
        if (this->currentSize == this->maxSize){
            this->realloc();
        }
        // this->dataPtr[this->currentSize++] = move(value);
        new(this->dataPtr + currentSize) T(value);
        this->currentSize++;
    }

    T& operator[](int index){
        if (index >= this->currentSize){
            cout << "Err";
        }
        return this->dataPtr[index];
    }

    const T& operator[](int index) const{
        if (index >= this->currentSize){
            cout << "Err";
        }
        return this->dataPtr[index];
    }   
    
    void printVector(){
        for (size_t i = 0; i < this->currentSize; i++)
        {
            cout << "[" << this->dataPtr[i] << "] ";
        }
        cout << endl;
        
    }

private:
    T* dataPtr = nullptr;
    int calculateNextMaxSize(){
        return this->maxSize * 2;
    }
};

ostream& operator<<(ostream &strm, const Integer &a) {
  return strm << "val = " << a.value;
}

int main(){
    DoubleLinkedList<int> dl;
    dl.addEnd(1);
    dl.addEnd(2);
    dl.addBeggining(0);
    dl.addBeggining(100);
    dl.addEnd(99);
    //dl.factoryReset();
    //dl.printList();
    
    for(auto it = dl.begin(); it != dl.end(); ++it){
        cout << it->value << " ";
    }
    
    cout << endl;
    dl.printList();

    return 0;
    dl.removeEnd();
    dl.removeBeggining();
    dl.removeEnd();
    dl.removeBeggining();
    dl.printList();
    /*
    Vector<Integer> v;
    v.push(2);
    v.push(9);
    v.printVector();
    */
    return 0;
}