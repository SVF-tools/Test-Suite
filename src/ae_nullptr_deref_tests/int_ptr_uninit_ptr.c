
extern void UNSAFE_LOAD(void *ptr);

int main() {
  int* p;
  UNSAFE_LOAD(p);
}
