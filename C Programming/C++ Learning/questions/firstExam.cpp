#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Subject{
    private:
        string subName;
        int grade;  
    public:
        Subject() = default;

        Subject(string subName, int grade){
            this->subName = subName;
            this->grade = grade;
        }

        void SetSubName(string subName) {this->subName = subName;}
        void SetGrade(int grade) {this->grade = grade;}

        string GetSubName(){
            return this->subName;
        }

        int GetGrade(){
            return this->grade;
        }
};

class ReportCard{
    private:
        string stuName;
        int grades;
        vector <Subject> subArray;
    public:
        ReportCard(string name, int num){ //enter string name, int num
            this->stuName = name;
            this->grades = num;
            this->subArray.resize(this->grades);
        }

        void SetStduName(string stuName) {this->stuName = stuName;}
        void SetSubArray(vector <Subject> arr){ 
            for (int i = 0; i < arr.size(); i++)
            {
                this->subArray[i] = arr[i];
            } 
        }

        string GetStuName(){return this->stuName;}
        vector<Subject> GetSubArray(){return this->subArray;}

        double average(){
            double sum = 0;
            for (int i = 0; i < this->grades; i++)
            {
                sum += this->subArray[i].GetGrade();
            }
            return sum / this->grades;
        }

        bool isExcellent(){
            bool x54 = true;
            bool x100 = false;
            bool x85 = this->average() >= 85.0;
            for (int i = 0; i < this->grades; i++)
            {
                int grade = this->subArray[i].GetGrade();
                if (grade == 100){
                    x100 = true;
                }
                
                if (grade <= 54){ // if ( !(grade > 54) )
                    x54 = false;
                }
            }            
            return x54 && x100 && x85;
        }

};

class MyString{
    public:
        string str;
    public:
        MyString() : str("") {};
        MyString(string s): str(s) {};
        int countChar(char ch){
            int count = 0;
            for (int i = 0; i < this->str.length(); i++)
            {
                if(this->str[i] == ch){
                    count++;
                }
            }
            return count;
        }

        void removeChar(char ch){
            string tmp = "";
            for (int i = 0; i < this->str.length(); i++)
            {
                if(this->str[i] != ch){
                    tmp+= str[i];
                }
            }
            this->str = tmp;
        }

        void appendChar(char ch) {this->str += ch;}
        char firstChar(){return this->str[0];}
        bool isEmpty(){return this->str.empty();}
        void printStr(){cout << this->str;}
};

template <typename T>
struct Node{
    public:
        T value;
        Node * next;
    Node(): value(0), next(nullptr){}
    Node(T value): value(value), next(nullptr){}
    Node(T value, Node * next): value(value), next(next){}

};

class BiList{
    public:
        Node<int> * lst1;
        Node<int> * lst2;

        BiList(): lst1(nullptr), lst2(nullptr){}
        void addNum(int num, int codeList){
            if (codeList == 1){
                if(this->lst1 == nullptr){
                    this->lst1 = new Node<int>(num);
                }
                else{
                    Node<int> *current = this->lst1;
                    while(current->next != nullptr){
                        current = current->next;
                    }
                    current->next = new Node<int>(num);
                }
            }
            if (codeList == 2){ //could've used else, but the question made it look like this is more accurate representation.
                if(this->lst2 == nullptr){
                    this->lst2 = new Node<int>(num);
                }
                else{
                    Node<int> *current = this->lst2;
                    while(current->next != nullptr){
                        current = current->next;
                    }
                    current->next = new Node<int>(num);
                }
            }
        }

        void print_obj(){
            cout << "list1: ";
            Node<int> *current = this->lst1;
            while(current!=nullptr){
                cout << "[" << current->value << "]-->";
                current = current->next;
            }
            cout << "null" << endl;

            cout << "list2: ";
            current = this->lst2;
            while(current!=nullptr){
                 cout << "[" << current->value << "]-->";
                current = current->next;
            }
            cout << "null" << endl;
        }
};

template <typename T>
struct Queue{
    public:
        Node<T>* first;
        Node<T>* last;

    Queue(): first(nullptr), last(nullptr) {};
    
    void Insert(T num){
        if(first == nullptr && last == nullptr){
            first = last = new Node<T>(num);
        }
        else{
            last->next = new Node<T>(num);
            last = last->next;
        }
    }

    T Extract(){
        if(first == nullptr && last == nullptr){
            return 0;
        }
        if(first == last){
            T retval = first->value;
            delete first;
            first = last = nullptr;
            return retval;
        }
        Node<T>* current = first;
        first = first->next;
        T retval = current->value;
        delete current;
        return retval;
    }

    bool IsEmpty(){
        return first == nullptr && last == nullptr;
    }

    int count(){
        Node<T> * current = first;
        int count = 0;
        while(current != nullptr){
            count++;
            current = current->next;
        }
        return count;
        
    }
    void print_queue(){
        cout << "size: " << sizeof(*this) << endl;
        if(first == nullptr && last == nullptr){
            cout << " <queue empty>!" << endl;
            return;
        }
        Node<T> *current = first;
        cout <<"<exit> ";
        while(current->next != nullptr){
            cout << current->value << " <-- ";
            current = current->next;
        }
        cout << current->value << " <entrance>";
        cout << endl;
        current = first;
        cout << "Pointers: <first> ";
        while(current->next != nullptr){
            cout << current << "-->";
            current = current->next;
        }
        cout << current << " <last>";
        cout << endl;
    }
};
Node <int>* Delete(Node<int>* head, int num){

    Node<int> *tmp = new Node<int>(0, head);
    Node<int> *current = tmp;
    while(current->next != nullptr){
        if(current->next->value == num){
            Node<int> *del = current->next;
            current->next = current->next->next;
            delete del;
        }
        else{
            current = current->next;
        }
    }
    head = tmp->next;
    delete tmp;
    return head;
}

BiList generateBiList(Node<int>* head){
    BiList ret;
    Node<int>* current = head;
    int count = 0;

    while(current != nullptr){
        count++;
        current = current->next;
    }

    int target = count / 2;
    count = 0;

    while(count < target){
        current = head;
        int min = current->value;
        current = current->next;
        while(current!=nullptr){
            if(current->value < min){
                min = current->value;
            }
            current = current->next;
        }
        head = Delete(head, min);
        ret.addNum(min, 2);
        count++;
    }

    while(head!=nullptr){
        int max = head->value;
        head = Delete(head, max);
        ret.addNum(max, 1);
    }
    return ret;
}
void printExcellent(vector <ReportCard> arr){
    cout << "Excellent students: ";
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i].isExcellent()){
            cout << arr[i].GetStuName() << " ";
        }
    }
    cout << endl;
        
}
void print_vector(vector<int> &arr){
    for (int i = 0; i < arr.size() ; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    
}
vector <int> Q1(vector <int> arr, int num){
    if(sizeof(arr) == 0){
        return vector <int>(0);
    }
    int count = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i] != num){
            count +=1;
        }
    }
    vector <int> retArr(count);
    int index = 0;
    for (int i = 0; i <arr.size(); i++)
    {
        if(arr[i] != num){
            retArr[index] = arr[i];
            index++;
        }
    }
    return retArr;     
}

MyString Special(MyString ms){
    MyString ret;
    while(ms.isEmpty() == false){
        char c = ms.firstChar();
        int times = ms.countChar(c);
        ms.removeChar(c);
        while (times != 0){
            ret.appendChar(c);
            times--;
        }
    }
    return ret;
}

void print_nodes(Node<int>* head){
    while(head != nullptr){
        cout << head->value << "-->";
        head = head->next;
    }
    cout << "null" << endl;
}

Node<int>* move(Node<int>* head, int n){
    int count = 0;
    Node<int> *current = head;
    while(current != nullptr){
        count++;
        current = current->next;
    }
    int target = count - n;
    current = head;
    count = 1;
    while(count < target){
        current = current->next;
        count++;
    }
    Node<int>* new_head = current->next;
    current->next = nullptr;
    current = new_head;
    while(current->next != nullptr){
        current = current->next;
    }
    current->next = head;
    return new_head;
}


bool isIdentical(Queue<int> q1, Queue<int> q2){ //better to use reference, to save copying (I wanted it to be like C#)
    if(q1.count() != q2.count()){
        return false;
    }

    Queue<int> tmp1;
    Queue<int> tmp2;

    /* what I learned from this function:
    --- The code below destroys the Queue's in the main function, because it deletes all of the nodes the pointer's point to.
    while(!q1.IsEmpty()){
        q1.Extract();
    }

    while(!q2.IsEmpty()){
        q2.Extract();
    }

    --- This code doesn't change anything, because everytime a memory location gets freed from q1 it gets added to the bin cache,
    --- then when allocate memory with the same size it gets taken from the bin, and put the same value that was taken in there.
    while(!q1.IsEmpty()){
        tmp1.Insert(q1.Extract());
    }

    while(!q2.IsEmpty()){
        tmp2.Insert(q2.Extract());
    }
    */
    while(!q1.IsEmpty()){
        tmp1.Insert(q1.Extract());
    }

    while(!q2.IsEmpty()){
        tmp2.Insert(q2.Extract());
    }
    bool same = true;
    while(!tmp1.IsEmpty()){
        int n1 = tmp1.Extract();
        q1.Insert(n1);
        int n2 = tmp2.Extract();
        q2.Insert(n2);
        if(n1 != n2){ // can't return straight, because we need to restore q1,q2.
            same = false;
        }
        // ### THIS WAS WRONG FOR SOME REASON ---> If we change the order of these two lines, it will copy it opposite to the original. (because now in the bin the location the tmp2 pointer is first, and then tmp1)
        //q1.Insert(n1);
       // q2.Insert(n2);
    }
    return same;
}

bool isSimilar(Queue<int>q1, Queue<int>q2){
    int count = q1.count();
    if(count != q2.count()){
        return false;
    }
    for (int i = 0; i < count; i++)
    {
        if(isIdentical(q1,q2)){
            return true;
        }
        q2.Insert(q2.Extract()); //What's in the () gets done first, so in the cache now the location of the deleted pointer, and he now gets assigned.
    }
    return false;
    // this funcion destroyes the q2 Queue, because in the main it will only show from q2 and forth.
}
int main(){

    /* Exercise 1 
    vector <int> q1 = {6, 9, 2, 2, 9, 4, -3};
    print_vector(q1);
    vector <int> q1ret = Q1(q1, 9);
    print_vector(q1ret);
    */

    /* Exercise 2
    ReportCard r1("r1", 4);
    vector<Subject> t1{Subject("math", 100), Subject("physics", 96), Subject("history", 84), Subject("cyber", 98)};
    r1.SetSubArray(t1);

    ReportCard r2("r2", 4);
    vector<Subject> t2{Subject("math", 100), Subject("physics", 100), Subject("history", 53), Subject("cyber", 100)};
    r2.SetSubArray(t2);

    ReportCard r3("r3", 4);
    vector<Subject> t3{Subject("math", 90), Subject("physics", 90), Subject("history", 90), Subject("cyber", 90)};
    r3.SetSubArray(t3);

    vector<ReportCard>rArr = {r1,r2,r3};

    printExcellent(rArr);
    */

    /* Exercise 3
    MyString ms ("babca");
    Special(ms).printStr();
    */

    /* Exercise 4
    Node<int>* tail = new Node<int>(13);
    Node<int>* n1 = new Node<int>(6, tail);
    Node<int>* n2 = new Node<int>(10, n1);
    Node<int>* n3 = new Node<int>(0, n2);
    Node<int>* n4 = new Node<int>(-9, n3);
    Node<int>* head = new Node<int>(88, n4); // I checked, and Node<int>head(5, n4) works!
    print_nodes(head);
    
    // head = Delete(head, 5); works!
    // print_nodes(head);

    
    BiList b;
    b = generateBiList(head);
    b.print_obj();
    */

    /* Exercise 5
    Node<int>* tail = new Node<int>(4);
    Node<int>* n1 = new Node<int>(8, tail);
    Node<int>* n2 = new Node<int>(2, n1);
    Node<int>* n3 = new Node<int>(1, n2);
    Node<int>* head = new Node<int>(5, n3);
    print_nodes(head);

    head = move(head, 2);
    print_nodes(head);
    */

    int *p = new int(31);
    //cout << p->val << endl;
    Queue<int> q1;
    q1.Insert(5);
    q1.Insert(7);
    q1.Insert(4);
    q1.Insert(6);
    cout << "###first set###\n";
    q1.print_queue();

    Queue<int> q2;
    q2.Insert(4);
    q2.Insert(6);
    q2.Insert(5);
    q2.Insert(7);
    q2.print_queue();

    cout << "isIdentical: " << isIdentical(q1, q2) << endl;
    cout <<  "isSimilar: " << isSimilar(q1, q2) << endl;
    //q1.print_queue();
    //q2.print_queue();
    

    return 0;
}
