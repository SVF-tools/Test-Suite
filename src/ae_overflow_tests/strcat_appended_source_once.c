/* d holds "" and s holds "A", so strcat writes d[0] = 'A' and d[1] = 0:
 * the last byte written is d[1], inside char[2]. AE must not report an
 * overflow. Without the fix, AE counts s twice and reports access size
 * [3, 3], which excludes the true access. */
#include <string.h>
int main(void)
{
    char s[2], d[2] = "";
    s[0] = 'A';
    s[1] = 0;
    strcat(d, s);
    return 0;
}
