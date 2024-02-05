#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
 
int count = 0;

bool isPalindrome(char* word, int index) {
    count++;
    int length = strlen(word) - (index + 1);
    if (word[index] == word[length]) {
        if (index + 1 == length || index == length) {
            return true;
        }
        isPalindrome(word, index + 1);
    }
    else {
        return false;
    }
}
 
int main() {
    char* word;
    if(strlen(word) > 0) {    
        isPalindrome(word, 0);
        if(strlen(word) % 2 == 0) {
            svf_assert(count == strlen(word)/2);
        }
        else {
            svf_assert(count == (strlen(word) + 1)/2);
        }
    }
}
