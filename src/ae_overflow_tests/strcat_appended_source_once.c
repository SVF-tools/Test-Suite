/* d holds "" and s holds "A", so strcat writes d[0] = 'A' and d[1] = 0:
 * the last byte written is d[1], inside char[2]. Without the fix, AE
 * appends s twice, overwriting the terminator with a second 'A', so
 * strlen(d) becomes 2 and the access appears to overflow. */
#include <string.h>
extern void svf_assert(int);
extern void SAFE_BUFACCESS(void *buffer, int size);
int main(void)
{
    char s[2], d[2] = "";
    s[0] = 'A';
    s[1] = 0;
    strcat(d, s);
    svf_assert(d[1] == 0);
    /* The last byte strcat writes is d[strlen(d)]. */
    SAFE_BUFACCESS(d, strlen(d));
    return 0;
}
