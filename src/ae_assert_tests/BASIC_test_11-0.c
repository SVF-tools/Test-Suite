//scope testing, pass

#include "stdbool.h"
extern void svf_assert(bool);

int main() {
    int data = 0;
    {
        int data = 1;
        {
            int data = 2;
        }
        svf_assert(data == 1);
    }
	return 0;
}