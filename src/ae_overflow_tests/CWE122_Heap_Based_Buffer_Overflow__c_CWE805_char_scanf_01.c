/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE122_Heap_Based_Buffer_Overflow__c_CWE805_char_scanf_01.c
Label Definition File: CWE122_Heap_Based_Buffer_Overflow__c_CWE805.label.xml
Template File: sources-sink-01.tmpl.c
*/
/*
 * @description
 * CWE: 122 Heap Based Buffer Overflow
 * BadSource: Allocate buffer of insufficient size
 * GoodSource: Allocate buffer with sufficient size
 * Sink: scanf
 *    BadSink : Read data from the console using scanf without limit
 * Flow Variant: 01 Baseline
 *
 * */

#include "std_testcase.h"

#ifndef OMITBAD

void CWE122_Heap_Based_Buffer_Overflow__c_CWE805_char_scanf_01_bad()
{
    char * data;
    data = NULL;
    /* FLAW: Allocate a small buffer */
    data = (char *)malloc(10 * sizeof(char));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Using scanf without specifying length limit */
    printLine("Enter a string:");
    scanf("%s", data); /* May cause buffer overflow */
    UNSAFE_BUFACCESS(data, strlen(data) * sizeof(char));
    printLine(data);
    free(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void goodG2B()
{
    char * data;
    data = NULL;
    /* FIX: Allocate a larger buffer */
    data = (char *)malloc(100 * sizeof(char));
    if (data == NULL) {exit(-1);}
    /* FIX: Use scanf with length limit */
    printLine("Enter a string:");
    scanf("%99s", data); /* Limits input to 99 characters */
    SAFE_BUFACCESS(data, 99 * sizeof(char));
    printLine(data);
    free(data);
}

void CWE122_Heap_Based_Buffer_Overflow__c_CWE805_char_scanf_01_good()
{
    goodG2B();
}

#endif /* OMITGOOD */

/* Below is the main(). It is used when building this testcase on its own
 * for testing or for building a binary to use in testing binary analysis tools.
 */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE122_Heap_Based_Buffer_Overflow__c_CWE805_char_scanf_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE122_Heap_Based_Buffer_Overflow__c_CWE805_char_scanf_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
