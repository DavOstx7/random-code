#include <stdio.h>
#include <string.h>
#include <stdlib.h>
unsigned char retadd[8] = {0,0,0,0,0,0,0,0};
int counter = 0;

void exploit(){
	printf("%s\n", "Entered exploited funciton");
}

void vulnfunc(const char *input, const char *addr){ //input = input from terminal, addr = address of exploit func.
	printf("In vuln function, making a 4 bytes buffer!\n");
	unsigned char buffer[4]; //looking at gdb, its 25 bytes from the rbp. print $rbp - buffer
	buffer[0] = 0xff; //for testing what's the address.

	while (1){
		if(addr[counter] == '\0')
			break;
		if(addr[counter+1] == '\0')
		{
			char n[1] = {addr[counter]};
			int number = (int)strtol(n, NULL, 16);
			printf("value of number: %x\n", number);
			retadd[counter/2] = *((char *)&number);
			break;
		}
		char n[2] = {addr[counter], addr[counter+1]};
		int number = (int)strtol(n, NULL, 16);
		printf("value of number: %x\n", number);
		retadd[counter/2] = *((char *)&number);
		counter+=2;
	}

	printf("\n");
	int index;
	for (int i = 7; i > -1; i--)
	{
		if(retadd[i] != 0){
			index = i;
			break;
		}
	}
	for (int i = 0; i < index  / 2; ++i)
	{
		char tmp = retadd[index - i];
		retadd[index - i] = retadd[i];
		retadd[i] = tmp;
	}

	printf("printing the value of retadd after reverse: ");
	for (int i = 0; i < 8; ++i)
	{
		unsigned int val = retadd[i];
		printf("%08x ", val);
	}


	printf("\n");

	strcpy(buffer, "xxxxxxxxxxxxxxxxxxxxxxxxx12345678"); //this is for the buffer(25 bytes), and rbp (8 bytes).
	strcat(buffer, retadd);
	printf("%s\n", buffer);

	return;

}
int main(int *argc, char *argv[]){
	char tmpaddr[20];
	sprintf(tmpaddr,"%p", &exploit);
	char *addr = (char *)tmpaddr + 2;
	printf("%s%s\n", "Exploit function address: ", addr);
	vulnfunc(argv[1], addr);
	return 0;

}