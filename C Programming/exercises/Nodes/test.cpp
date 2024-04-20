#include <iostream>
#include <string>

using namespace std;

struct Node{
	int value;
	Node *next;	

	Node(){}
	Node(int num){
		value = num;
	}
	Node(int num, Node *nextUp){
		value = num;
		next = nextUp;
	}
};

struct Stack{
	Node* bottom;
	Node* top;
	int countItems;

	Stack(): bottom(nullptr), top(nullptr), countItems(0){}

	void Push(int val){
		if(bottom == nullptr and top == nullptr){
			bottom = top = new Node(val);
		}
		else{
			top->next = new Node(val);
			top = top->next;
		}
		countItems++;
	}

	void Pop(){
		Node *current = bottom;
		if(top == nullptr){
			goto Finish;
		}
		if(top == bottom){
			delete top;
			bottom = top = nullptr;
			goto Finish;
		}
		while(current->next->next != nullptr){
			current = current->next;
		}
		delete current->next;
		current->next = nullptr;
	Finish:
		countItems--;
	}

	void print(){
		int loopfor = countItems - 1;
		for (int i = 0; i < countItems; ++i)
		{

			Node *current = bottom;
			for (int i = 0; i < loopfor; ++i)
			{
				current = current->next;
			}
			cout << "|" << current->value << "|\n";
			loopfor--;
		}
		cout << "---\n";
	}
};

struct BinNode{
	int val;
	BinNode* left;
	BinNode* right;

	BinNode(): val(0), left(nullptr), right(nullptr) {}
	BinNode(int val): val(val), left(nullptr), right(nullptr) {}
	BinNode(int val, BinNode* left, BinNode* right): val(val), left(left), right(right) {}

	bool IsLeaf(){ return left == nullptr && right == nullptr; }	
};

BinNode* BinNodeTreeCreator(int value){
	BinNode* root = new BinNode(value);
	BinNode* current = root;
	//BinNode* root = new
	cout << "Explanation:\nCurrently the root value is: " << value << endl;
	cout << "To add a node on the left enter l followed (no space) with an int. same with right side\n";
	cout << "To move to the left node enter ml, same with the right side\n";
	cout << "To quit enter x:\n";

	while (1){
		string answer;
		cin >> answer;
		if(answer == "")
			continue;
		if(answer[0] == 'x')
			break;
		if(answer[0] == 'l' and answer.length() > 1){
			//answer = answer.erase(0, 1);
			answer = answer.substr(1, answer.length() - 1);
			current->left = new BinNode(stoi(answer));
			cout << "added " << answer << " to the left side...\n";
			continue;
		}
		if(answer[0] == 'r' and answer.length() > 1){
			answer = answer.erase(0, 1);
			current->right = new BinNode(stoi(answer));
			cout << "added " << answer << " to the right side...\n";
			continue;
		}
		if(answer == "ml"){
			if(current->left != nullptr)
				cout << "moving to the left node...\n";
			else
				cout << "left node is empty/null! cannot move there";
			current = current->left;
		}
		if(answer == "mr")
			if(current->right != nullptr)
				cout << "moving to the right node...\n";
			else
				cout << "right node is empty/null! cannot move there";
	}
	cout << "returning...\n";
	return root;


}

int ReturnSumBinNode(BinNode* root){
	if(root == nullptr)
		return 0;
	return root->val + ReturnSumBinNode(root->left) + ReturnSumBinNode(root->right);
}

void PrintBinNode(BinNode* ptr){
	if(ptr == nullptr){
		return;
	}
	cout << ptr->val << " ";
	PrintBinNode(ptr->left);
	PrintBinNode(ptr->right);
}
void DeleteBinNode(BinNode *ptr, int x, bool deleted = false, BinNode *l = nullptr, BinNode *r = nullptr){
	if(ptr == nullptr){
		return;  
	}
	if(ptr->IsLeaf()){
		if(deleted == false){
			return;
		}
		ptr->right = r;
		ptr->left = l;
		return;
	}
	if(deleted){
		goto Deleted;
	}
	if(ptr->left != nullptr && ptr->left->val == x){
		if (ptr->left->IsLeaf()){ 
			delete ptr->left;
			ptr->left = nullptr;
			cout << "Deleting leaf with the value of " << x << endl;
			return;
		}
		else if (ptr->left->left != nullptr && ptr->left->right != nullptr){
			BinNode* ln = ptr->left->left;
			BinNode* rn = ptr->left->right;
			delete ptr->left;
			ptr->left = nullptr;
			cout << "Deleted Node with the value of " << x << endl;
			DeleteBinNode(ptr, x, true, ln, rn);
		}
		else if (ptr->left->left != nullptr){
			BinNode* l = ptr->left->left;
			delete ptr->left;
			ptr->left = l;
			goto Returning;
		}
		else if(ptr->left->right != nullptr){
			BinNode* r = ptr->left->right;
			delete ptr->left;
			ptr->left = r;
			goto Returning;
		}
	}

	if (ptr->right != nullptr && ptr->right->val == x){
		if (ptr->right->IsLeaf()){ 
			delete ptr->right;
			cout << "Deleting leaf with the value of " << x << endl;
			ptr->right = nullptr;
			return;
		}
		else if (ptr->right->left != nullptr && ptr->right->right != nullptr){
			BinNode* ln = ptr->right->left;
			BinNode* rn = ptr->right->right;
			delete ptr->right;
			cout << "Deleted Node with the value of " << x << endl;
			DeleteBinNode(ptr, x, true, ln, rn); // this line gave a lot of problems, since if it deletes the left node
			// the next if will try to access it (after it returns) and cause a segment fault. I added else if but to solve it but if I wanted
			// to use my logic I should've put a return after like in the next line:
			// return;
		}
		else if (ptr->right->left != nullptr){
			BinNode* l = ptr->right->left;
			delete ptr->right;
			ptr->right = l;
			goto Returning;
		}
		else if(ptr->right->right != nullptr){
			BinNode* r = ptr->right->right;
			delete ptr->right;
			ptr->right = r;
			goto Returning;
			return;
		}		
	}
Deleted:
	DeleteBinNode(ptr->left, x, deleted, l, r);
	DeleteBinNode(ptr->right, x, deleted, l, r);
	return;
Returning:
	cout << "Deleted Node with the value of " << x << endl;
	return;
}
int main(){
	/*
	Stack st;
	st.Push(1);
	st.Push(5);
	st.Push(3);
	st.print();
	*/
	BinNode* root = BinNodeTreeCreator(10);
	PrintBinNode(root);
	cout << endl;
	cout << "\nsum is: " << ReturnSumBinNode(root) << endl;
	cout << "Enter a value to delete: ";
	int x;
	cin >> x;
	cout << endl;
	DeleteBinNode(root, x);

	PrintBinNode(root);
	cout << endl;
	cout << "\nsum is: " << ReturnSumBinNode(root) << endl;
	return 0;
}