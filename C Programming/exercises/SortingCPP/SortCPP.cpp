#include <iostream>
#include <array>

using namespace std;

int cmp(const int& a1){
	return a1;
}

template<typename T, size_t N, typename v>
void sort(array<T,N>& arr, int (*cmpfunc)(v&)){

	int current_index = 0;
	while(current_index < N - 1)
	{
		int min_index = current_index;
		int min_val = arr[current_index];
		for (int j = current_index + 1; j < N; ++j)
		{
			if(arr[j] < min_val){
				min_index = j;
				min_val = arr[j];
			}
		}
		T tmp = arr[min_index];
		arr[min_index] = arr[current_index];
		arr[current_index] = tmp;
		++current_index;
	}
}
int main(){

	array<int, 5>arr = {65,2,-2,4,5};
	sort(arr, cmp);
	for (auto var: arr)
	{
		cout << var << endl;
	}

	return 0;
}