#include "Parser.h"
//variable to keep track of where in the lexics array the tokens are coming from
int globalIndex = -1;
//helper function to retrieve the next single token for parsing direction
enum token nextToken(struct lexics *someLexics, int numLex){
    //no segfaults here
    if(globalIndex < numLex){
        globalIndex++;
        enum token tok = someLexics[globalIndex].token;
        return tok;
    }
    //I didn't know what to return here so -1 it is
    else return -1;
}
//function to determine if a token is either a number or an identifier
_Bool term(struct lexics *someLexics, int numLex){
    //get next token and compare
    enum token tok = nextToken(someLexics, numLex);
    if(tok == IDENTIFIER || tok == NUMBER){
        return TRUE;
    } else return FALSE;
}
//function to determine if the arg declaration is valid in a lexics
_Bool argDecl(struct lexics *someLexics, int numLex){
    //continue until it returns
    while(1){
        //if the current symbol is vartype, we continue parsing
        if(nextToken(someLexics, numLex) == VARTYPE){
            //if the current symbol is identifier, we can pass by it and check if the 
            //next token is a comma.
            if(nextToken(someLexics, numLex) == IDENTIFIER){
                enum token tok = nextToken(someLexics, numLex);
                //when there are no commas, and we already passed valid vartype/identifier 
                //pairs, we can return true. Since we don't know what tok is (just that
                //it isn't a comma), we decrement the counter so we don't skip anything
                if(tok != COMMA){
                    globalIndex--;
                    return TRUE;
                }
            } else return FALSE;
        } else return FALSE;
    }
}
//function to determine if the structure of the expression is valid
_Bool expression(struct lexics *someLexics, int numLex){
    _Bool t;
    enum token tok;
    //checks the next single token for if it is the start a parenthesis couple
    if(nextToken(someLexics, numLex) == LEFT_PARENTHESIS){
        //if it might be, we use a recursive loop to repeatedly check for nested 
        //parentheses
        _Bool e = expression(someLexics, numLex);
        //we finish the first loop by checking for where the right parenthses come in
        if( e == TRUE && nextToken(someLexics, numLex) == RIGHT_PARENTHESIS){
            return  TRUE;
        } 
        else{
            globalIndex--;
            return FALSE;
        } 
    }
    //if it isn't part of the first segment, the || operator in the EBNF
    //dictates that there is still a way that the parse is valid 
    else {
        globalIndex--;
        //continues until a return
        while(1){
            //checks if the token is a valid term
             if( term(someLexics, numLex) == TRUE){
                 //passes to next token and checks if it is a BINOP
                 //if it is, it continues back to the top of the while loop
                 if(nextToken(someLexics, numLex) != BINOP){
                    return TRUE;
                 }
             }
             else return FALSE;
        }
    }
        
}
//function to determine if a string of tokens is a valid assignment statement
_Bool assignment(struct lexics *someLexics, int numLex){
    //checks the next token to see if it is an identifier
    if(nextToken(someLexics, numLex) == IDENTIFIER){
        //if it is, the program passes that token to check the next one for an =
        if(nextToken(someLexics, numLex) == EQUAL){
            //if the token is =, the expression function is called to check if there is a
            //valid expression within the assignment block
            _Bool expr = expression(someLexics, numLex);
            globalIndex--;
            //if there is a valid expression, and the next token is ;, a value of true is returned
            if(expr == TRUE && nextToken(someLexics, numLex) == EOL){
                return TRUE;
            } else{
                return FALSE;
            } 
        } else return FALSE;
    } else return FALSE;
}
//a function to determine if a block of code is a valid return statement
_Bool returnStmt(struct lexics *someLexics, int numLex){
    //checks if the first token is the word "return"
    if(nextToken(someLexics, numLex) == RETURN_KEYWORD){
        //then we check to see if there is a valid expression after the return statement
        _Bool expr = expression(someLexics, numLex);
        if(expr == TRUE){
            globalIndex--;
        }
        //if there is a ; after the valid expression, then it is a valid return statement
        if(expr == TRUE && nextToken(someLexics, numLex) == EOL){
            return TRUE;
        }else return FALSE;
    } else return FALSE;
}
//a function to check if a block of code is a valid while-loop
_Bool whileLoop(struct lexics *someLexics, int numLex){
    _Bool expr;
    _Bool stmt;
    //checks first token, and if it is the word "while", moves to the next token
    if(nextToken(someLexics, numLex) == WHILE_KEYWORD){
        //if the next token is (, checks if there is an expression within the someLexics array
        if(nextToken(someLexics, numLex) == LEFT_PARENTHESIS){
            expr = expression(someLexics, numLex);
            //if an expression is found, the function then checks for a )
            if(expr == TRUE && nextToken(someLexics, numLex) == RIGHT_PARENTHESIS){
                //if the ) is found, the program checks for a statement, and if it 
                // is found, the method returns TRUE
                stmt = statement(someLexics, numLex);
                if(stmt == TRUE){
                    return TRUE;
                } else return FALSE;
            } else return FALSE;
        } else return FALSE;
    }else return FALSE;
}
//a function for determining if there is a valid statement in the given lexics array
_Bool statement(struct lexics *someLexics, int numLex){
    //stores the first token to be used as the switch control
    //since we don't know which case it will take, the globalIndex is decremented in 3 of the cases
    enum token t = nextToken(someLexics, numLex);
    _Bool s = TRUE;
    //depending on the first token within the given structs, there are 4 possible cases
    switch(t){
        //a 2 (or a '[' ), indicates the possible start of a body segment, 
        //hence a function for body is called
        case 2: 
            s = body(someLexics, numLex);
            return s;
            break;
        //a 4, AKA a "while" token, results in a while function being called to check
        // if the given array contains a while statement
        case 4:
            globalIndex--;
            s = whileLoop(someLexics, numLex);
            return s;
            break;
        // a 5, meaning a return keyword, is used here to denote a possible return 
        //statement. This is verified by the calling of the returnStmt function
        case 5:
            globalIndex--;
            s = returnStmt(someLexics, numLex);
            return s;
            break;
        //a 10 could potentially mark the location of an assign statement. This can 
        //easily be checked by calling the assignment method.
        case 10:
            globalIndex--;
            s = assignment(someLexics, numLex);
            return s;
            break;
        //in the event that none of these cases apply, parsing stops here
        default: 
            return FALSE;
}
}
//a function to validate the presence of a statement list using tokens of the lexics array
_Bool statementList(struct lexics *someLexics, int numLex){
    //the function first calls statement to establish the minimum 1 statement
    _Bool stmt = statement(someLexics, numLex);
    //after the first statement is located, the subsequent tokens are used to make 
    //repeated calls to statement. The function halts when a return statement is reached
    while(1){
        //The statement list is only ever located before a } character 
        if(nextToken(someLexics, numLex) == RIGHT_BRACKET && stmt == TRUE){
            //globalIndex is decremented to preserve the }
            globalIndex--;
            return TRUE;
        }
        else if(stmt == FALSE){
            return FALSE;
        }
        //statement is called again and the while loop continues
        else {
             globalIndex--;
            stmt = statement(someLexics, numLex);}
    }
    
    
}
//a method to determine if there is a body segment as defined by an EBNF grammar within
//the given array
_Bool body(struct lexics *someLexics, int numLex){
    //the first token in a body must be a left bracket, but the presence of said {
        // is located within another section of code. As such, determining the presence 
        //of a } immediately succeeding the { is enough to return true
    if(nextToken(someLexics, numLex) == RIGHT_BRACKET){
        return TRUE;
    } else {
        //globalIndex is decremented to allow for future use of the non-right-bracket char
        globalIndex--;
        //statement list is called here because the statement list is optional
        // and that case is covered by the first check in this function
        _Bool stmtL = statementList(someLexics, numLex);
        //if a } is found and a valid statement list precedes it, then a value of TRUE 
        //is returned
        if(nextToken(someLexics, numLex) == RIGHT_BRACKET && stmtL == TRUE){
            return TRUE;
        } else return FALSE;
    }
}
//a function to determine is a valid header is within the tokens of the lexics array
_Bool header(struct lexics *someLexics, int numLex){
    //the first token within a header is the vartype, but the presence of such a token 
    //is determined within the "function" method. 
    if(nextToken(someLexics, numLex) == IDENTIFIER){
        //Once an identifier is found, the program iterates to the next token, checking 
        //if it is a (, the header function iterates once more
        if(nextToken(someLexics, numLex) == LEFT_PARENTHESIS){
            //once the next token is retrived, if it is a ), this means that the optional
            // arg declaration was not present, so the function returns TRUE
            if(nextToken(someLexics, numLex) == RIGHT_PARENTHESIS){
                return TRUE;
            }else {
                //if the optional segment is present, the index is decremented to save the 
                // char that is now known to not be a )
                globalIndex--;
                //the argDecl method is called to determine if the extra pieces present
                //constitute a valid argument string
                _Bool arg = argDecl(someLexics, numLex);
                //Once any arguments are captured, the truth value can now be calculated 
                // by checking once more for a ) character
                if(nextToken(someLexics, numLex) == RIGHT_PARENTHESIS && arg == TRUE){
                    return TRUE;
                }else return FALSE;
            } 
        } else return FALSE;
    } else return FALSE;
}
//a function to determine if there is a function present in the input file as presented 
//through tokens
_Bool function(struct lexics *someLexics, int numLex){
    //if the first token from the array is a VARTYPE, we call the header function 
    //to determine right away if the function is valid
    if(nextToken(someLexics, numLex) == VARTYPE){
        _Bool head = header(someLexics, numLex);
        //if a left bracket is located immediately following the header function (and if 
        //there is a valid header segment), the body function is called.
        //If there is a body segment of code present, the bod function returns TRUE
        if(nextToken(someLexics, numLex) == LEFT_BRACKET && head == TRUE){
            _Bool bod = body(someLexics, numLex);
            if(bod == TRUE){
                return TRUE;
            } else return FALSE;
        } else return FALSE;
        //If the bod function returned TRUE, then the function method also returns TRUE
        
    } else return FALSE;
}
//main driver method to start the parsing sequence
_Bool parser(struct lexics *someLexics, int numberOfLexics){
    _Bool fun = function(someLexics, numberOfLexics);
    return fun;
}

