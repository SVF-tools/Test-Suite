#include <string.h>
#include "stdbool.h"
#define ALLOCA alloca

extern void svf_assert(bool);

int main() {
    char * data;
    char * dataBuffer = (char *)ALLOCA(3*sizeof(char));
    memset(dataBuffer, 'A', 3-1);
    dataBuffer[3-1] = '\0';
    /* FLAW: Set data pointer to before the allocated memory buffer */
    data = dataBuffer;
    char dest[2*2];
    memset(dest, 'C', 2*2-1); /* fill with 'C's */
    dest[2*2-1] = '\0'; /* null terminate */
    /* POTENTIAL FLAW: Possibly copy from a memory location located before the source buffer */
    strcpy(dest, data);
    svf_assert(data[0] == 'A');
}