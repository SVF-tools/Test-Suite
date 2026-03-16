#include <string.h>
#include "stdbool.h"
#define ALLOCA alloca

extern void svf_assert(bool);

typedef struct _twoIntsStruct
{
    int intOne;
    int intTwo;
} twoIntsStruct;

int main() {
    twoIntsStruct * data;
    twoIntsStruct * dataBadBuffer = (twoIntsStruct *)ALLOCA((4)*sizeof(twoIntsStruct));
    /* FLAW: Set a pointer to a buffer that does not leave room for a NULL terminator when performing
     * string copies in the sinks  */
    data = dataBadBuffer;
    data[0].intOne = 10;
    data[1].intOne = 11;
    data[2].intOne = 12;
    svf_assert(data[1].intOne == 11);
}