#include "aliascheck.h"

// The code produced by these macros looks like:
//   call XALIAS(...)
//   %1 = load ...
//   ...
//   %n = load %p
//   store ... %n-1, ...* %n !ctir !t1
//   call deref()
//   %n+1 = load ...
//   ...
//   %n+n = load %q
//   store ... %n+n-1, ...* %n+n !ctir !t2
//   call deref()
// We want to test the points-to sets of %n and
// %n+n after filtering with !t1 and !t2 respectively.
// Clang producing ctir annotations necessary.

void deref(void) { }

#define TBHC_MUSTALIAS(p, q) {\
    MUSTALIAS(p, q);\
    *p = *p;\
    deref();\
    *q = *q;\
    deref();\
}

#define TBHC_PARTIALALIAS(p, q) {\
    PARTIALALIAS(p, q);\
    *p = *p;\
    deref();\
    *q = *q;\
    deref();\
}

#define TBHC_MAYALIAS(p, q) {\
    MAYALIAS(p, q);\
    *p = *p;\
    deref();\
    *q = *q;\
    deref();\
}

#define TBHC_NOALIAS(p, q) {\
    NOALIAS(p, q);\
    *p = *p;\
    deref();\
    *q = *q;\
    deref();\
}

#define TBHC_EXPECTEDFAIL_MAYALIAS(p, q) {\
    EXPECTEDFAIL_MAYALIAS(p, q);\
    *p = *p;\
    deref();\
    *q = *q;\
    deref();\
}

#define TBHC_EXPECTEDFAIL_NOALIAS(p, q) {\
    EXPECTEDFAIL_NOALIAS(p, q);\
    *p = *p;\
    deref();\
    *q = *q;\
    deref();\
}

