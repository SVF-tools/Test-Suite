extern void svf_assert(int);
extern int* malloc(int);
int main(int argc){
    int* p = malloc(10);
    *p = 10;
    if(argc){
        *p = 20;
    }
    else{
        svf_assert(*p==10);
    }
}
