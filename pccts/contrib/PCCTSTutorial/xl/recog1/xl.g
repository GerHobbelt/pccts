#header
<<
// any definitions that you need in the generated files
>>


<<
// scanner definitions would go here
#include "DLexerBase.h"
#include "DLGLexer.h"
#include "AToken.h"
typedef ANTLRCommonToken ANTLRToken;

int main(int argc, char **argv)
{
    DLGFileInput in(stdin);
    DLGLexer scanner(&in);
    ANTLRTokenBuffer pipe(&scanner);
    ANTLRToken tok;
	scanner.setToken(&tok);
    XLParser xlParser(&pipe);

    xlParser.init(); // initialize
    xlParser.program(); // start first rule
    return 0;
}
>>


// scanner rules

#lexclass START // Not really necessary, but
                // good commentary nonetheless

// White Space
#token "[\ \t\r]"       <<skip();>>
#token "\n"           <<skip(); newline();>>

// Comments
#token "// ~[\n@]* [\n@]" <<skip(); newline();>>

// Literals
#token INTLIT  "[0-9]+"
#token CHARLIT "\' ~[] \'"
#token         "\"" << // start STRINGLIT
                        skip();
                        mode(STRING);
                    >>

// Keywords
#token PROGRAM   "program"
#token BEGIN     "begin"
#token END       "end"
#token VAR       "var"
#token CONSTANT  "constant"
#token TYPE      "type"
#token RECORD    "record"
#token ARRAY     "array"
#token OF        "of"
#token PROCEDURE "procedure"
#token PUT       "put"
#token GET       "get"
#token SKIPLINE  "skipLine"
#token NEWLINE   "newLine"
#token EXIT      "exit"
#token WHEN      "when"
#token RETURN    "return"
#token IF        "if"
#token THEN      "then"
#token ELSE      "else"
#token ELSIF     "elsif"
#token WHILE     "while"
#token LOOP      "loop"
#token AND       "and"
#token OR        "or"
#token INTEGER  "Integer"
#token BOOLEAN "Boolean" 

// Operators
#token DOT        "."
#token BECOMES    ":="
#token COLON      ":"
#token SEMI       ";"
#token COMMA      ","
#token EQUALS     "="
#token LBRACKET   "\["
#token RBRACKET   "\]"
#token DOTDOT     ".."
#token LPAREN     "\("
#token RPAREN     "\)"
#token NOT_EQUALS "/="
#token LT         "<"
#token LTE        "<="
#token GT         ">"
#token GTE        ">="
#token PLUS       "\+"
#token MINUS      "\-"
#token TIMES      "\*"
#token DIV        "/"
#token MOD        "mod"
#token NOT        "not"

// Identifiers
#token IDENT "[a-zA-Z] [a-zA-Z0-9]*"

// String Literal Processing
// Separate Scanner class!
#lexclass STRING
#token           "\"\"" <<
                            more();
                            replchar('\"');
                        >>
#token BADSTRING "\n"   <<
                            replchar('\0');
                            newline();
                            mode(START);
                            /* error message */
                        >>
#token STRINGLIT "\""   <<
                            replchar('\0');
                            mode(START);
                        >>
#token           "~[]"  <<more();>>

#tokclass STRING_LITERAL {STRINGLIT BADSTRING}
#tokclass ADD_OP {PLUS MINUS}
#tokclass RELATIONAL_OP {EQUALS NOT_EQUALS GT GTE LT LTE}
#tokclass BOOLEAN_OP {AND OR}
#tokclass MULT_OP {TIMES DIV MOD}

class XLParser
{
<<
    // parser definitions go here

    public:
        void init()
        {
            ANTLRParser::init();
            // any specific initialization you need
            // (if none, don't override the init() method
        }
>>



program
  : PROGRAM IDENT EQUALS 
        subprogramBody 
    DOT
    "@" // end-of-file
  ;


subprogramBody
  : (basicDecl)*
    (procedureDecl)*
    BEGIN
        (statement)*
    END IDENT
  ;


basicDecl
  : varDecl
  | constDecl
  | typeDecl
  ;


varDecl
  : VAR identList COLON typeName
    {BECOMES constantValue}
    SEMI
  ;


constDecl
  : CONST identList COLON typeName
    BECOMES constantValue SEMI
  ;



identList
  : IDENT (COMMA IDENT)*
  ;


constantValue
  : INTLIT
  | STRING_LITERAL
  | IDENT
  ;


typeDecl
  : TYPE IDENT EQUALS
    ( arrayDecl
    | recordDecl
    )
    SEMI
  ;


arrayDecl
  : ARRAY LBRACKET integerConstant DOTDOT integerConstant RBRACKET
    OF typeName
  ;

integerConstant
  : INTLIT
  | IDENT // again, a constant...
  ;


recordDecl
  : RECORD (identList COLON typeName SEMI)+ END RECORD
  ;


typeName
  : IDENT
  | INTEGER
  | BOOLEAN
  ;


procedureDecl
  : PROCEDURE IDENT {formalParameters} EQUALS
        subprogramBody
    SEMI
  ;


formalParameters
  : LPAREN parameterSpec (SEMI parameterSpec)* RPAREN
  ;


parameterSpec
  : {VAR} identList COLON typeName
  ;

statement
  : exitStatement
  | returnStatement
  | ifStatement
  | loopStatement
  | ioStatement
  | procedureCallStatement
  | assignmentStatement
  | endStatement
  ;

assignmentStatement
  : variableReference BECOMES expression SEMI
  ;


exitStatement
  : EXIT WHEN expression
  ;

procedureCallStatement
  : IDENT {actualParameters} SEMI
  ;

actualParameters
  : LPAREN { expression (COMMA expression)* } RPAREN
  ;


returnStatement
  : RETURN SEMI
  ;


ifStatement
  : IF ifPart END IF SEMI
  ;

ifPart
  : expression THEN
    (statement)*
    { ELSIF ifPart
    | ELSE (statement)*
    }
  ;

loopStatement
  : {WHILE expression} LOOP
        (statement)*
    END LOOP SEMI
  ;

endStatement
  : END SEMI
  ;

variableReference
  : IDENT
    ( LBRACKET expression RBRACKET
    | DOT IDENT
    )*
  ;



ioStatement
  : PUT LPAREN expression RPAREN SEMI
  | GET LPAREN variableReference RPAREN SEMI
  | NEWLINE {LPAREN RPAREN} SEMI
  | SKIPLINE {LPAREN RPAREN} SEMI
  ;


primitiveElement
  : constantValue
  | variableReference
  | LPAREN expression RPAREN
  ;


booleanNegationExpression
  : (NOT)* primitiveElement
  ;

signExpression
  : (ADD_OP)* booleanNegationExpression
  ;


multiplyingExpression
  : signExpression (MULT_OP signExpression)*
  ;

addingExpression
  : multiplyingExpression (ADD_OP multiplyingExpression)*
  ;

relationalExpression
  : addingExpression (RELATIONAL_OP addingExpression)*
  ;

expression
  : relationalExpression (BOOLEAN_OP relationalExpression)*
  ;

}