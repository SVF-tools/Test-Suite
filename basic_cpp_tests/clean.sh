#!/bin/bash
for i in `find . -name '*.ll'`
do
	echo delete $i
	rm -rf $i
done
for i in `find . -name '*.wpa'`
do
	echo delete $i
	rm -rf $i
done
