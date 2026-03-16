#include "stdbool.h"
#include <stdint.h>
extern void svf_assert(bool);
int main() {
    int64_t largeValue = 256; // 假设我们有一个int64_t的值
    int8_t truncatedValue = (int8_t)largeValue; // trunc to int8_t
    // 由于256超出了int8_t的表示范围(-128到127)，所以这里会回绕到0
    svf_assert(truncatedValue == 0);
    return 0;
}