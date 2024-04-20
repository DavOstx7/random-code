#include <stdio.h>
#include <stdlib.h>

int main(int argc, unsigned char *argv[]){

	printf("char = %c\n", argv[1][0]);
	unsigned int num = argv[1][0];
	if(num == 0x89){
		printf("Yes!\n");
	}
	else{
		printf("noooo %x\n", num);
	}

	return 0;
}