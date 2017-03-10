/////////////////////////////////////////////////////////////////////////
%{
    #include "AST/AST.hpp"
    #include "AST/Node.hpp"
    #include "IRDefinition.hpp"
    #include <iostream>

    using namespace IRDefinition;
    using namespace SubtypesArithmetic;

    using namespace Compiler;
    using namespace AST;

    Block *programBlock;

    extern int yylex();
    void yyerror(const char *s) { std::cout << "ERROR: " << s << std::endl; }
%}

/////////////////////////////////////////////////////////////////////////
//
%union {
    Compiler::AST::Node *node;
    Compiler::AST::Block *block;
    Compiler::AST::Expr *expr;
    Compiler::AST::Statement *stmt;
    std::vector<Compiler::AST::Statement> *stmts;
    std::string *string;
    int token;
}

/////////////////////////////////////////////////////////////////////////
// Tokens

%left TPLUS TMINUS
%left TMUL TDIV

%token <string> TINTEGER
%token <token> TPLUS TMINUS TMUL TDIV
%token <token> TSEMICOLON TLPAREN TRPAREN

%type <expr> numeric expr term factor
%type <block> program stmts block
%type <stmt> stmt

/////////////////////////////////////////////////////////////////////////
// Parsing of program
%start program

%%

program : block { programBlock = $1; }
        ;

block: stmts
      ;

stmts : stmt TSEMICOLON { $$ = new Block(0); $$->statements.push_back($<stmt>1); }
      | stmts stmt TSEMICOLON { $1->statements.push_back($<stmt>2);  }
      ;

stmt : expr { /*$$ = new ExprStmt($1);*/ }
     ;

expr : expr TPLUS  expr { $$ = new BinaryOp($1, IR_ADD, $3, 0); }
     | expr TMINUS expr { $$ = new BinaryOp($1, IR_SUB, $3, 0); }
     | term
     ;

term : term TMUL factor { $$ = new BinaryOp($1, IR_MUL, $3, 0); }
     | term TDIV factor { $$ = new BinaryOp($1, IR_DIV, $3, 0); }
     | factor
     ;

factor : TLPAREN expr TRPAREN { $$ = $2; }
       | numeric { $$ = $1; }
       ;

numeric : TINTEGER { $$ = new Literal(atol($1->c_str()), kBasicTypeId::kInt, 0);  delete $1; }
        ;

%%
