#include <string.h>
#include "stdbool.h"
#define ALLOCA alloca

extern void svf_assert(bool);

#include <string.h>
#include "stdbool.h"
#define ALLOCA alloca

extern void svf_assert(bool);
// int a[2] = {1,2}
int main() {
    char * data;
    char * dataGoodBuffer = (char *)ALLOCA(2*sizeof(char));
    memset(dataGoodBuffer, 'A', 2); /* fill with 'A's */
    /* FLAW: Set data pointer to a small buffer */
    data = dataGoodBuffer;
    char dest[2];
    memcpy(dest, data, 2*sizeof(char));
    svf_assert(data[0] == 'A');
}