//scope testing, pass

#include "stdbool.h"
extern void svf_assert(bool);

int no_main_BASIC_test_11_0() {
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