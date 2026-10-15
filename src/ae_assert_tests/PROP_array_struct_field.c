#include <stdbool.h>

extern void svf_assert(bool);

struct Record
{
    int tag;
    int data[2];
};

int main(void)
{
    struct Record records[2] = {{1, {2, 3}}, {4, {5, 6}}};
    records[1].data[1] = 9;
    // Array element and struct-field indices must select the same sub-Obj.
    svf_assert(records[1].data[1] == 9);
    svf_assert(records[1].data[0] == 5);
    svf_assert(records[0].data[1] == 3);
    return 0;
}
