#include <stdio.h>
#include <stdlib.h>

void MUSTALIAS(void* p, void* q){
  printf("\n");
}

void PARTIALALIAS(void* p, void* q){
  printf("\n");
}

void MAYALIAS(void* p, void* q){
  printf("\n");
}

void NOALIAS(void* p, void* q){
  printf("\n");
}

void EXPECTEDFAIL_MAYALIAS(void* p, void* q){
  printf("\n");
}

void EXPECTEDFAIL_NOALIAS(void* p, void* q){
  printf("\n");
}

// safe malloc
void* SAFEMALLOC(int n){
  return malloc(n);
}
// partial leak malloc
void* PLKMALLOC(int n){
  return malloc(n);
}
/// never free malloc
void* NFRMALLOC(int n){
  return malloc(n);
}
/// context leak malloc
void* CLKMALLOC(int n){
  return malloc(n);
}
/// expected never free false positive leak
void* NFRLEAKFP(int n){
  return malloc(n);
}
/// expected partial leak false positive leak
void* PLKLEAKFP(int n){
  return malloc(n);
}
/// expected leak false negative leak
void* LEAKFN(int n){
  return malloc(n);
}

// ****************************************************************************************
// RC_ACCESS is used for concurrency analysis validation.
// The target memory access is indicated as the closest memory access before its call site.
// The function calls of RC_ACCESS should always appear in pairs.
//   - Parameter #1 pairId: the id of pairs that RC_ACCESS occurs.
//   - Parameter #2 p: the validation flags, whose predefined values are shown below.
void RC_ACCESS(int id, int flags) {
  printf("\n");
}

// Predefined flag values for RC_ACCESS.
#define RC_MHP 0x01
#define RC_ALIAS 0x02
#define RC_PROTECTED 0x04
#define RC_RACE 0x10

// ****************************************************************************************
// MTA Validation
void CXT_THREAD(int thdid, char* cxt) {
  //printf("\n");
}
void TCT_ACCESS(int thdid,char* cxt){
  //printf("\n");
}
void INTERLEV_ACCESS(int thdid,char* cxt, char* lev){
  //printf("\n");
}

void PAUSE(char* str){
  printf("%s\n", str);
  printf("Press ENTER to continue\n");
  getchar();
}

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
