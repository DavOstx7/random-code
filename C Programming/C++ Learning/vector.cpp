#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector <int> v1(4); //create a vector with 4 slots. automatically put's 0's in it.
    v1[0] = 13;
    cout << "v1[0] ||| v1[3] = " << v1[0] << " ||| " << v1[3] << endl;
    cout << "the current size of v1 is: " << v1.size() << endl;
    // int popped = v1.pop_back(); // doesn't have a return value;
    v1.pop_back();
    cout << "the current size of v1 is: " << v1.size() << endl;

    vector <int> v2; // = vector <int> v2(0);. You can't do vector <int> v2();.
    // cout << v2[3]; // this doesn't give an error, but it just crashes it.
    v2.push_back(1), v2.push_back(2);
    cout << "[" << &v2[0] << "] = " << v2[0] << ", [" << &v2[1] << "] = " << v2[1] << endl;

    int arr[] = {1,23};
    cout << "arr: " << &arr << " " << &arr[0] << endl;

    vector <int> v3(2);
    cout << "vector: " << &v3 << " " << &v3[0] << endl;

    cout << "arr: " << *arr << " " << *(arr + 1) << endl;
    // cout << "vector: " << *v3 << " " << *(v3 + 1) << endl; // error.

    vector <double> v4 = {132, 43.1, 3.04}; // can initialize like this.
    cout << v4[1] << endl;

    // filling a vector of vector. (If we would like to fill it like a 2D array, we would need to specify first the sizes.)
    vector <vector <int> > v5;
    for (int i = 0; i < 4; i++)
    {
        vector<int> temp;
        if(i == 0 or i == 3)
        {
            for (int j = 0; j < 3; j++)
            {
                temp.push_back(i);
            }
        } else 
        {
            for (int j = 0; j < 5; j++)
            {
                temp.push_back(i);
            }
        }
        v5.push_back(temp);
    }
    
    for (int i = 0; i < v5.size(); i++)
    {
        //first way:
        vector <int> tmp = v5[i];
        for (int j = 0; j < tmp.size(); j++)
        {
            cout << tmp[j];
        }
        cout << endl;

        //second way:
        for (int j = 0; j < v5[i].size(); j++)
        {
            cout << v5[i][j];
        }
        cout << endl;
        
        
    }
    

    return 0;
}
