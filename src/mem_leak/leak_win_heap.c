/*
 * Win32 Heap Memory Leak Test for Saber
 * Validates HeapAlloc, LocalAlloc, and GlobalAlloc annotations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "memleak_check.h"

int main() {
    // 1. HeapAlloc leak - Never freed (Saber should detect NEVERFREE leak)
    char* p1 = (char*)HeapAlloc(GetProcessHeap(), 0, 100);

    // 2. LocalAlloc leak - Never freed (Saber should detect NEVERFREE leak)
    char* p2 = (char*)LocalAlloc(LMEM_FIXED, 100);

    // 3. HeapAlloc safe - Freed with HeapFree
    char* p3 = (char*)HeapAlloc(GetProcessHeap(), 0, 100);
    HeapFree(GetProcessHeap(), 0, p3);

    return 0;
}
