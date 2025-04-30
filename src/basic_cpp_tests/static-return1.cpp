#include "aliascheck.h"
#include <cerrno>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
{  
  char* p = getenv("HOME");
  char* q = getenv("HOME");

  MUSTALIAS(p, q);
}

{
  int* p = __errno_location();
  int* q = __errno_location();

  MUSTALIAS(p, q);
}

  return 0;
}
