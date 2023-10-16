#include "Tokenizer.h"
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
    //buffer to store the input file
    char buffer[256];
    //variable to store the substring that will be the next lexeme
    char previousLexeme[LEXEME_MAX];
    //temp array to store various buffers
    char temp[LEXEME_MAX];
    //index variable to populate buffer and control the main for-loop
    int index1 = 0;
    //count variable for various for-loops throughout tokenizer method
    int count = 0;
    //character to store each new character from *inf
    int c = 0;
    //index of next lexics struct to be stored in *aLex
    int sindex = 0;
    //loop to put all characters in the infile into the buffer
    while(1)
    {
        c = fgetc(inf);
        //loops ends when the end of file character is read
        if( feof(inf) ) {break;}
        buffer[index1] = c;
        index1++;
    }
    //add a null terminator to the char buffer array to prevent the program from exceding desired bounds
    buffer[index1] = '\0';
    //main for-loop to iterate through each char in the buffer
    for(int d = 0; d < index1; d++){
        //switch statement controled by the character specified at index d in buffer
        switch(buffer[d]){
            case '(':
            //first checks if the characters preceding the left parenthesis make a valid identifier 
            //or number. If such a case exists, it makes a lexics struct using the given methods
            //and resets the value of previousLexeme. It then increments the index for the next lexics
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //adds the delimiting left parenthesis
                aLex[sindex].token = LEFT_PARENTHESIS;
                strcpy(aLex[sindex].lexeme, "(");
                sindex++;
                break;
            case ')':
            //kinda repetitive, but checks if there is a valid lexeme preceding the right parenthesis
            //and assigns it the correct token to make it an actual lexics, then resets previousLexeme
            //and increments sindex
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //adds the delimiting right parenthesis
                aLex[sindex].token = RIGHT_PARENTHESIS;
                strcpy(aLex[sindex].lexeme, ")");
                sindex++;
                break;
            case '{':
            //does the same checks as the previous 2 cases, just with the left bracket and then does
            //the same operations as the last 2 cases.
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //adds the delimiting left bracket. 
                //I'm seeing a pattern here... oh wait I wrote the code lol. 
                aLex[sindex].token = LEFT_BRACKET;
                strcpy(aLex[sindex].lexeme, "{");
                sindex++;
                break;
            case '}':
            //You know the drill by now, but as a refresher, if the last few characters make up a valid 
            //identifier or number, the appropriate token is assigned while adding the completed struct to the array.
            //The array holding said characters is then cleared for further use.
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //adds the delimiting right bracket
                aLex[sindex].token = RIGHT_BRACKET;
                strcpy(aLex[sindex].lexeme, "}");
                sindex++;
                break;
            case '*':
            //Something different this time? Nah.
            //checks for validity and if it is, does the same operations as the last 4 cases.
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //adds the delimiting asterisk
                aLex[sindex].token = BINOP;
                strcpy(aLex[sindex].lexeme, "*");
                sindex++;
                break;
            case '+':
            //checks the previousLexeme to see if it is an actual identifier or number and makes a lexics struct accordingly
            //It would be a lot easier to copy paste as I type this at 3am.
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //adds the delimiting plus sign
                aLex[sindex].token = BINOP;
                strcpy(aLex[sindex].lexeme, "+");
                sindex++;
                break;
            case ',':
            //That's a good idea
            //first checks if the characters preceding the left parenthesis make a valid identifier 
            //or number. If such a case exists, it makes a lexics struct using the given methods
            //and resets the value of previousLexeme. It then increments the index for the next lexics
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //adds the delimiting comma
                aLex[sindex].token = COMMA;
                strcpy(aLex[sindex].lexeme, ",");
                sindex++;
                break;
            case ';':
            //first checks if the characters preceding the left parenthesis make a valid identifier 
            //or number. If such a case exists, it makes a lexics struct using the given methods
            //and resets the value of previousLexeme. It then increments the index for the next lexics
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //adds the delimiting semicolon
                aLex[sindex].token = EOL;
                strcpy(aLex[sindex].lexeme, ";");
                sindex++;
                break;
            case 'w':
    //Can't really copy and paste anything here :(
                //uses a temporary buffer to check if the next 4 characters complete the "while"
                for(count = 0; count < 4; count++){
                    temp[count] = buffer[count+d+1];
                }
                //compares the buffer to the rest of the word "while" (since the w was used in the switch case)
                if(strcmp(temp, "hile") == 0){
                    aLex[sindex].token = WHILE_KEYWORD;
                    strcpy(aLex[sindex].lexeme, "while");
                    memset(temp, 0, LEXEME_MAX);
                    //if it does make while, we skip ahead in the buffer 4 spaces (since we just iterated over them)
                    d+=4;
                    sindex++;
                } 
                //if it doesn't make while, we just add a w to previousLexeme and continue incrementing d by 1 (using the for-loop)
                else {
                    strcat(previousLexeme, "w");
                }
                break;
            case 'r':
            //kinda similar to the while, but this time with return
                //iterates a few chars ahead to fill the buffer
                for(count = 0; count < 5; count++){
                    temp[count] = buffer[count+d+1];
                }
                //compares the buffer to the rest of the word return and makes a new entry in the lexics array
                if(strcmp(temp, "eturn") == 0){
                    aLex[sindex].token = RETURN_KEYWORD;
                    strcpy(aLex[sindex].lexeme, "return");
                    memset(temp, 0, LEXEME_MAX);
                    //we can skip 5 spaces this time
                    d+=5;
                    sindex++;
                } else{
                    //we cannot skip if there isn't a return, but we can add an r to the previousLexeme
                    strcat(previousLexeme, "r");
                }
                break;
            case '=':
    //But here I can :)
            //first checks if the characters preceding the left parenthesis make a valid identifier 
            //or number. If such a case exists, it makes a lexics struct using the given methods
            //and resets the value of previousLexeme. It then increments the index for the next lexics
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //makes a new temporary buffer
                char eBuffer[2];
                //puts the next char in the buffer after the = to check if it is a second =
                eBuffer[0] = buffer[d+1];
                //if the next character is =, we can make a binop lexeme (and skip a space with d++)
                if(strcmp(eBuffer, "=") == 0){
                    aLex[sindex].token = BINOP;
                    strcpy(aLex[sindex].lexeme, "==");
                    sindex++;
                    d++;
                }
                //if the next character in the buffer is not another =, we simply make a lexics struct with the EQUAL token instead of BINOP
                else {
                    aLex[sindex].token = EQUAL;
                    strcpy(aLex[sindex].lexeme, "=");
                    sindex++;
                }
                break;
            case '!':
            //similar to the last one, a buffer is made to check the next char in the main buffer
                
                
                temp[0] = buffer[d+1];
                if(strcmp(temp, "=") == 0){
                    //the difference here is that if an = is next, it now becomes a delimiter as well as a BINOP token, 
                    //so now we check for the usual: is previousLexeme an identifier or a number?
                    if(validNumber(previousLexeme)){
                        aLex[sindex].token = NUMBER;
                        strcpy(aLex[sindex].lexeme, previousLexeme);
                        memset(previousLexeme, 0, LEXEME_MAX);
                        sindex++;
                    } 
                    else if(validIdentifier(previousLexeme)){
                        aLex[sindex].token = IDENTIFIER;
                        strcpy(aLex[sindex].lexeme, previousLexeme);
                        memset(previousLexeme, 0, LEXEME_MAX);
                        sindex++;
                    }
                    aLex[sindex].token = BINOP;
                    strcpy(aLex[sindex].lexeme, "!=");
                    memset(temp, 0, LEXEME_MAX);
                    d++;
                    sindex++;
                }
                //if it happens to not be a delimiter, then we just add ! to the previousLexeme
                else {
                    strcat(previousLexeme, "!");
                }
                break;
            case '%':
            //wow another single character delimeter :/
            //does the same checks and operations as the first few cases, but here I am dumb and don't know how to 
            //escape the % symbol. So I did what any great programmer does and I manually made a string and appended the \0 to the % to make
            //it a string
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                //add the delimiting %
                char modBuffer[2];
                modBuffer[0] = '%';
                modBuffer[1] = '\0';
                aLex[sindex].token = BINOP;
                strcpy(aLex[sindex].lexeme, modBuffer);
                sindex++;
                break;
            case 'i':
            //now we get to the vartypes
            //In the same way that I compared the next few characters to the completed word for the "return" and "while" cases,
            //it is the same here.
             

            
                //look ahead a few slots
                for(count = 0; count < 2; count++){
                    temp[count] = buffer[count+d+1];
                }
                //compare the buffer to the rest of the desired word. If it is int, congrats we have a new lexics entry
                    if(strcmp(temp, "nt") == 0){
                        aLex[sindex].token = VARTYPE;
                        strcpy(aLex[sindex].lexeme, "int");
                        memset(temp, 0, LEXEME_MAX);
                        //we can skip here too (or 2 depending on how you read that)
                        d+=2;
                        sindex++;
                    } 
                    //if it isn't, then at least previousLexeme is one i richer
                    else{
                        strcat(previousLexeme, "i");
                    }
                break;
            case 'v':
                //make an array

                
                //look ahead to see what chars are there
                for(count = 0; count < 3; count++){
                    temp[count] = buffer[count+d+1];
                }
                //if they are the chars we are looking for, we make a new lexics with the VARTYPE token
                if(strcmp(temp, "oid") == 0){
                    aLex[sindex].token = VARTYPE;
                    strcpy(aLex[sindex].lexeme, "void");
                    memset(temp, 0, LEXEME_MAX);
                    sindex++;
                    //we also get to skip ahead so we don't have to look at those boring "oid"s
                    d+=3;
                } 
                //if it isn't void then we put the v on the growing string of chars
                else{
                    strcat(previousLexeme, "v");
                }
                break;
            case ' ':
            //if a space is hit, we can check if the previous lexeme is an identifier or a number, but we don't want the space 
            //character in our lexics structure so we don't even mess with it >:(
                if(validNumber(previousLexeme)){
                    aLex[sindex].token = NUMBER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                } 
                else if(validIdentifier(previousLexeme)){
                    aLex[sindex].token = IDENTIFIER;
                    strcpy(aLex[sindex].lexeme, previousLexeme);
                    memset(previousLexeme, 0, LEXEME_MAX);
                    sindex++;
                }
                break;
            case '\n':
            //same as space but we hate newline even more >>:(
                break;
            case '\t':
            //don't even get me started on tab D:<<<
                break;
            default:
            //the default case just makes each character that isn't a delimeter a part of the previousLexeme. To do this I just made the 
            //char into a string

                
                temp[0] = buffer[d];
                temp[1] = '\0';
                strcat(previousLexeme, temp);
                memset(temp, 0, LEXEME_MAX);
                break;

        }
    }
    
    *numLex = sindex;
    return TRUE;
}