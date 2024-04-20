#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum BOOL {false = 0, true = 1} bool;
typedef struct BinNode{
	int value;
	struct BinNode* left;
	struct BinNode* right;
} BinNode;

BinNode* CreateBinNode(int value){
	BinNode* n = (BinNode *) malloc(sizeof(BinNode));
	n->left = n->right = NULL;
	n->value = value;
	return n;
}

bool PrintLevel(BinNode* binnode, int targetLevel, int level, int spacesFirst, int spacesOther, bool needsFirst){ //needsFirst should be true in the first call
	if(binnode == NULL){
		if(level == targetLevel){
			if(needsFirst){ //It's printing the first one of this level.
				printf("%*c", spacesFirst, ' '); //the node is empty, but we still need to push spaces.
				return false; //signaling that we don't need the first no more
			}
			printf("%*c", spacesOther, ' '); //the node is empty, but we still need to push spaces.
			return false;
		}
		return true; //signaling the first hasn't been printed yet
	}
	
	if(level == targetLevel){
		if(needsFirst){ //It's printing the first one of this level.
			printf("%*d", spacesFirst, binnode->value); 
			return false; //signaling that we don't need the first no more
		}
		else{ //The first one has already been printed
			printf("%*d", spacesOther, binnode->value);
			return false; //signaling that it's not the first (already has been printed)
		}
		
	}

	needsFirst = PrintLevel(binnode->left, targetLevel, level + 1, spacesFirst, spacesOther, needsFirst);
	PrintLevel(binnode->right, targetLevel, level + 1, spacesFirst, spacesOther, needsFirst);
}

void PrintBinaryTree(BinNode* root, int levels){
	for (int currentLevel = 0; currentLevel < levels; currentLevel++)
	{
		int spacesFirst = pow(2, levels - currentLevel) -1;
		int spacesOther = pow(2, levels - currentLevel+1) ;
		//printf("spacesFirst: %d, spacesOthers: %d, currentlevel: %d", spacesFirst, spacesOther, currentLevel);
		PrintLevel(root, currentLevel, 0, spacesFirst, spacesOther, true);
		printf("\n");
	}
}
int main(){
	BinNode* root = CreateBinNode(5);
	
	root->right = CreateBinNode(3);
	root->right->right = CreateBinNode(1);
	root->right->left = CreateBinNode(9);

	root->left = CreateBinNode(7);
	root->left->left = CreateBinNode(4);
	root->left->right = CreateBinNode(5);
	
	PrintBinaryTree(root, 3);

	return 0;
}