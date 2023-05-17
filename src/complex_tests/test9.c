#include <wchar.h>
#include <wctype.h>
#include <stdio.h>

int main() {
    wchar_t wc = L'a';

    if (iswlower(wc)) {
        wprintf(L"The character is a lowercase letter.\n");
    } else {
        wprintf(L"The character is not a lowercase letter.\n");
    }
    
    wchar_t uc = towupper(wc);
    wprintf(L"The uppercase version of the character is %lc.\n", uc);

    return 0;
}
