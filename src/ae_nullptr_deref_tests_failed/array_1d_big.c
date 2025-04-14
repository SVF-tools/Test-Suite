#include <stdio.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

#define SIZE 100

int main() {
    int *arr[SIZE];
    
    for (int i = 0; i < SIZE; i++) {
            if (i < SIZE / 2) {
                arr[i] = NULL;
            } else {
                arr[i] = malloc(sizeof(int));
                *arr[i] = 1024;
            }
    }

    for (int i = 0; i < SIZE; i++) {
        if (i < SIZE / 2)
            UNSAFE_LOAD(arr[i]); 
        else
            SAFE_LOAD(arr[i]);
    }

    return 0;
}