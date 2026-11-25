/* p may point to either string, so strcpy(dst, p) may write the 15-character
 * string plus its terminator, up to dst[15], past the end of char[8].
 * strlen(p) must cover both sources, [3, 15]. Without the fix, AE takes the
 * length from only one of them ([4, 4]) and misses the overflow. */
#include <string.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);
int main(int argc, char **argv)
{
    char longer[16] = "abcdefghijklmno";
    char shorter[4] = "abc";
    char *p = argc > 1 ? longer : shorter;
    char dst[8];
    strcpy(dst, p);
    /* The last byte strcpy writes is dst[strlen(p)]. */
    UNSAFE_BUFACCESS(dst, strlen(p));
    return 0;
}
