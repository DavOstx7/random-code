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


bool PrintLevelXs(BinNode* binnode, int targetLevel, int level, int spacesFirst, int spacesOther, bool needsFirst, int levels){ //needsFirst should be true in the first call
	if(binnode == NULL)
	{
		if(level == targetLevel)
		{
			if(needsFirst)
			{ //It's printing the first one of this level.
				printf("%*c", spacesFirst, 'X'); //the node is empty, but we still need to push spaces.
				return false; //signaling that we don't need the first no more
			}
			printf("%*c", spacesOther, 'X'); //the node is empty, but we still need to push spaces.
			return false;
		}
		//we need to push spaces the amount of times that would've been pushed if we reached target level from this binnode
		int pushes = pow(2, levels - level -1);
		bool ret = needsFirst; //if it's the first we gone print it, then print the others.
		if(needsFirst)
		{
			printf("%*c", spacesFirst, 'X');
			ret = false; //change ret to be false to signal that we don't need anymore to print the first.
			pushes--;
		}

		for (int i = 0; i < pushes; ++i) //loop an print the number that would've been printed.
			printf("%*c", spacesOther, 'X');

		return ret; //signaling the first hasn't been printed yet
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
	needsFirst = PrintLevelXs(binnode->left, targetLevel, level + 1, spacesFirst, spacesOther, needsFirst, levels);
	PrintLevelXs(binnode->right, targetLevel, level + 1, spacesFirst, spacesOther, needsFirst, levels);
}
	
bool PrintLevelsEmpty(BinNode* binnode, int targetLevel, int level, int spacesFirst, int spacesOther, bool needsFirst, int levels){ //needsFirst should be true in the first call
	if(binnode == NULL){
		if(level == targetLevel){
			if(needsFirst){ //It's printing the first one of this level.
				printf("%*c", spacesFirst, ' '); //the node is empty, but we still need to push spaces.
				return false; //signaling that we don't need the first no more
			}
			printf("%*c", spacesOther, ' '); //the node is empty, but we still need to push spaces.
			return false;
		}
		//we need to push spaces the amount of times that would've been pushed if we reached target level from this binnode
		int pushes = pow(2, levels - level -1);
		bool ret = needsFirst; //if it's the first we gone print it, then print the others.
		if(needsFirst)
		{
			printf("%*c", spacesFirst, ' ');
			ret = false; //change ret to be false to signal that we don't need anymore to print the first.
			pushes--;
		}

		for (int i = 0; i < pushes; ++i) //loop an print the number that would've been printed.
			printf("%*c", spacesOther, ' ');

		return ret; //signaling the first hasn't been printed yet
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

	needsFirst = PrintLevelsEmpty(binnode->left, targetLevel, level + 1, spacesFirst, spacesOther, needsFirst, levels);
	PrintLevelsEmpty(binnode->right, targetLevel, level + 1, spacesFirst, spacesOther, needsFirst, levels);
}


void PrintBinaryTreeXs(BinNode* root, int levels){
	for (int currentLevel = 0; currentLevel < levels; currentLevel++)
	{
		int spacesFirst = pow(2, levels - currentLevel) -1;
		int spacesOther = pow(2, levels - currentLevel+1);
		printf("|%d|   ", currentLevel);
		PrintLevelXs(root, currentLevel, 0, spacesFirst, spacesOther, true, levels);
		printf("%*c  |%d|\n", spacesFirst, ' ', currentLevel);
	}
}


void PrintBinaryTreeEmpty(BinNode* root, int levels){
	for (int currentLevel = 0; currentLevel < levels; currentLevel++)
	{
		int spacesFirst = pow(2, levels - currentLevel) -1;
		int spacesOther = pow(2, levels - currentLevel+1) ;
		//printf("spacesFirst: %d, spacesOthers: %d, currentlevel: %d", spacesFirst, spacesOther, currentLevel);
		PrintLevelsEmpty(root, currentLevel, 0, spacesFirst, spacesOther, true, levels);
		printf("\n");
	}
}





int main(){
	BinNode* root = CreateBinNode(5);
	
	root->right = CreateBinNode(3);
	root->right->right = CreateBinNode(1);
	//root->right->left = CreateBinNode(9);

	root->left = CreateBinNode(7);
	root->left->left = CreateBinNode(4);
	root->left->right = CreateBinNode(5);
	//root->left->left->left = CreateBinNode(3);
	root->right->right->left = CreateBinNode(2);
	root->left->right->left = CreateBinNode(4);
	root->right->right->right = CreateBinNode(4);
	PrintBinaryTreeXs(root, 4);
	printf("\nPrinting Levels Empty:\n");
	PrintBinaryTreeEmpty(root, 4);

	return 0;
}