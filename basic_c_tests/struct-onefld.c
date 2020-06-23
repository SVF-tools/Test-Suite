/*
 * Struct with one field.
 * Author: Sen Ye
 * Date: 28/04/2014
 */
#include "aliascheck.h"

struct IntStruct {
	int f1;
};

struct CharStruct {
	char f1;
};

int main() {
	struct IntStruct* pint1, *pint2;
	struct IntStruct s;
	pint1 = &s;
	pint2 = &s;
	MUSTALIAS(&pint1->f1, &pint2->f1);
	MUSTALIAS(&pint1->f1, &s.f1);
	
	struct CharStruct* qint1, *qint2;
	struct CharStruct t;
	qint1 = &t;
	qint2 = &t;
	MUSTALIAS(&qint1->f1, &qint2->f1);
	MUSTALIAS(&qint1->f1, &t.f1);

	return 0;
}
