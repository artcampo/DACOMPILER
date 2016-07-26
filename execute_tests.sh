cd install/tests

#test1
./dacomp test1.bc < test1.txt > test1.out
diff test1.out test1.ver
diff test1.bc test1.bc.ver
rm test1.out

#test2
./dacomp test2.bc < test2.txt > test2.out
diff test2.out test2.ver
diff test2.bc test2.bc.ver
rm test2.out

#end
echo "No messages of error means all tests passed."