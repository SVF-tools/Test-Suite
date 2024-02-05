#include <string.h>
#include "stdbool.h"

#define ALLOCA alloca

extern void svf_assert(bool);

int main() {
    char * data;
    char * dataBadBuffer = (char *)ALLOCA((4)*sizeof(char));
    /* FLAW: Set a pointer to a buffer that does not leave room for a NULL terminator when performing
     * string copies in the sinks  */
    data = dataBadBuffer;
    data[0] = 'A';
    data[1] = 'A';
    data[2] = 'A';
    svf_assert(data[1] == 'A');
}