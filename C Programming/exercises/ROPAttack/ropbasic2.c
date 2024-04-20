#include <stdio.h>
#include <string.h>

void exploit(){
	printf("Entered exploit function!");
}

void TakeInput(){
	printf("Copying input for a buffer of size 5 bytes\n");
	unsigned char buffer[5];
	scanf(buffer);
	printf("I am now going to return from the funciton!\n");
}

int main(int argc, char *argv[]){
	printf("addres of the exploit function is: %p\n", &exploit);
	TakeInput();
}
