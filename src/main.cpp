#include <iostream>
#include "Node.h"
#include "CodeGenerator.h"

// using namespace AST_Nodes;
extern Block* programBlock;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();

    CodeGenerator::printAST(programBlock);
    
    return 0;
}