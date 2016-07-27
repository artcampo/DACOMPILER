%{
    #include "Node.hpp"
    #include <iostream>
    Block *programBlock; /* the top level root node of our final AST */

    extern int yylex();
    void yyerror(const char *s) { std::cout << "ERROR: " << s << std::endl; }
%}

/* Represents the many different ways we can access our data */
%union {
    Node *node;
    Block *block;
    Expression *expr;
    ExpressionStatement *stmt;
    std::vector<ExpressionStatement> *stmts;
    std::string *string;
    int token;
}      

%left TPLUS

//terminal symbols
 
%token <string> TINTEGER
%token <token> TPLUS 
%token <token> TSEMICOLON

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */
%type <expr> numeric expr
%type <block> program stmts block
%type <stmt> stmt
 
%start program

%%

program : block { programBlock = $1; }
        ;

block: stmts
      ;
        
stmts : stmt TSEMICOLON { $$ = new Block(); $$->statements.push_back($<stmt>1); }
      | stmts stmt TSEMICOLON { $1->statements.push_back($<stmt>2);  }
      ;

stmt : expr { $$ = new ExpressionStatement($1); }
     ;

numeric : TINTEGER { $$ = new Literal(atol($1->c_str()));  delete $1; }
        ;
    
expr : numeric
     | expr TPLUS expr { $$ = new BinaryOp($1, $2, $3); }
     ;
    

%%