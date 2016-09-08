#!/bin/sh

cd install/tests

regeneratescript() {
    ./dacomp test$1.bc < test$1.txt > test$1.out
    cp test$1.out test$1.ver
    cp test$1.bc ../../src/tests/verification/test$1.bc.ver
}

for i in `seq 1 2`
do
    echo "Regenerating test $i"
    regenerate $i
done

echo "Tests regenerated"
