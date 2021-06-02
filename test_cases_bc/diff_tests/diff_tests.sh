#!/bin/bash

sysOS=`uname -s`
echo $sysOS
if [[ $sysOS == "Darwin" ]]
then
    ./diff_tests_osx $@
elif [[ $sysOS == "Linux" ]]
then
    ./diff_tests_linux $@
fi