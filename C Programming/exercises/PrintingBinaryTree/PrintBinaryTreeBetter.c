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

static inline void PrintChars(char c, int times){
	for (int i = 0; i < times; ++i)
	{
		printf("%c", c);
	}
}
bool PrintLevelXs(BinNode* binnode, int targetLevel, int level, int spacesFirst, int spacesOther, bool needsFirst, int levels, int maxDigits){ //needsFirst should be true in the first call
	if(binnode == NULL)
	{
		if(level == targetLevel)
		{
			if(needsFirst)
			{ //It's printing the first one of this level.
				PrintChars(' ', spacesFirst); //the node is empty, but we still need to push spaces.
				PrintChars('x', maxDigits);
				return false; //signaling that we don't need the first no more
			}
			PrintChars(' ', spacesOther); //the node is empty, but we still need to push spaces.
			PrintChars('x', maxDigits);
			return false;
		}
		//we need to push spaces the amount of times that would've been pushed if we reached target level from this binnode
		int pushes = pow(2, levels - level -1);
		bool ret = needsFirst; //if it's the first we gone print it, then print the others.
		if(needsFirst)
		{
			PrintChars(' ', spacesFirst);
			PrintChars('x', maxDigits);
			ret = false; //change ret to be false to signal that we don't need anymore to print the first.
			pushes--;
		}

		for (int i = 0; i < pushes; ++i){ //loop an print the number that would've been printed.
			PrintChars(' ', spacesOther);
			PrintChars('x', maxDigits);
		}

		return ret; //signaling the first hasn't been printed yet or has been printed.
	}
	if(level == targetLevel){
		if(needsFirst){ //It's printing the first one of this level.
			PrintChars(' ', spacesFirst);
			printf("%0*d", maxDigits, binnode->value);
			return false; //signaling that we don't need the first no more
		}
		else{ //The first one has already been printed
			PrintChars(' ', spacesOther);
			printf("%0*d", maxDigits, binnode->value);
			return false; //signaling that it's not the first (already has been printed)
		}	
	}
	needsFirst = PrintLevelXs(binnode->left, targetLevel, level + 1, spacesFirst, spacesOther, needsFirst, levels, maxDigits);
	PrintLevelXs(binnode->right, targetLevel, level + 1, spacesFirst, spacesOther, needsFirst, levels, maxDigits);
}
	

int GetMaxNum(BinNode* binnode){
	if(binnode == NULL)
		return -1;
	int n1 = GetMaxNum(binnode->left);
	int n2 = GetMaxNum(binnode->right);
	int n3 = (n1 > n2) ? n1 : n2;//n3 = the bigger number between n1 n2;
	return (binnode->value > n3) ? binnode->value : n3;
}

int CountDigits(int value){
	int count = 0;
	while (value != 0){
		count++;
		value = value/10;
	}
	return count;
}

void PrintBinaryTreeXs(BinNode* root, int levels){
	int maxDigits = CountDigits(GetMaxNum(root));
	if(maxDigits%2 == 0)
		maxDigits++;

	for (int currentLevel = 0; currentLevel < levels; currentLevel++){
		int ratio = (maxDigits/2 + 1);
		int spacesFirst = (pow(2, levels - currentLevel) -2 + maxDigits) * ratio;
		int spacesOther = (pow(2, levels - currentLevel+1) -1) * ratio -(ratio -1);

		printf("|%d| ", currentLevel);
		PrintLevelXs(root, currentLevel, 0, spacesFirst, spacesOther, true, levels, maxDigits);
		PrintChars(' ', spacesFirst);
		printf(" |%d|\n", currentLevel);

	}
}

int main(){
	BinNode* root = CreateBinNode(5);
	
	root->right = CreateBinNode(3);
	root->right->right = CreateBinNode(1);
	//root->right->left = CreateBinNode(9);

	root->left = CreateBinNode(1);
	root->left->left = CreateBinNode(4);
	
	root->left->right = CreateBinNode(4);
	//root->left->left->left = CreateBinNode(3);
	root->right->right->left = CreateBinNode(2);
	root->left->right->left = CreateBinNode(1);
	root->right->right->right = CreateBinNode(5);
	root->right->right->right->left = CreateBinNode(9);
	root->right->right->right->left->right = CreateBinNode(9);
	PrintBinaryTreeXs(root, 5); //Doesn't work over the depth of 4 !!!
	

	return 0;
}