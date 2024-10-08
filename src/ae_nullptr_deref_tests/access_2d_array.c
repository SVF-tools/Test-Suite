#include <stdio.h>
int main() {
    int (*arr)[3] = NULL;
    int value = arr[0][0];  // This will trigger a null pointer dereference
}