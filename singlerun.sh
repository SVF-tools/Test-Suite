#/bin/bash
################################################
#
#  Script to run a test in $PTATEST/tests folder
#  ./singlerun *.c  analyze a single c file
#  Set TestScript to indicate which analysis/optimizations you want to test with
################################################

##remember to run ./setup script before running testings
CLANGFLAG='-Xclang -disable-O0-optnone -g -c -emit-llvm -I.'
LLVMOPTFLAG='-mem2reg -mergereturn'

TARGET=$1
COMPILELOG="compile.log"
### Add the fold of c files to be tested

### Add the test shell files
TestScripts="testwpa.sh"
#      testrc.sh
#	     testdvf.sh\
#	     testmssa.sh"


### remove previous compile log
rm -rf $COMPILELOG

if [ $# -eq 0 ]
  then
      echo "No test file specified"
      exit 1
fi
### start testing
	for testscript in $TestScripts 
	do
        ### test plain c program files
        echo $TARGET;
        if [[ $TARGET == *.c ]]; then
            FileName=$(dirname $TARGET)/`basename $TARGET .c`
		    $CLANG -I$PTATEST $CLANGFLAG $TARGET -o $FileName.bc >>$COMPILELOG 2>&1
		    $LLVMOPT $LLVMOPTFLAG $FileName.bc -o $FileName.opt
        elif [[ $TARGET == *.orig ]]; then
            FileName=$(dirname $TARGET)/`basename $TARGET .orig`
		    $LLVMOPT $LLVMOPTFLAG $FileName.orig -o $FileName.opt
        elif [[ $TARGET == *.bc ]]; then
            FileName=$(dirname $TARGET)/`basename $TARGET .bc`
		    $LLVMOPT $LLVMOPTFLAG $FileName.bc -o $FileName.opt
        else 
            echo "file format not supported"
            exit 1
        fi
		echo @@@analyzing $FileName.c with $testscript 
		$LLVMDIS $FileName.opt
		$PTATESTSCRIPTS/$testscript $FileName.opt $TESTWITHOPT
	done
echo analysis finished
