#!/bin/sh

cd install/tests

testscript() {
    ./dacomp $1.bc < $1.txt > $1.out
    diff $1.out $1.ver
    diff $1.bc $1.bc.ver
    rm $1.out
}

for i in `seq 1 2`
do
    testscript $i
done

echo "No messages of error means all tests passed."
