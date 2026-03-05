#include "stdbool.h"
extern void svf_assert(bool);

int mc91(int p){
    if(p > 100){
        return p - 10;
    }else{
        int p1 = p + 11;
        int p2 = mc91(p1);
        int result = mc91(p2);
        return result;
    }
}

int main(){
    int result = mc91(60);
    svf_assert(result >=91);
}