#include <iostream>
using namespace std;

struct BinNode{
	int val;
	BinNode* left;
	BinNode* right;

	BinNode(): val(0), left(nullptr), right(nullptr) {}
	BinNode(int val): val(val), left(nullptr), right(nullptr) {}
	BinNode(int val, BinNode* left, BinNode* right): val(val), left(left), right(right) {}

	bool IsLeaf(){ return left == nullptr && right == nullptr; }	
};

void PrintBinNode(BinNode* ptr){
	if(ptr == nullptr){
		return;
	}
	cout << ptr->val << " ";
	PrintBinNode(ptr->left);
	PrintBinNode(ptr->right);
}

void DeleteBinNode(BinNode *ptr, int x, bool deleted = false, BinNode *l = nullptr, BinNode *r = nullptr){
	cout << "\n\n~~~in start loop~~~~\n\n";
	cout << "In loop with " << ptr << endl;
	if(ptr == nullptr){
		cout << "Couldn't delete a node with the value " << x << endl;
		return;  
	}
	if(deleted){
		cout << "\n\nIN DELETED\n\n";
		if(ptr)
			cout << "wasup" << ptr << "\n\n!!!!\n\n";
	}
	if(ptr->IsLeaf()){
		if(deleted == false){
			cout << "Couldn't delete a node with the value " << x << endl;
			return;
		}
		cout << "LN value = " << l->val << " r = " << r << endl;
		ptr->left = l;
		ptr->right = r;
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
		if (ptr->left->left != nullptr && ptr->left->right != nullptr){
			BinNode* ln = ptr->left->left;
			BinNode* rn = ptr->left->right;
			delete ptr->left;
			ptr->left = nullptr;
			cout << "Deleted Node with the value of " << x  << endl;
			cout << "About to join the pointer: " << ptr->right << endl;
			cout << "LN VALUE IS: " << ln->val;
			cout << "\n TESTING PTR-RIGHT: " << ptr->right->val;
			if(ptr->right)
				DeleteBinNode(ptr->right, x, true, ln, rn);
		}
		if (ptr->left->left != nullptr){
			BinNode* l = ptr->left->left;
			delete ptr->left;
			ptr->left = l;
			goto Returning;
		}
		if(ptr->left->right != nullptr){
			BinNode* r = ptr->left->right;
			delete ptr->left;
			ptr->left = r;
			goto Returning;
		}
	}

	if(ptr->right != nullptr && ptr->right->val == x){
		if (ptr->right->IsLeaf()){ 
			delete ptr->right;
			cout << "Deleting leaf with the value of " << x << endl;
			ptr->right = nullptr;
			return;
		}
		if (ptr->right->left != nullptr && ptr->right->right != nullptr){
			BinNode* ln = ptr->right->left;
			BinNode* rn = ptr->right->right;
			delete ptr->right;
			cout << "Deleted Node with the value of " << x << endl;
			DeleteBinNode(ptr->left, x, true, ln, rn);
		}
		if (ptr->right->left != nullptr){
			BinNode* l = ptr->right->left;
			delete ptr->right;
			ptr->right = l;
			goto Returning;
		}
		if (ptr->right->right != nullptr){
			BinNode* r = ptr->right->right;
			delete ptr->right;
			ptr->right = r;
			goto Returning;
			return;
		}		
	}
	cout << "Im in the value of " << ptr->val << " and deleted = " << deleted << endl;
Deleted:
	DeleteBinNode(ptr->left, x, deleted, l, r);
	DeleteBinNode(ptr->right, x, deleted, l, r);
Returning:
	cout << "Deleted Node with the value of " << x << endl;
	return;
}

int main(){

	BinNode* root = new BinNode(5, new BinNode(20), new BinNode(10));
	BinNode* fleft = root->left;
	fleft->left = new BinNode(4);
	fleft->right = new BinNode(6);
	
	PrintBinNode(root);
	cout << endl;
	DeleteBinNode(root, 20);
	PrintBinNode(root);

}