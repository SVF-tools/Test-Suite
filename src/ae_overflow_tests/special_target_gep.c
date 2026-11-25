/* The external result has no known allocation size. AE must report the
 * alarm with an unbounded allocation size [0, +oo] and the real 4-byte
 * offset of p[1]. Without the fix it reports [0, 0] for both. */
extern int *unknown_pointer(void);
int main(void)
{
    int *p = unknown_pointer();
    p[1] = 0;
    return 0;
}
