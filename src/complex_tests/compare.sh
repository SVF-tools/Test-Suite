#!/bin/bash
if [ -z $PARFAIT ]; then
   PARFAIT="/usr/local/bin/parfait"
fi

echo "parfait is $PARFAIT"

for f in *.c; do
    fname=${f%.*}
    parfait-gcc -c $fname.c &> /dev/null
    $PARFAIT -d all -D pta --llvmpass=memanalysis $fname.o.bc &> temp
    out=./output/$fname.out
    if [ -e $out ]; then
        if [ ! $(cmp temp $out) ]; then
            echo "$fname.c results are identical"
        else
            echo "$fname.c diff dump :"
            diff temp $out
        fi
    else    
        echo "$fname.c results not found"
        mv temp $out
    fi     
done

