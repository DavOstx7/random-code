#include <iostream>
#include <memory>

using namespace std;

struct Node{
    int value;
    static int count;
    int num;
    shared_ptr<Node>next;
    
    Node(): value(0), next(nullptr){
        num = ++count;
    }
    
    ~Node(){
        cout << "Destructed " << num << endl;
    }
};

int Node::count = 0;

struct NodeNormal{
    int value;
    static int count;
    int num;
    NodeNormal* next;
    
    NodeNormal(): value(0), next(nullptr){
        num = ++count;
    }
    
    ~NodeNormal(){
        cout << "Destructed Normal " << count << endl;;
    }
};

int NodeNormal::count = 0;

void Test(shared_ptr<Node> head){
    shared_ptr<Node> save = head->next->next;
    head->next = nullptr;
    head->next = save;
    return;
    head->next = head->next->next;
}

void Test(NodeNormal* head){
    NodeNormal* save = head->next->next;
    delete head->next;
    head->next = save;
    return;
    head->next = head->next->next;
}

int main()
{
    cout << "~~~Testing shared_ptr V1~~~\n";
    auto n2 = make_shared<Node>(); // 1
    n2->next = make_shared<Node>(); //2
    n2->value = 5;
    
    Test(n2);
    
    cout << "~~~Testing shared_ptr V2~~~\n";
    auto n22 = make_shared<Node>(); // 3
    auto n11 = make_shared<Node>(); // 4
    n22->next = n11;
    n22->value = 5;
    
    Test(n22);
    
    cout << "~~~Testing shared_ptr V3~~~\n";
    
    auto n222 = make_shared<Node>(); // 5
    auto n111 = make_shared<Node>(); // 6
    n222->next = n111;
    n222->value = 5;
    
    Test(n222);
    n111 = nullptr;
    
    cout << "\n~~~Testing normal pointerV1~~~\n";
    NodeNormal* m2 = new NodeNormal;
    m2->next = new NodeNormal;
    m2->value = 5;
    Test(m2);
    
    cout << "\n~~~Testing normal pointerV2~~~\n";
    NodeNormal* m22 = new NodeNormal;
    NodeNormal* m11 = new NodeNormal;
    m22->next = m11;
    m22->value = 5;
    Test(m22);
    
  
    cout << "\nEnd of main!\n";
    return 0;
}
