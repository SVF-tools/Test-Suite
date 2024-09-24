/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE122_Heap_Based_Buffer_Overflow__c_CWE680_int_overflow_01.c
Label Definition File: CWE122_Heap_Based_Buffer_Overflow__c_CWE680.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 122 Heap Based Buffer Overflow
 * BadSource: Set dataSize to a large value causing integer overflow
 * GoodSource: Set dataSize to a small, safe value
 * Sink: malloc
 *    BadSink : Allocate memory using malloc() and initialize it
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#ifndef OMITBAD

void CWE122_Heap_Based_Buffer_Overflow__c_CWE680_int_overflow_01_bad()
{
    int * data;
    int dataSize;
    /* FLAW: Set dataSize to a value that will cause an integer overflow in malloc */
    dataSize = INT_MAX / sizeof(int) + 2;
    /* POTENTIAL FLAW: dataSize * sizeof(int) may overflow to a small value */
    data = (int *)malloc(dataSize * sizeof(int));
    if (data == NULL) {exit(-1);}
    {
        size_t i;
        /* POTENTIAL FLAW: May write beyond allocated memory if dataSize * sizeof(int) overflows */
        for (i = 0; i < (size_t)dataSize; i++)
        {
            data[i] = 0;
        }
        UNSAFE_BUFACCESS(data, dataSize * sizeof(int) - 1);
        printIntLine(data[0]);
        free(data);
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B()
{
    int * data;
    int dataSize;
    /* FIX: Set dataSize to a small, safe value */
    dataSize = 20;
    data = (int *)malloc(dataSize * sizeof(int));
    if (data == NULL) {exit(-1);}
    {
        size_t i;
        /* SAFE: dataSize is small and does not cause overflow */
        for (i = 0; i < (size_t)dataSize; i++)
        {
            data[i] = 0;
            SAFE_BUFACCESS(data, i * sizeof(int));
        }
        printIntLine(data[0]);
        free(data);
    }
}

void CWE122_Heap_Based_Buffer_Overflow__c_CWE680_int_overflow_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__c_CWE680_int_overflow_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE122_Heap_Based_Buffer_Overflow__c_CWE680_int_overflow_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
