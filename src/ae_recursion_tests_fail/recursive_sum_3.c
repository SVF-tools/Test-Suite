void tp_trigger(){
    int idx = 2;
    char arr[2];
    arr[idx] = 'a';
}

void fp_trigger(){
    int idx = 2;
    char arr[2];
    arr[idx] = 'a';
}

int sum(int n, int m) {
    if (n <= 0) {
        return m + n;
    } else {
        return sum(n - 1, m + 1);
    }
}

int main(){
    int a = 10;
    int b = 3;
    int res = sum(a, b);
    if(res > 3){
        fp_trigger();
    }
    tp_trigger();
}