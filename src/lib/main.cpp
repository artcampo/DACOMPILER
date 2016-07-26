#include "Node.hpp"
#include "Utils.hpp"
#include "ASTVisitorCodeGenerator.hpp"
#include "ASTVisitorPrettyPrinter.hpp"
#include <iostream>
#include <fstream>

// using namespace AST_Nodes;
extern Block* programBlock;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();

    {
    std::cout << "Print AST\n";
    ASTVisitorPrettyPrinter visitor;
    visitor.Visit(*programBlock);
    }
    
    std::cout << "--------------------------\n";
    std::cout << "ByteCode:\n";
    ASTVisitorCodeGenerator visitor;
    visitor.Visit(*programBlock);
    visitor.EndOfProgram();
    
    visitor.Print();
    
    if(argc == 2){
      VMUtils::writeByteCode( visitor.byte_code(), std::string(argv[1]) );
      
//       std::cout << "--------------------------\n";
//       std::cout << "Bytecode written to: " << argv[1] << "\n";
    }
    
    return 0;
}