FLAGS="-Xclang -disable-O0-optnone -g -c -emit-llvm"
FLAGS="${FLAGS} -I../ -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1"
FLAGS="${FLAGS} -std=c++11"
#FLAGS="-g ${FLAGS}"

FILES=`ls *.cpp`

find . -name "*.ll" -exec rm {} \;
find . -name "*.wpa" -exec rm {} \;
for file in ${FILES}
do
	file=${file%.*}
	echo ${file}
	$CLANGCPP ${FLAGS} -o ${file}.ll ${file}.cpp
	$LLVMOPT -mem2reg -S -o ${file}.mem2reg.ll ${file}.ll
	wpa -ander -stat=false ${file}.mem2reg.ll
done
