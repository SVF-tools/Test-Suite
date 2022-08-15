/*
 * double free
 * Author: Jiawei Ren
 * Date: 03/02/2022
 */


/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_struct_17.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-17.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 17 Control flow: for loops
 *
 * */

#include "std_testcase.h"

#include <wchar.h>
#include "doublefree_check.h"



void CWE415_Double_Free__malloc_free_struct_17_bad()
{
    int i,j;
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    for(i = 0; i < 1; i++)
    {
        data = (twoIntsStruct *)DOUBLEFREEMALLOC(100*sizeof(twoIntsStruct));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        SAFEFREE(data);
    }
    for(j = 0; j < 1; j++)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        DOUBLEFREE(data);
    }
}


/* goodB2G() - use badsource and goodsink in the for statements */
static void goodB2G()
{
    int i,k;
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    for(i = 0; i < 1; i++)
    {
        data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        SAFEFREE(data);
    }
    for(k = 0; k < 1; k++)
    {
        /* do nothing */
        /* FIX: Don't attempt to free the memory */
        ; /* empty statement needed for some flow variants */
    }
}

/* goodG2B() - use goodsource and badsink in the for statements */
static void goodG2B()
{
    int h,j;
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    for(h = 0; h < 1; h++)
    {
        data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
        if (data == NULL) {exit(-1);}
        /* FIX: Do NOT free data in the source - the bad sink frees data */
    }
    for(j = 0; j < 1; j++)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        DOUBLEFREE_FP(data);
    }
}

void CWE415_Double_Free__malloc_free_struct_17_good()
{
    goodB2G();
    goodG2B();
}

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */


int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
    CWE415_Double_Free__malloc_free_struct_17_good();
    CWE415_Double_Free__malloc_free_struct_17_bad();
    return 0;
}

