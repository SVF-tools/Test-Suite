/*
 * A minimal extapi for blk_extapi_tests, passed to wpa with -extapi=.
 * It checks that SCANF:FormatArgN, not the function name, selects the
 * scanf handling of STORE_TOP outputs.
 */

/* scanf-like although its name does not contain "scanf". */
__attribute__((annotate("STORE_TOP:Arg2+"), annotate("SCANF:FormatArg1")))
int read_record(const char *src, const char *format, ...)
{
    return 0;
}

/* Stores unknown values through argument 1 onwards and has no format string. */
__attribute__((annotate("STORE_TOP:Arg1+")))
int fill_unknown(const char *tag, ...)
{
    return 0;
}
