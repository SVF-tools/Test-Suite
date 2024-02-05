#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
	int ch;
	if (ch >= 97 && ch <= 122) {
		ch = toupper(ch);
		svf_assert(ch >= 65 && ch <= 90);
	}
}
