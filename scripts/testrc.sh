#/bin/bash
###############################
#
# Script to test WPA, change variables and options for testing
#
##############################

TNAME=mta
###########SET variables and options when testing using executable file
EXEFILE=$PTABIN/mta    ### Add the tools here for testing
FLAGS="-stat=false -mhp " #-print-pts" # -dump-pag'  ### Add the FLAGS here for testing
#echo testing MSSA with flag $FLAGS

###########SET variables and options when testing using loadable so file invoked by opt
LLVMFLAGS="-mem2reg -rc -ander --debug-pass=Structure " #'-count-aa -dse -disable-opt -disable-inlining -disable-internalize'
LIBNAME=lib$TNAME

############don't need to touch here (please see run.sh script for meaning of the parameters)##########
if [[ $2 == 'opt' ]]
then
  $RUNSCRIPT $1 $TNAME "$LLVMFLAGS" $2
else
  $RUNSCRIPT $1 $TNAME "$FLAGS" $2
fi
