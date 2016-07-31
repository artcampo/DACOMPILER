cd install/tests

#test1
./dacomp test1.bc < test1.txt > test1.out
cp test1.out ../../src/tests/verification/test1.ver
cp test1.bc  ../../src/tests/verification/test1.bc.ver

#test2
./dacomp test2.bc < test2.txt > test2.out
cp test2.out ../../src/tests/verification/test2.ver
cp test2.bc  ../../src/tests/verification/test2.bc.ver

#end
echo "Tests regenerated. You need to reinstall before running tests again."