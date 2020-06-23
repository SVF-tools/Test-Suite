FLAGS="-Xclang -disable-O0-optnone -g -c -emit-llvm"
FLAGS="${FLAGS} -I../"
FLAGS="${FLAGS} -std=c++11"
#FLAGS="-g ${FLAGS}"

file="array-1"


$CLANGCPP ${FLAGS} -o ${file}.ll ${file}.cpp
$LLVMOPT -mem2reg -S -o ${file}.mem2reg.ll ${file}.ll
wpa -ander -stat=false ${file}.mem2reg.ll

