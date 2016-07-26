#!/bin/sh 
cd install/tests

test(){
    ./dacomp $1.bc < $1.txt > $1.out
    diff $1.out $1.ver
    diff $1.bc $1.bc.ver
    rm $1.out
}

test test1
test test2

echo "No messages of error means all tests passed."
