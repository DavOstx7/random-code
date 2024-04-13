#include <stdio.h>
#include <stdlib.h>

int exerciseArr(int row, int col, int arr[row][col]){ 
    printf("%d %d \n", row, col);
    double math = 0, physics = 0, cmath = 0, cphysics = 0;
    for (int i = 0; i < col; i ++){
        if(arr[0][i] > 0 && arr[0][1] < 101)
        {
            math += arr[0][i];
            cmath++;
        }
    }

    for (int i = 0; i < col; i ++){
        if(arr[1][i] > 0 && arr[1][1] < 101)
        {
            physics += arr[1][i];
            cphysics++;
        }
    }
    double averages[2] = {math / cmath, physics / cphysics};
    printf("The average grade for math class is: %f, and the average grade for physics class is: %f", averages[0], averages[1]);
    return 0;
}

void guessNumberV1(int number){
    if(number == 555)
        printf("You guessed it right\n");
    if(number < 555)
        printf("Your guess is too low\n");
    if(number > 555)
        printf("Your guess is too high\n");
}

void guessNumberV2(int number){
    if(number == 555){
        printf("You guessed it right\n");
        return;
    } else if (number < 555){
        printf("Your guess is too low\n");
        return;
    }
    printf("Your guess is too high\n");
}

void arrayPractice(){
    int array[] = {1, 7, 2, 5, 3, 6, 10, 33};
    // let the compiler tell you the size by getting the total size of the array in bytes sizeof(a) and dividing it by the size of one element sizeof(a[0]):
    int size = sizeof(array) / sizeof(array[0]);
    int num;
    for (int i = 0; i < size; i++){
        num = array[i];
        if(num < 5){
            continue;
        }
        if(num > 10){
            break;
        }
        printf("%d ", num);
        
    }
    printf("\n");

}

void allocation(){
    int i, j;
    /* TODO: define the 2D pointer variable here */
    int *p1;

    /* TODO: complete the following line to allocate memory for holding three rows */
    int **pnumbers = (int **) malloc(3 * sizeof(int));

    /* TODO: allocate memory for storing the individual elements in a row */
    pnumbers[0] = (int *) malloc(1 * sizeof(int));
    pnumbers[1] = (int *) malloc(2 * sizeof(int));
    pnumbers[2] = (int *) malloc(3 * sizeof(int));

    pnumbers[0][0] = 1;
    pnumbers[1][0] = 1;
    pnumbers[1][1] = 1;
    pnumbers[2][0] = 1;
    pnumbers[2][1] = 2;
    pnumbers[2][2] = 1;

    for (i = 0; i < 3; i++) {
        for (j = 0; j <= i; j++) {
            printf("%d", pnumbers[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < 3; i++) {
        /* TODO: free memory allocated for each row */
        free(pnumbers[i]); //free *pnumbers + 1
    }

    /* TODO: free the top-level pointer */
    free(pnumbers);

}

int factorial(n){
    if(n == 0){
        return 1;
    }
    return n * factorial(n-1);
}

int main(){
    int grades[2][3] = {{90, 90, 90}, {70, 100, 60}};
    int r = 2;
    int c = 3;
    //exerciseArr(r, c, grades); 

    //guessNumberV1(555);
    //guessNumberV2(555);

    //arrayPractice();

    //allocation();

    printf("%d\n", factorial(5));
    return 0;

}