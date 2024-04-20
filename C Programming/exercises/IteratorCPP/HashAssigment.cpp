#include <iostream>

using namespace std;


class HashTable{
private:
	static const u_int size = 26;
	string hashArr[size];
	string nev = "never used";
	string occ = "occupied";
	string tom = "tombstone";
public:
	HashTable(){
		for (int i = 0; i < size; ++i)
		{
			hashArr[i] = nev;
		}
	}

	u_int convertCtoI(const char& c) const{
		u_int val = *((int *)&c);
		if(val < 90){ //A = 61 ...
			return val - 65;
		}
		// a = 97;
		return val - 97;
	}

	u_int Search(const string& input) const{

		u_int index = convertCtoI(input[input.length()-1]);

		for (u_int i = index; i < size; ++i)
		{
			i = i % 26;
			if(hashArr[i] == nev)
				return -1;
			if(hashArr[i] == input)
				return i;
		}
		return -1;
	}

	void Insert(string input){
		if(Search(input) != -1)
			return;

		u_int index = convertCtoI(input[input.length()-1]);

		for (u_int i = index; i < size; ++i)
		{
			i = i % 26;
			if(hashArr[i] == nev || hashArr[i] == tom){
				hashArr[i] = input;
				return;
			}
			
		}
		cout << "something went wrong!\n";
	}

	void Delete(const string& input) {
		u_int location = Search(input);
		if(location == -1){
			cout << "can't delete! key not found\n";
			return;
		}
		hashArr[location] = tom;
	}

	void Print(){
		for (int i = 0; i < size; ++i)
		{
			if(hashArr[i] != nev && hashArr[i] != tom)
				cout << hashArr[i] << " ";
		}
		cout << endl;
	}
};
int main(){
	HashTable h;
	while (1){
		string input;
		cout << "Enter input: ";
		cin >> input;
		if(input == "")
			break;
		if(input[0] == 'A'){
			input.erase(0,1);
			h.Insert(input);
		}
		else if(input[0] == 'D'){
			input.erase(0,1);
			h.Delete(input);
		}
		else{
			cout << "Bad input!, exiting loop\n";
			break;
		}
	}
	h.Print();
	return 0;
}