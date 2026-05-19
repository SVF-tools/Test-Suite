extern void svf_assert(int);
extern int* malloc(int);
int no_main_BASIC_br_nd_malloc_0(int argc){
    int* p = malloc(10);
    *p = 10;
    if(argc){
        *p = 20;
    }
    else{
        svf_assert(*p==10);
    }
}
