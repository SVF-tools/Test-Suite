#include "std_testcase.h"

#ifndef OMITBAD

void CWE122_Heap_Based_Buffer_Overflow__realloc_01_bad()
{
    char * data;
    data = NULL;
    /* Allocate initial memory */
    data = (char *)malloc(100 * sizeof(char));
    if (data == NULL) {exit(-1);}
    strcpy(data, "This is a long string that exceeds the reallocated buffer size.");
    /* FLAW: Reallocate to a smaller buffer without checking */
    data = (char *)realloc(data, 50 * sizeof(char));
    if (data == NULL) {exit(-1);}
    {
        char dest[50] = "";
        size_t i;
        /* POTENTIAL FLAW: Possible buffer overflow if data is larger than dest */
        for (i = 0; i < strlen(data); i++)
        {
            dest[i] = data[i];
        }
        UNSAFE_BUFACCESS(dest, (strlen(data) - 1) * sizeof(char));
        dest[49] = '\0'; /* Ensure null termination */
        printLine(dest);
        free(data);
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B()
{
    char * data;
    data = NULL;
    /* Allocate initial memory */
    data = (char *)malloc(50 * sizeof(char));
    if (data == NULL) {exit(-1);}
    strcpy(data, "Short string");
    /* FIX: Reallocate to a larger buffer if necessary */
    data = (char *)realloc(data, 100 * sizeof(char));
    if (data == NULL) {exit(-1);}
    strcat(data, " with additional data that fits.");
    {
        char dest[100] = "";
        size_t i;
        /* SAFE: Copy data to dest safely */
        for (i = 0; i < 99; i++)
        {
            dest[i] = data[i];
            SAFE_BUFACCESS(dest, i * sizeof(char));
        }
        dest[99] = '\0'; /* Ensure null termination */
        printLine(dest);
        free(data);
    }
}

void CWE122_Heap_Based_Buffer_Overflow__realloc_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
 * its own for testing or for building a binary to use in testing binary
 * analysis tools. It is not used when compiling all the testcases as one
 * application, which is how source code analysis tools are tested.
 */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__realloc_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE122_Heap_Based_Buffer_Overflow__realloc_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif