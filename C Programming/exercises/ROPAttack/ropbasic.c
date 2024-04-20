#include <stdio.h>
#include <string.h>

void exploit(){
	printf("Entered exploit function!");
}

void TakeInput(){
	printf("Copying input for a buffer of size 5 bytes\nWaiting for enter: ");
	char buffer[5];
	//scanf("%s", buffer); don't work - can't find a solution to give \x89
	getchar();
	unsigned char* my_env_var = getenv("MY_ENV_VAR");
	strcpy(buffer, my_env_var);

	printf("I am now going to return from the funciton!\n");
}

int main(int argc, char *argv[]){
	printf("addres of the exploit function is: %p\n", &exploit);
	TakeInput();
}
