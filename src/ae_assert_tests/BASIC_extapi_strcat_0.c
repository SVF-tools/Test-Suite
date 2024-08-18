#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 假设 svf_assert 函数的声明
extern void svf_assert(bool);

int main() {
    char dest[20] = "Hello, "; // 目标字符串
    strcat(dest, "world!");    // 连接字符串
    svf_assert(strcmp(dest, "Hello, world!") == 0); // 使用 svf_assert 进行测试
    return 0;
}