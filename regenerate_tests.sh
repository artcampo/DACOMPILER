cd install/tests

regenerate(){
    ./dacomp $1.bc < $1.txt > $1.out
    cp $1.out ../../src/tests/verification/$1.ver
    cp $1.bc  ../../src/tests/verification/$1.bc.ver
    rm $1.out
}

regenerate test1
regenerate test2
regenerate test3

#end
echo "Tests regenerated. You need to reinstall before running tests again."