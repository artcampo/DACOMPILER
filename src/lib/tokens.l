%{
#include <string>
#include "AST/Node.hpp"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }
%}

%%

[ tn]                   ;
[0-9]+                  SAVE_TOKEN; return TINTEGER;
"+"                     return TOKEN(TPLUS);
"-"                     return TOKEN(TMINUS);
"*"                     return TOKEN(TMUL);
"/"                     return TOKEN(TDIV);
"("                     return TOKEN(TLPAREN);
")"                     return TOKEN(TRPAREN);
";"                     return TOKEN(TSEMICOLON);
.                       printf("Unknown token!n"); yyterminate();

%%
