/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE122_Heap_Based_Buffer_Overflow__c_CWE805_struct_loop_01.c
Label Definition File: CWE122_Heap_Based_Buffer_Overflow__c_CWE805.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 122 Heap Based Buffer Overflow
 * BadSource: Allocate buffer for fewer elements than needed
 * GoodSource: Allocate buffer with sufficient elements
 * Sink: loop
 *    BadSink : Copy struct array to data using a loop
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#ifndef OMITBAD

void CWE122_Heap_Based_Buffer_Overflow__c_CWE805_struct_loop_01_bad()
{
    twoIntsStruct * data;
    data = NULL;
    /* FLAW: Allocate buffer for 5 elements */
    data = (twoIntsStruct *)malloc(5 * sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    {
        twoIntsStruct source[10];
        size_t i;
        /* Initialize source array */
        for (i = 0; i < 10; i++)
        {
            source[i].intOne = (int)i;
            source[i].intTwo = (int)i;
        }
        /* POTENTIAL FLAW: Possible buffer overflow if data has fewer than 10 elements */
        for (i = 0; i < 10; i++)
        {
            data[i] = source[i];
            if (i > 5)
                UNSAFE_BUFACCESS(data, i * sizeof(twoIntsStruct));
        }
        printStructLine(&data[0]);
        free(data);
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B()
{
    twoIntsStruct * data;
    data = NULL;
    /* FIX: Allocate buffer for 10 elements */
    data = (twoIntsStruct *)malloc(10 * sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    {
        twoIntsStruct source[10];
        size_t i;
        /* Initialize source array */
        for (i = 0; i < 10; i++)
        {
            source[i].intOne = (int)i;
            source[i].intTwo = (int)i;
        }
        /* SAFE: data has enough space for the copy operation */
        for (i = 0; i < 10; i++)
        {
            data[i] = source[i];
            SAFE_BUFACCESS(data, i * sizeof(twoIntsStruct));
        }
        printStructLine(&data[0]);
        free(data);
    }
}

void CWE122_Heap_Based_Buffer_Overflow__c_CWE805_struct_loop_01_good()
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
    CWE122_Heap_Based_Buffer_Overflow__c_CWE805_struct_loop_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE122_Heap_Based_Buffer_Overflow__c_CWE805_struct_loop_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
