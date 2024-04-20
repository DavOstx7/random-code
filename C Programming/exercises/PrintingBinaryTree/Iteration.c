#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum bool {NO, YES} bool;
enum structureName {ARRAY = 1, LINKEDLIST = 2, BINARYTREE = 3};

typedef struct Node{
	int value;
	struct Node* next;
} Node;

typedef struct BinNode{
	int value;
	struct BinNode* left;
	struct BinNode* right;
} BinNode;

typedef struct IterInfo{
	void* dataStructure;
	union{
		size_t size;
		size_t depth;
	};
	enum structureName name;
} IterInfo;

void PrintNodes(Node* head){
	printf("LinkedList: ");
	while(head != NULL){
		printf("%d-->", head->value);
		head = head->next;
	}
	printf("null\n");
}

void PrintArray(const size_t size, int arr[size]){
	printf("Array: ");
	for (int i = 0; i < size; ++i)
	{
		printf("[%d]", arr[i]);
	}
	printf("\n");
}

unsigned int IsLeaf(BinNode* node){
	return node->left == NULL & node->right == NULL;
}

void PrintBinaryTreeHorizontal(BinNode* binnode, int spaces, int newlines){ //spaces should be 0 at the start, newlines should be pow(levels-1,2)
	if(binnode == NULL){
		return;
	}
	if(IsLeaf(binnode)){
		printf("%*d", spaces, binnode->value);
		return;
	}

	PrintBinaryTreeHorizontal(binnode->right, (int)(spaces  + 2) * 1.5, newlines/2);
	for (int i = 0; i < newlines/2; ++i)
			printf("\n");
	printf("%*d", spaces, binnode->value);
	for (int i = 0; i < newlines/2 * 2; ++i)
			printf("\n");
	PrintBinaryTreeHorizontal(binnode->left, (int)(spaces  + 2) * 1.5, newlines/2);
	for (int i = 0; i < newlines - newlines/2; ++i)
		printf("\n");
}


void DataStructureIterator(size_t size, IterInfo arr[]){
	for (int i = 0; i < size; ++i)
	{
		if(arr[i].name == LINKEDLIST){
			PrintNodes((Node*) arr[i].dataStructure);
			printf("\n");
			continue;
		}
		if(arr[i].name == ARRAY){
			PrintArray(arr[i].size, (int*) arr[i].dataStructure);
			printf("\n");
			continue;
		}
		if(arr[i].name == BINARYTREE){
			printf("BinaryTree: \n\n\n");
			PrintBinaryTreeHorizontal((BinNode*)arr[i].dataStructure, 0, pow(arr[i].depth -1, 2));
			printf("\n");
			continue;
		}
	}
}

int main(){
	
	//Creating Linked List
	Node* head = (Node*) malloc(sizeof(Node));
	Node* body1 = (Node*) malloc(sizeof(Node));
	Node* body2 = (Node*) malloc(sizeof(Node));
	Node* tail = (Node*) malloc(sizeof(Node));

	head->value = 10;
	head->next = body1;

	body1->value = 5;
	body1->next = body2;

	body2->value = 24;
	body2->next = tail;

	tail->value = 3;
	tail->next = NULL;

	//Creating Array
	int arr[5] = {1, 7, 3, 9, 5};
	
	//Creating Binary Tree
	BinNode* root = (BinNode *) malloc(sizeof(BinNode));
	root->value = 0;
	BinNode* left = (BinNode *) malloc(sizeof(BinNode));
	left->value = 3;
	root->left = left;
	BinNode* right = (BinNode *) malloc(sizeof(BinNode));
	right->value = 9;
	root->right = right;



	BinNode* rightright = (BinNode *) malloc(sizeof(BinNode));
	rightright->value = 11;
	right->right = rightright;
	BinNode* rightleft = (BinNode *) malloc(sizeof(BinNode));
	rightright->value = 43;
	right->left = rightleft;
	BinNode* leftleft = (BinNode *) malloc(sizeof(BinNode));
	leftleft->value = 84;
	left->left = leftleft;
	BinNode* leftright = (BinNode *) malloc(sizeof(BinNode));
	leftright->value = 77;
	left->right = leftright;

	IterInfo LinkedList = {.dataStructure = (void *)head, .name = LINKEDLIST};
	IterInfo Array = {.dataStructure = (void *)arr, .size = 5, .name = ARRAY};
	IterInfo BianryTree = {.dataStructure = (void *)root, .depth = 3, .name = BINARYTREE};

	IterInfo iterator[] = {Array, LinkedList, BianryTree};
	DataStructureIterator(sizeof(iterator) / sizeof(iterator[0]), iterator);
	return 0;	

}

/* This is a cleaner way - I thought about a class (c++), but I should use in C functions that keep it simple.

struct Node* newNode(int data)
{
	struct Node* node = malloc(sizeof(struct Node));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

	struct Node *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);

	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(7);

	root->left->left->left = newNode(8);
	root->left->left->right = newNode(9);
	root->left->right->left = newNode(10);
	root->left->right->right = newNode(11);
*/
