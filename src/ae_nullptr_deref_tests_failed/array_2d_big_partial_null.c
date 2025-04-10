#include <stdio.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

#define SIZE 100

int main() {
    int *arr[SIZE][SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j < SIZE / 2) {
                arr[i][j] = NULL;
            } else {
                arr[i][j] = malloc(sizeof(int));
                *arr[i][j] = 1024;
            }
        }
    }

    for (int m = 0; m < SIZE; m++) {
        for (int n = 0; n < SIZE; n++) {
            if (n < SIZE / 2)
                UNSAFE_LOAD(arr[m][n]);
            else
                SAFE_LOAD(arr[m][n]);
        }
    }

    return 0;
}