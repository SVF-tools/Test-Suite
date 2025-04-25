#include "aliascheck.h"
#include <ctime>

using namespace std;

int main(int argc, char **argv)
{
  time_t time = 0;
  tm* p1 = gmtime(&time);
  tm* p2 = gmtime(&time);
  tm* q1 = localtime(&time);
  tm* q2 = localtime(&time);

  MAYALIAS(p1, q1);
  MUSTALIAS(p1, p2);
  MUSTALIAS(q1, q2);


  return 0;
}
