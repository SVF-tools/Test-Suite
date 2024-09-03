#include <string.h>
#include "stdbool.h"
#define ALLOCA alloca

extern void svf_assert(bool);

int main() {
    int * data;
    int * dataBadBuffer = (int *)ALLOCA((4)*sizeof(int));
    /* FLAW: Set a pointer to a buffer that does not leave room for a NULL terminator when performing
     * string copies in the sinks  */
    data = dataBadBuffer;
    data[0] = 10;
    data[1] = 11;
    data[2] = 12;
    svf_assert(data[1] == 11);
}