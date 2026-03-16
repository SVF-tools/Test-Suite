#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

#define SIZE 100

int main() {
    int *arr[SIZE][SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = NULL;
        }
    }

    for (int m = 0; m < SIZE; m++) {
        for (int n = 0; n < SIZE; n++) {
            UNSAFE_LOAD(arr[m][n]);
        }
    }

    return 0;
}