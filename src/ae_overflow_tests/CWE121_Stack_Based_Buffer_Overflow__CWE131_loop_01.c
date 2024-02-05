/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE121_Stack_Based_Buffer_Overflow__CWE131_loop_01.c
Label Definition File: CWE121_Stack_Based_Buffer_Overflow__CWE131.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 121 Stack Based Buffer Overflow
 * BadSource:  Allocate memory without using sizeof(int)
 * GoodSource: Allocate memory using sizeof(int)
 * Sink: loop
 *    BadSink : Copy array to data using a loop
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#ifndef OMITBAD

void CWE121_Stack_Based_Buffer_Overflow__CWE131_loop_01_bad()
{
    int * data;
    data = NULL;
    /* FLAW: Allocate memory without using sizeof(int) */
    data = (int *)ALLOCA(10);
    {
        int source[10] = {0};
        size_t i;
        /* POTENTIAL FLAW: Possible buffer overflow if data was not allocated correctly in the source */
        for (i = 0; i < 10; i++)
        {
            data[i] = source[i];
        }
        SAFE_BUFACCESS(source, 10 * sizeof(int) - 1);
        UNSAFE_BUFACCESS(data, 10 * sizeof(int) - 1);
        printIntLine(data[0]);
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    int * data;
    data = NULL;
    /* FIX: Allocate memory using sizeof(int) */
    data = (int *)ALLOCA(10*sizeof(int));
    {
        int source[10] = {0};
        size_t i;
        /* POTENTIAL FLAW: Possible buffer overflow if data was not allocated correctly in the source */
        for (i = 0; i < 10; i++)
        {
            data[i] = source[i];
            SAFE_BUFACCESS(data, (i+1) * sizeof(int) - 1);
            SAFE_BUFACCESS(source, (i+1) * sizeof(int) - 1);
        }
        SAFE_BUFACCESS(source, 10 * sizeof(int) - 1);
        SAFE_BUFACCESS(data, 10 * sizeof(int) - 1);

        printIntLine(data[0]);
    }
}

void CWE121_Stack_Based_Buffer_Overflow__CWE131_loop_01_good()
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
    CWE121_Stack_Based_Buffer_Overflow__CWE131_loop_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE121_Stack_Based_Buffer_Overflow__CWE131_loop_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
