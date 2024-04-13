#include <iostream>
#include <iomanip>

using namespace std;

template<int R, int C>
struct Matrix{
private:
    int arr[R * C];
    int columns;
    int rows;
    int padding;
    int setI;
public:
    Matrix(): rows(R), columns(C), padding(0), setI(-1){
        for(int i = 0; i < rows * columns; i++){
            arr[i] = i;
        }
    }
    
    int operator[](int index){
        return arr[index];
    }
    
    
    void index(int r, int c, int value){
        arr[r * columns + c] = value;
    }
    
    void Print(){
        if(padding == 0){
            padding = find_padding();
        }
        for (int i = 0; i < rows * columns; i++) {
            if(i != 0 && i % columns == 0){
                cout << endl;
            }
            cout << setw(padding) << setfill('0') << arr[i] << " ";
        }
        cout << endl;
    }
    
    Matrix& set(int r, int c){
        setI = r  * columns + c;
        return (*this);
    }
    
    void value(int value){
        arr[setI] = value;
        setI = -1;
    }
private:
    int find_padding(){
        int max = arr[0];
        for(int i = 1; i < rows * columns; i++){
            
            if(arr[i] > max){
                max = arr[i];
            }
            
        }
        int count = 0;
        while(max != 0){
            count++;
            max/=10;
        }
        return count;
    }
};


int main()
{
    Matrix<5,4> a2d;
    
    a2d.index(1,2,23);
    
    a2d.set(1,1).value(3000);
    a2d.Print();
    
    return 0;
}
