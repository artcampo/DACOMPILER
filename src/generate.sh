bison -d -o parser.cpp parser.y
flex -o tokens.cpp tokens.l
g++ -o parser parser.cpp tokens.cpp main.cpp