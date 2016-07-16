cd install/tests
#test1
./dacomp < test1.txt > test1.out
diff test1.out test1.ver
rm test1.out
#test2
./dacomp < test2.txt > test2.out
diff test2.out test2.ver
rm test2.out