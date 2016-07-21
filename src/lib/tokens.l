%{
#include <string>
#include "Node.hpp"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }
%}

%%

[ tn]                   ;
[0-9]+                  SAVE_TOKEN; return TINTEGER;
"+"                     return TOKEN(TPLUS);
";"                     return TOKEN(TSEMICOLON);
.                       printf("Unknown token!n"); yyterminate();

%%