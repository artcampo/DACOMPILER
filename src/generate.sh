bison -d -o parser.cpp parser.y
flex -o tokens.cpp tokens.l
g++ -g -std=c++11 -o parser parser.cpp tokens.cpp main.cpp Node.cpp ASTVisitorPrettyPrinter.cpp 