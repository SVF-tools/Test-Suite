#!/bin/bash

sysOS=`uname -s`
if [[ $sysOS == "Darwin" ]]
then
    ${BASH_SOURCE%/*}/diff_tests_osx "$@"
elif [[ $sysOS == "Linux" ]]
then
    ${BASH_SOURCE%/*}/diff_tests_linux "$@"
else
   echo "Builds outside Ubuntu and macOS are not supported."
fi