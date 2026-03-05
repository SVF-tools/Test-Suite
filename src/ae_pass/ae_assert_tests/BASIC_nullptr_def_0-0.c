/*
Program description: In this program, the struct twoIntsStructPointer, contains two integers, twoIntsStructPointer->intOne and twoIntsStructPointer->intTwo, which are assigned as 5 and 3, respectively. Then, twoInstructPointer is set to NULL, and an if statement is used to check if twoIntsStructPointer is not equal to NULL and if twoIntsStructPointer->intOne is equal to 5. If the if condition holds true, then the program prints that twoIntsStructPointer->intOne is equal to 5

Vulnerability and consequence: However, the and operator (&) that is used in the if statement to check that twoIntsStructPointer is not equal to NULL and if the first integer in the struct is equal to 5 evaluates both sides of the and operator. Therefore, even though twoIntStructPointer is set to NULL, the program will still check if the first integer in the struct is equal to 5, thus causing a NULL pointer dereference

The vulnerability triggers in the following lines:
if ((twoIntsStructPointer != NULL) & (twoIntsStructPointer->intOne == 5))

Mitigation: To make this program safe to run, use the conditional and operator (&&) instead of the and operator (&) to ensure the right hand side of the operator is only evaluated if the left hand side of the operator is true, which avoids the NULL pointer dereference
*/

#include <stdlib.h>
#define ALLOCA alloca

typedef struct _twoIntsStruct {
	int intOne;
	int intTwo;
} twoIntsStruct;

int main() {
	twoIntsStruct * twoIntsStructPointer = (twoIntsStruct * )ALLOCA(sizeof(twoIntsStruct));
	twoIntsStructPointer->intOne = 5;
    twoIntsStructPointer->intTwo = 3;
    if (twoIntsStructPointer->intTwo < 0) {
        twoIntsStructPointer = NULL;
    }
	svf_assert(twoIntsStructPointer->intTwo == 3);// wrong assert should be !=
    //svf_assert(twoIntsStructPointer->intOne != 5 && twoIntsStructPointer->intTwo != 3);
	return 0;
}