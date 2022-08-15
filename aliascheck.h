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

void LOCK(char* lockname) {

}

void PAUSE(char* str){
  printf("%s\n", str);
  printf("Press ENTER to continue\n");
  getchar();
}

