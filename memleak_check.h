#include <stdio.h>
#include <stdlib.h>

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
