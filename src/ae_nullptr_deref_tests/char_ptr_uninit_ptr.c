
extern void UNSAFE_LOAD(void *ptr);

int main() {
    char *p;
    UNSAFE_LOAD(p);
}
