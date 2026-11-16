/* The strcpy source may be either string. The 15-character one overflows
 * dst[8], so AE must report an overflow at the strcpy (line 12). Without
 * the fix, AE takes the length from only one of the possible sources and
 * reports nothing. */
#include <string.h>
int main(int argc, char **argv)
{
    char longer[16] = "abcdefghijklmno";
    char shorter[4] = "abc";
    char *p = argc > 1 ? longer : shorter;
    char dst[8];
    strcpy(dst, p);
    return 0;
}
