#include "Givens.h"
//prototypes for all functions with Parser.c
_Bool parser(struct lexics *someLexics, int numberOfLexics);
_Bool function(struct lexics *someLexics, int numLex);
_Bool body(struct lexics *someLexics, int numLex);
_Bool statementList(struct lexics *someLexics, int numLex);
_Bool statement(struct lexics *someLexics, int numLex);
_Bool whileLoop(struct lexics *someLexics, int numLex);
_Bool returnStmt(struct lexics *someLexics, int numLex);
_Bool assignment(struct lexics *someLexics, int numLex);
_Bool expression(struct lexics *someLexics, int numLex);
_Bool header(struct lexics *someLexics, int numLex);
_Bool argDecl(struct lexics *someLexics, int numLex);
_Bool term(struct lexics *someLexics, int numLex);
enum token nextToken(struct lexics *someLexics, int numLex);

