/*
Program description: In this program, data is allocated memory for 100 integers, which are all assigned as 5 using a for loop. Then, the memory that was allocated to data is freed. Finally, the first element of data is printed out 

Vulnerability and consequence: However, after data is deallocated with free, the program tries to print the first element of data, which causes a use after free error

The vulnerability triggers in the following lines:
printf("%d\n", data[0]);

Mitigation: To make this program safe to run, ensure that data is only freed after the first element of data is printed out. Therefore, only free data when there are no more uses for data. To check if the data has been freed or not, assign data to NULL after using free, then perform a NULL check
*/
#define ALLOCA alloca

#include <stdlib.h>
int main() {
    int * data = (int *)ALLOCA(2 * sizeof(int));
    data[0] = 0;
    data[1] = 1;
    if (data[1] != 1) {
        free(data);
        data = NULL;
    }
    svf_assert(data != NULL);
    return 0;
}