#include <iostream>
#include "Node.h"

// using namespace AST_Nodes;
extern Block* programBlock;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();
//     std::cout << programBlock << std::endl;
    return 0;
}