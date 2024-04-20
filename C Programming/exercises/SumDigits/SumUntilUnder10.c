#include <stdio.h>

int SumDigits(int x){
	if(x == 0)
		return 0;
	return x % 10 + SumDigits(x / 10);
}

int MostReadable(int x){
	int y = x;
	while (1){ //can also do while(;;)
		y = SumDigits(y);
		if(y < 10)
			return y;
	}
}
int SumDigitsUnder10V1(int x){
	int y = x;
	while(y = SumDigits(y), y > 9)
		;
	return y; 

}

int SumDigitsUnder10V2(int x){
	int y = x;
	do{
		y = SumDigits(y);
	} while (y > 9);
	return y;
}

int SumDigitsUnder10V3(int x){
	if(x < 10){
		return x;
	}
	return SumDigitsUnder10V3(SumDigits(x));
}

int SumDigitsUnder10V4(int x){
	if(x < 10){
		return x;
	}
	return SumDigitsUnder10V4(x % 10 + SumDigitsUnder10V4(x / 10));
}

int SumDigitsUnder10V5(int x){
	if(x == 0){
		return 0;
	}
	return SumDigitsUnder10V4(x % 10 + SumDigitsUnder10V4(x / 10));
}

int SumDigitsMoreReadable(int x){
	if(x < 10)
		return x;
	return x % 10 + SumDigits(x / 10);
}
 
/* Take aways:
	At first I didn't realize why the function SumDigitsUnder10V4 works (I just remembered it did).
	The reason it wasn't clear is because the function SumDigits uses the if(x == 0) ---> return 0.
	If we would've used if(x < 10) --> return x (which is probably more effecient too), it would already make more sense.
	
	The steps to understand the solution is first under MostReadable:
	sum the number,
	check if it's under 10 and return if it is,
	else sum again.

	Then understand V3:
	First check if it's under 10, if yes return it, if not
	Then pass the sum of the number as a parameter,
	if it's under 10 return the sum,
	else pass the sum of the sum as a paramter, and so forth.

	The V4:
	It's basically the same as V3, but the two function's used are merged because of the if statement "(x < 10)"
	(That's why I said at the start that it was harder to understand when I used if(x == 0)).
	Explanation of the function:
	First check if the nubmer is under 10,
	If not pass the to the function the the most right digit + the function with the number without this right digit,
	which essentialy goes to the start of the function and when it returns the number under 10, and it sums up all of the digits,
	which get entered into the function which goes to the start of the function, which checks if the sum is under 10, if not,
	the process repeats it's self.
	You can view this function as first a check if the input is already smaller than 10, if not,
	sum up the digits using the first check, (the first check merges for the two purposes),
	and the sum gets entered back into the function as input.

	
	EDIT: I thought that the V5 function wouldn't work because it doesn't look right in the eyes and fit the question of
	"Sum untill it's under 10". But it functions the same way - the difference is that,
	instead of returning the number when it's smaller than 10,
	it calls the function with the number (number % 10 = number) and the sum of 0 (func(num/10) = return 0).
	The same concept, but it did help me see that the SumDigits function can be not as readable as the SumDigitsMoreReadable.
	

	EDIT 2: After looking at what these function do on paper, the V4 sums the most left digit,
	then adds to it the next most left digit, checks if its under 10, if yes it returns it, if not it sums it again
	and if it's under 10 it returns, if not it sums it and so forth and on (sums the first digit untill it's under 10,
	then the sums it with the next digit, untill the last digit). from seeing it it's probably less effecient,
	because all of the function calls. I can't even describe how V5 really works because of the calls. Same idea but with different
	if statement. The V5 one feels like it just spams the sum that it will for sure have to work, but,
	it sums the most left digit all the way(first), the adds the sum with the next digit and then sums it all the way,
	then adds it to the next digit and so forth. The way I look at it is it just sums to the fullest each (digit + sum),
	but you can look at it the same as V4, because whenever it gets to the point the input is under 10,
	it will always make an extra call which will just return 0 which essentialy returns the number that was under 10,
	Just like the function SumDigits and SumDigitsMoreReadable. Just look what happens when you give V5 one digit input like 4.

	conclusion:
	like the logic and and effeciency behind V4 and V5 is worse (V5 is way worse) + better use if(x < 10).
*/
int main(){
	printf("%d\n", 1); //replace 1 with the function name and parameter.
	return 0;
}