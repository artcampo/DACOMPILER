#include <iostream>
#include "Node.h"
#include "ASTVisitorCodeGenerator.hpp"
#include "ASTVisitorPrettyPrinter.hpp"
#include "ASTVisitorCodeGenerator.hpp"

// using namespace AST_Nodes;
extern Block* programBlock;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();

    std::cout << "Print AST\n";
    
//     ASTVisitorPrettyPrinter visitor;
//     visitor.Visit(*programBlock);
    
    ASTVisitorCodeGenerator visitor;
    visitor.Visit(*programBlock);
    
    visitor.Print();
    
    return 0;
}