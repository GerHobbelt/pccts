/*
 * Script grammar.
 *
 * Compile with ANTLR.
 *
 * ..\bin\antlr -emsvc -gd -gs -gh -e3 -cr -ga -k 2 -tab 2 -w2 -gk -rl 2000 $(InputName).g
 *
 */

/*
 * Script compiler will produce P-code (Z80-opcodes later?) which is executed
 *
 * As such the original 'direct execution' idea has been left and we're acting
 * much more like a compiler really.
 */

/********************************************************************
 *                                                                  *
 *       Common Header Definition Stuff                             *
 *                                                                  *
 ********************************************************************/

#header << 
/* ------------------------------------------------------------------------- */
/*                        (C) copyright Insh_Allah                           */
/* ------------------------------------------------------------------------- */
/* $Logfile:: /PRJ_VC/XLIBS/TSC/src/tsc_main.c                             $ */
/* $Workfile:: tsc_main.c                                                  $ */
/* $Header:: /PRJ_VC/XLIBS/TSC/src/tsc_main.c 14    29/05/98 3:14p Hobbg   $ */
/* $Date:: 29/05/98 3:14p                                                  $ */
/* $Revision:: 14                                                          $ */
/* $Modtime:: 29/05/98 2:34p                                               $ */
/* $Author:: Hobbg                                                         $ */
/*
 *  GNU IAS is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 1, or (at your option)
 *  any later version.
 *
 *  GNU IAS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU IAS; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Log: /PRJ_VC/XLIBS/TSC/src/tsc_main.c $
 */
#if !defined(_NO_VSS_STRING) 
#if defined(_WIN32) && (defined(_MSC_VER) && (_MSC_VER > 800))
#pragma comment (exestr, "$Header: /PRJ_VC/XLIBS/TSC/src/tsc_main.c 14    29/05/98 3:14p Hobbg $" )
#endif
#endif
/* $NoKeywords: $ */
/* ------------------------------------------------------------------------- */

#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "attrib.h"
#include "set.h" /* needed by antlr.h [at least] */

>>




/********************************************************************
 *                                                                  *
 *       Stuff to put in the Generated Code                         *
 *                                                                  *
 ********************************************************************/

#first <<

#if defined(__TURBOC__)
#pragma warn -aus  /* unused assignment of 'xxx' */
#endif
#ifdef _MSC_VER
/* local variable is initialized but not referenced */
#pragma warning(disable : 4189)
#endif

>>

/* regular additions for ANTLR generated C source */
<<

#if defined(USER_ZZSYN)

/*
 * as we use exceptions to handle errors, we might reduce the amount of 'unreachable code'
 * by redefining zzsyn() and zzresynch() which are only referenced by
 * the _fail: labels.
 *
 * Our embedded compiler isn't that awfully smart: unreachable code STAYS around :-((
 */

#if 0
#define zzsyn(text, tok, egroup, eset, etok, k, bad_text)              \
  /* should never get here as we use exception handling */             \
  assert(0)                                                            
#endif

#define zzresynch(s, t)                                                \
  /* should never get here as we use exception handling */             \
  assert(0)                                                            


#endif


static const char *signal2descr(int _signal)
{
  const char *s;

  switch (_signal)
  {
  case NoSignal:
    s = "NoSignal (PCCTS standard exception)";
    break;

  case MismatchedToken:
    s = "MismatchedToken (PCCTS standard exception)";
    break;

  case NoViableAlt:
    s = "NoViableAlt (PCCTS standard exception)";
    break;

  case NoSemViableAlt:
    s = "NoSemViableAlt (PCCTS standard exception)";
    break;

  case Unwind:
    s = "Unwind (PCCTS standard exception)";
    break;


  case UnsupportedStatement:
    s = "UnsupportedStatement (I_A exception extension)";
    break;

  case UnsupportedTypedef:
    s = "UnsupportedTypedef (I_A exception extension)";
    break;

  case UnsupportedInitialization:
    s = "UnsupportedInitialization (I_A exception extension)";
    break;

  
  default:
    {
      static char response[5+1+9];
    
      sprintf(response, "???(%d)", _signal);
      return response;
    }
  }
  return s;
}

>>


/********************************************************************
 *                                                                  *
 *       TOKEN definitions for the lexer and grammar                *
 *                                                                  *
 ******* DON'T PUT LITERAL TOKEN STRINGS IN THE GRAMMAR ITSELF! *****
 *                                                                  *
 ********************************************************************/

#lexclass START


/*
 * This one MUST be placed before the grammar definition itself or else
 * ANTLR barfs on the "@" being assigned a token which is _used_ in the
 * grammar!
 */
#token SCRIPT_EOF     	     ("End Of Script")             "@"
                             << printf("End Of Script Reached...\n"); >>




#token ERROR_ITS_EOF_TOKEN   ("???") /* Incorrectly terminated string constant */
                                
#token ERROR_ITC_TOKEN       ("Incorrectly terminated 'C' style comment")

#token UNARY_PLUS            ("'unary +'")
#token UNARY_MINUS           ("'unary -'")
#token INTEGER_SIZE          ("'*'")     /* MULTIPLY as in 'INTEGER MULTIPLY INT_VALUE' typedef */
#token INCREMENT             ("'++'")    /* PLUS PLUS */
#token DECREMENT             ("'--'")    /* MINUS MINUS */




/* keywords */

#token ANY                   ("'any'")                     /* "any"                      */
#token ARRAY                 ("'array'")                   /* "array"                    */
#token AS                    ("'as'")                      /* "as"                       */
#token BOOLEAN               ("'boolean'")                 /* "boolean"                  */
#token BOOLEAN_FALSE         ("'false'")                   /* "false"                    */
#token BOOLEAN_TRUE          ("'true'")                    /* "true"                     */
#token BREAK                 ("'break'")                   /* "break"                    */
#token CONST                 ("'const'")                   /* "const"                    */
#token CONTINUE              ("'continue'")                /* "continue"                 */
#token DECLARATIONS          ("'var' or 'declarations'")   /* "var|declarations"         */
#token DEFINE                ("'define'")                  /* "define"                   */
#token DEFINITIONS           ("'definitions'")             /* "definitions"              */
#token DO                    ("'do'")                      /* "do"                       */
#token DONE                  ("'done'")                    /* "done"                     */
#token ELIF                  ("'elif'")                    /* "elif"                     */
#token ELSE                  ("'else'")                    /* "else"                     */
#token ENDIF                 ("'endif'")                   /* "endif"                    */
#token ENDSCRIPT             ("'endscript'")               /* "endscript"                */
#token ENDSTRUCT             ("'endstruct'")               /* "endstruct"                */
#token ENDSUB                ("'endsub'")                  /* "endsub"                   */
#token GOTO                  ("'goto'")                    /* "goto"                     */
#token HALT                  ("'halt'")                    /* "halt"                     */
#token IF                    ("'if'")                      /* "if"                       */
#token IMPLEMENTATION        ("'code' or 'implementation'") /* "code|implementation"      */
#token INTEGER               ("'integer'")                 /* "integer"                  */
#token OF                    ("'of'")                      /* "of"                       */
#token REAL                  ("'real'")                    /* "real"                     */
#token REPEAT                ("'repeat'")                  /* "repeat"                   */
#token RESET                 ("'reset'")                   /* "reset"                    */
#token RETURN                ("'return'")                  /* "return"                   */
#token SCRIPT                ("'script'")                  /* "script"                   */
#token STRING                ("'string'")                  /* "string"                   */
#token STRUCT                ("'struct'")                  /* "struct"                   */
#token SUBROUTINE            ("'subroutine'")              /* "subroutine"               */
#token UNTIL                 ("'until'")                   /* "until"                    */
#token VOID                  ("'void'")                    /* "void"                     */
#token WHILE                 ("'while'")                   /* "while"                    */

#token BOOLEAN_AND           ("'&&' or 'and'")             "\&\&" /* "\&\&|and" */
#token BOOLEAN_OR            ("'||' or 'or'")              "\|\|" /* "\|\||or" */

#token BITWISE_AND           ("'&'")                       "\&"
#token BITWISE_OR            ("'|'")                       "\|"
#token BITWISE_XOR           ("'^'")                       "\^"

#token END                   ("'}' or 'end'")              "\}"  /* "\}|end" */
#token BEGIN                 ("'{' or 'begin'")            "\{"  /* "\{|begin" */

/*
 * these tokens clash with UNARY plus and minus as in:
 *
 *   i := +++++j;
 *
 * which should be allowed as we don't mind:
 *
 *   i := !!!!j;
 *
 * though more than TWO of these is quite ridiculous...
 *
 * --j is nonsense (== j), ++j is nonsense too, while !!j is positive logic: j --> boolean
 */
/* #token PLUSPLUS              "\+\+"                */
/* #token MINUSMINUS            "\-\-"                */

#token ASSIGN                ("':='")                      ":="
#token ASSIGN_PLUS           ("'+='")                      "\+="
#token ASSIGN_MINUS          ("'-='")                      "\-="
#token ASSIGN_MULTIPLY       ("'*='")                      "\*="
#token ASSIGN_DIVIDE         ("'/='")                      "/="
#token ASSIGN_MODULO         ("'%='")                      "%="
#token ASSIGN_POWER          ("'**='")                     "\*\*="
#token ASSIGN_LSHIFT         ("'<<='")                     "\<\<="
#token ASSIGN_RSHIFT         ("'>>='")                     "\>\>="
#token ASSIGN_BITWISE_OR     ("'|='")                      "\|="
#token ASSIGN_BITWISE_AND    ("'&='")                      "\&="
#token ASSIGN_BITWISE_XOR    ("'^='")                      "\^="
#token ASSIGN_BOOLEAN_OR     ("'||='")                     "\|\|="
#token ASSIGN_BOOLEAN_AND    ("'&&='")                     "\&\&="

#token LSHIFT                ("'<<'")                      "\<\<"
#token RSHIFT                ("'>>'")                      "\>\>"

#token GE                    ("'>='")                      "\>="
#token GT                    ("'>'")                       "\>"
#token EQ                    ("'=='")                      "=="
#token LE                    ("'<='")                      "\<="
#token LT                    ("'<'")                       "\<"
#token NE                    ("'!='")                      "\!="
#token DIVIDE                ("'/'")                       "/"
#token MODULO                ("'%'")                       "%"
#token POWER                 ("'**'")                      "\*\*"
#token BITWISE_NOT           ("'~'")                       "\~"
#token MINUS                 ("'-'")                       "\-"
#token PLUS                  ("'+'")                       "\+"
#token MULTIPLY              ("'*'")                       "\*"
#token BOOLEAN_NOT           ("'!'")                       "\!"

#token TRIPLE_DOT            ("'...'")                     "\.\.\."

#token LPARENS               ("'('")                       "\("
#token RPARENS               ("')'")                       "\)"
#token LBRACKET              ("'['")                       "\["
#token RBRACKET              ("']'")                       "\]"
#token COMMA                 ("','")                       ","
#token DOT                   ("'.'")                       "."
#token SEMICOLON             ("';'")                       ";"
#token COLON                 ("':'")                       ":"

/*---------------------- STRING_VALUES --------------------------*/
#lexclass STRING_VALUES

/*
 * C-style string handling
 */
#token STRING_VALUE          ("'\"'")                      "\""
                             << 
                                zzreplstr(""); /* throw away terminating \" */
                                /* can we use zzreplchar(0) here? end of string anyway! */
                                zzmode(START); 
                             >>

#token BOGUS1                ("???")                       "\\\\"
                             << zzreplchar('\\'); zzmore(); >>
#token BOGUS2                ("???")                       "\\\""    
                             << zzreplchar('\"'); zzmore(); >>
#token BOGUS3                ("???")                       "\\\'"  
                             << zzreplchar('\''); zzmore(); >>
#token BOGUS4                ("???")                       "\\n"
                             << zzreplchar('\n'); zzmore(); >>
#token BOGUS5                ("???")                       "\\r"
                             << zzreplchar('\r'); zzmore(); >>
#token BOGUS6                ("???")                       "\\t"
                             << zzreplchar('\t'); zzmore(); >>
#token BOGUS7                ("???")                       "\\v"
                             << zzreplchar('\v'); zzmore(); >>
#token BOGUS8                ("???")                       "\\f"
                             << zzreplchar('\f'); zzmore(); >>
#token BOGUS9                ("???")                       "\\b"
                             << zzreplchar('\b'); zzmore(); >>
#token BOGUS10               ("???")                       "\\a"
                             << zzreplchar('\a'); zzmore(); >>
#token BOGUS11               ("???")                       "\\[0-7] { [0-7] { [0-7] }}"                 
                             << 
                                /* C-strings don't support DECIMAL \\-escaped codes.
                                 * We won't either! */
                                zzreplchar((char)strtol(zzbegexpr + 1, NULL, 8));
                                zzmore(); 
                             >>
#token BOGUS12               ("???")                       "\\[Xx] [0-9a-fA-F] { [0-9a-fA-F] }"        
                             << 
                                zzreplchar((char)strtol(zzbegexpr + 2, NULL, 16));
                                zzmore(); 
                             >>
#token ERROR_INVALID_ESC_SEQ ("invalid '\\'-escaped sequence in string constant")
                                                           "\\~[\r\n0-7nrtvfbaxX\\\'\"]"               
                             << 
                                /* faulty escape sequence: report this! */

                                /* TBD */

                                zzmore(); 
                             >>
#token BOGUS14               ("???")                       "\\{\r}\n"                              
                             << 
                                zzline++; 

                                /* faulty escape sequence: report this! In fact, this is a 'string continuation' method in 'C'
                                   to make strings continue on the next line. */

                                NLA = ERROR_INVALID_ESC_SEQ;

                                /*
                                 * REMOVE continuation and newline! 
                                 * Accept MSDOS 'newlines' BTW 
                                 */ 
                             >>
#token BOGUS15               ("???")                       "~[\"\r\n\\]+"                            
                             << zzmore(); >>

#token ERROR_ITS_TOKEN       ("???")                       "{\r}\n"
                             <<
                                zzline++; zzmode(START); 
                                zzmore(); 
                                /* Print error: incorrectly terminated string */ 
                             >>

#token                       "@"
                             << 
                                NLA = ERROR_ITS_EOF_TOKEN;

                                zzmode(START); 
                                /* incorrectly terminated string */ 
                             >> 

/*---------------------- COMMENT --------------------------*/
/*
 * C-style comment handling
 */
#lexclass COMMENT

#token COMMENTBLOCK          ("'C' comment block")         "\*/"
                             << zzmode(START); zzskip(); >>
#token BOGUS17               ("???")                       "~[\*\n]"                               
                             << zzskip(); >>
#token BOGUS18               ("???")                       "\n"      
                             << zzline++; zzskip(); >>
#token BOGUS19               ("???")                       "\*"
                             << zzskip(); >>

#token                       "@"       
                             << 
                                NLA = ERROR_ITC_TOKEN;

                                zzmode(START); 
                                /* incorrectly terminated C-style comment */ 
                             >> 

/*---------------------- CPPCOMMENT --------------------------*/
/*
 * C++-style comment handling
 */
#lexclass CPPCOMMENT

#token CPPCOMMENTLINE        ("'C++' comment line")        "\n"
                             << zzline++; zzmode(START); zzskip(); >>
#token BOGUS20               ("???")                       "~[\n]"
                             << zzskip(); >>

#token                       "@"       
                             << 
                                zzskip();
                                zzmode(START); 
                                /* end of comment is end of file */ 
                             >> 


/*---------------------- START --------------------------*/
#lexclass START

/*
 * values 
 */
#token INT_VALUE             ("integer constant")          "0[0-7]*"
#token INT_VALUE                                           "[1-9][0-9]*"
#token INT_VALUE                                           "0[Xx][0-9A-Fa-f]+"                     
                             << /* Hex Value! */ >>

#token REAL_VALUE            ("floating point value")      "([1-9][0-9]* | 0 )( { \.[0-9]+ } [Ee] { [\+\-] } [0-9]+ | \.[0-9]+ )"

/* string */
#token                       "\""      
                             <<
                                zzmode(STRING_VALUES); 
#if 01
                                zzskip(); /* throw away the starting \" */
#else
                                zzreplstr(""); /* throw away terminating \" */
                                /* can we use zzreplchar(0) here? end of string anyway! */
                                zzmore();
#endif
                             >>

/*
 * variable identifiers 
 */
#token LIB_FUNCTION_ID       ("library function identifier")   /* 'converted' VARIABLE token */
#token SUBROUTINE_ID         ("subroutine identifier")         /* subroutine title in script */
#token JUMPLABEL_ID          ("jumplabel identifier")          /* label for GOTO */
#token TYPEDEF_ID            ("defined type identifier")       /* DEFINE identifier AS ... */

#token VARIABLE              ("identifier")        "[a-zA-Z\$_][a-zA-Z0-9\$_]*"
                             <<
                                /*
                                 * check if this is a reserved word: return
                                 * different token for that!
                                 */
                                {
                                  char keyword[ZZLEXBUFSIZE]; 
                                  size_t keyword_len = zzendexpr - zzlextext + 1;

                                  if (keyword_len < sizeof(keyword)
                                      && keyword_len > 1
                                      && !zzbufovf)
                                  {
                                    /* we assume no keyword is less than 2 characters in size */
                                    short int res;
                                    
                                    assert(strlen(zzbegexpr) < sizeof(keyword));
                                    strcpy(keyword, zzbegexpr);

                                    /* convert to all lowercase */
#if 0
                                    strlwr(keyword + 1);
#else
                                    {
                                      char *p = keyword + 1;

                                      while (*p)
                                      {
                                        *p++ = tolower(*p);
                                      }
                                    }
#endif
                                    keyword[0] = toupper(keyword[0]);

                                    res = get_reserved_keyword(keyword, keyword_len);
                                    if (res)
                                    {
                                      NLA = res;
                                    }
                                  }
                                }
                             >>


/*
 * Various tokens
 */
#token WHITESPACE            ("???")                       "[\t\r\ ]+"                             
                             << zzskip(); /* Ignore whitespace */>> 
#token NEWLINE               ("???")                       "\n"      
                             << zzline++; zzskip(); /* Count lines */ >>

#token BOGUS21               ("???")                       "/\*"     
                             << zzmode(COMMENT); zzskip(); >>
#token BOGUS22               ("???")                       "//"      
                             << zzmode(CPPCOMMENT); zzskip(); >>
#token BOGUS23               ("???")                       "#"       
                             << zzmode(CPPCOMMENT); zzskip(); >>

#token UNKNOWN_CHAR          ("unknown character")         "~[\-\n\t\r\ \"/#0-9a-zA-Z\$_\~\!\%\^\*\(\)\{\}\[\]=\+;:\<\>,.\&\|]"
                             << /* erroneous character! */ >>



#lexclass START





/********************************************************************
 *                                                                  *
 *       #errclass definitions for error reporting                  *
 *                                                                  *
 ********************************************************************/


#errclass "Incorrectly Terminated String Constant"   { ERROR_ITS_TOKEN ERROR_ITS_EOF_TOKEN }

/* #errclass "Incorrectly Terminated Comment"        { ERROR_ITC_TOKEN } */
/* #errclass "Undefined Character in Source"         { UNKNOWN_CHAR } */





/********************************************************************
 *                                                                  *
 *       #tokclass definitions for error reporting                  *
 *                                                                  *
 ********************************************************************/

/*
 * #tokclass'es are a luxury we don't really need here.
 *
 * Besides, this luxury grows our err.c data table space and we're planning to
 * plug this into our little Z80 based machine ('ram it in' that is... :-) )
 * so we'll do without...
 *
*/

#tokclass BOOLEAN_VALUE { BOOLEAN_TRUE BOOLEAN_FALSE }


#tokclass ASSIGNMENT { ASSIGN ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MULTIPLY ASSIGN_DIVIDE 
                       ASSIGN_MODULO ASSIGN_POWER ASSIGN_BITWISE_AND ASSIGN_BITWISE_OR
                       ASSIGN_BITWISE_XOR ASSIGN_BOOLEAN_AND ASSIGN_BOOLEAN_OR
                       ASSIGN_LSHIFT ASSIGN_RSHIFT }

#tokclass UNARY_OPERATOR { PLUS MINUS BITWISE_NOT BOOLEAN_NOT }

#tokclass BASIC_TYPES { INTEGER REAL BOOLEAN STRING }




/********************************************************************
 *                                                                  *
 *       Grammar definition                                         *
 *                                                                  *
 ********************************************************************/

/* root exception handler */
exception 
  catch MismatchedToken:
  catch NoViableAlt:
  catch NoSemViableAlt:
  catch UnsupportedStatement:
  catch UnsupportedTypedef:
    /* default:   WARNING! don't include 'default:' clause as it will ALWAYS
     *            'recover' from the signalled error: it (almost) does an 
     *            implicit zzSuppressSignal (except that the 'exported signal'
     *            is NOT reset!)
     *            Sounds to me like one big Attribute/AST leak: no calls to
     *            
     *                  zzEXIT(zztasp{nn});
     *
     *            This leakage has been fixed now by modifying the ANTLRx() macro's...
     */
                             <<
                                printf("ERROR: Global default exception handler\n"
                                       "       (token is '%s')\n"
                                       "       (signal is %s)\n"
                                       "       line: %d..%d, column: %d..%d\n"
                                      ,LATEXT(1)
                                      ,signal2descr(_signal)
                                      ,zzline
                                      ,zzreal_line
                                      ,zzendcol
                                      ,zzbegcol);

#if 0
                                zzMissTok = zzaCur.token_id; /* zzMissTok = 0??? */
                                zzFAIL(0
                                      ,&zzMissSet, &zzMissText, &zzBadTok, &zzBadText, &zzErrk);
                                zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
#endif

                                /* flush all: nobody can save you now :-) */
                                zzconsumeUntilToken(SCRIPT_EOF);
                                /* pass signal to caller */
                                zzsetSignal(Unwind); /* replaces: zzexportSignal; */
                             >>
  catch Unwind:
                             << 
                                /* we've got that one covered already! */
                                zzexportSignal;
                             >>


script: 
    SCRIPT title param_def_list 
      sections 
    ENDSCRIPT 
    SCRIPT_EOF
    ;

title:
    /* was: STRING_VALUE */
    VARIABLE
    ;
exception
  catch MismatchedToken:
  catch NoViableAlt:
  catch NoSemViableAlt:
                             <<
                                printf("ERROR: Expected a SCRIPT or SUBROUTINE TITLE\n"
                                       "       (token is '%s')\n"
                                       "       (signal is %s)\n"
                                       "       line: %d..%d, column: %d..%d\n"
                                      ,LATEXT(1)
                                      ,signal2descr(_signal)
                                      ,zzline
                                      ,zzreal_line
                                      ,zzendcol
                                      ,zzbegcol);

                                /* pass signal to caller */
                                zzsetSignal(Unwind); /* replaces: zzexportSignal; */
                             >>
  catch UnsupportedStatement:
  catch UnsupportedTypedef:
  catch Unwind:
                             << 
                                assert(!"May never happen!");
                                zzexportSignal;
                             >>



sections:
    { definitions } 
    ( subroutine )*
    { declarations } 
    implementation
    ;

definitions:
    DEFINITIONS 
    ( structdef 
    | const_init_type_def 
    )+
    ;
exception
  catch MismatchedToken:
  catch NoSemViableAlt:
                             <<
                                printf("ERROR: in DEFINITIONS section\n"
                                       "       (token is '%s')\n"
                                       "       (signal is %s)\n"
                                       "       line: %d..%d, column: %d..%d\n"
                                      ,LATEXT(1)
                                      ,signal2descr(_signal)
                                      ,zzline
                                      ,zzreal_line
                                      ,zzendcol
                                      ,zzbegcol);

                                /* pass signal to caller */
                                zzsetSignal(Unwind); /* replaces: zzexportSignal; */
                             >>
  catch NoViableAlt:
                             <<
                                printf("ERROR: in DEFINITIONS section\n"
                                       "       (token is '%s')\n"
                                       "       (signal is %s)\n"
                                       "       line: %d..%d, column: %d..%d\n"
                                       "       -- Did you at least enter ONE definition? If not, leave out\n"
                                       "          the DEFINITIONS header too! --\n"
                                      ,LATEXT(1)
                                      ,signal2descr(_signal)
                                      ,zzline
                                      ,zzreal_line
                                      ,zzendcol
                                      ,zzbegcol);

                                /* pass signal to caller */
                                zzsetSignal(Unwind); /* replaces: zzexportSignal; */
                             >>
  catch UnsupportedTypedef:
                             <<
                                printf("ERROR: Unsupported type definition found.\n"
                                       "       Currently we do not yet support statements\n"
                                       "       of type: DEFINE...AS...\n"
                                       "       (token is '%s')\n"
                                       "       (signal is %s)\n"
                                       "       line: %d..%d, column: %d..%d\n"
                                      ,LATEXT(1)
                                      ,signal2descr(_signal)
                                      ,zzline
                                      ,zzreal_line
                                      ,zzendcol
                                      ,zzbegcol);

                                /* pass signal to caller */
                                zzsetSignal(Unwind); /* replaces: zzexportSignal; */
                             >>
  catch UnsupportedInitialization:
                             <<
                                /* pass signal to caller */
                                zzexportSignal;
                             >>



structdef:
                             << zzsetSignal(UnsupportedTypedef); >>
    def:DEFINE VARIABLE
    AS 
    ( type
    | STRUCT ( 
               vardecl 
             )+ 
      ENDSTRUCT
    ) 
    SEMICOLON
                             << zzcopy_attr(&$structdef, &$def); /* test code */ >>
    ;

const_init_type_def:
    const_init_type SEMICOLON
    ;
 
subroutine:
                             << zzsetSignal(UnsupportedStatement); >>
    SUBROUTINE title param_def_list COLON return_type 
    sections
    /**** allow subsubsub....routines and subtypes, i.e. types and subroutines in local scope ****/
    ENDSUB
    ;
exception
  catch UnsupportedStatement:
                             <<
                                printf("ERROR: Unsupported statement found.\n"
                                       "       Currently we do not yet support SUBROUTINES.\n"
                                       "       (token is '%s')\n"
                                       "       (signal is %s)\n"
                                       "       line: %d..%d, column: %d..%d\n"
                                      ,LATEXT(1)
                                      ,signal2descr(_signal)
                                      ,zzline
                                      ,zzreal_line
                                      ,zzendcol
                                      ,zzbegcol);

                                zzconsumeUntilToken(ENDSUB);
                                /* pass signal to caller */
                                zzsetSignal(Unwind); /* replaces: zzexportSignal; */
                             >>



param_def_list:
    LPARENS 
    { 
      ( param_def ( COMMA param_def )* { COMMA TRIPLE_DOT }
      | TRIPLE_DOT ) 
    } 
    RPARENS
    ;

param_def:
    VARIABLE { COLON sub_param_type }
    ;

declarations:
    DECLARATIONS 
    ( vardecl )+
    ;

vardecl:
    VARIABLE COLON ( type | const_init_type ) SEMICOLON
    ;
  
sub_param_type:
    { CONST } 
    ( type
    | ANY )
    ;

return_type:
    type
  | VOID
  | ANY
    ;

type:
    BOOLEAN
  | integer_type
  | REAL
  | STRING
  | ARRAY OF type
  | VARIABLE
    ;

integer_type:
    INTEGER { MULTIPLY INT_VALUE } 
    ;

const_init_type:
    CONST integer_type ASSIGN INT_VALUE 
  | CONST REAL ASSIGN REAL_VALUE 
  | CONST BOOLEAN ASSIGN BOOLEAN_VALUE
  | CONST STRING ASSIGN const_string_value
  | CONST VARIABLE ASSIGN INT_VALUE 
    ;
exception
  catch UnsupportedStatement:
  catch UnsupportedTypedef:
                             <<
                                assert(!"May never get here!");
                             >>
  catch Unwind:
                             << 
                                /* pass signal to caller */
                                zzexportSignal;
                             >>
  catch MismatchedToken:
  catch NoViableAlt:
  catch NoSemViableAlt:
  default:
                             << 
                                /* any erroneous initialization: no support for pre-initialized complex types! */
                                zzsetSignal(UnsupportedInitialization); 
   
                                printf("ERROR: Erroneous initialization: language only supports\n"
                                       "       CONSTants initialization of basic types:\n"
                                       "         INTEGER, REAL, BOOLEAN, STRING\n"
                                       "       (token is '%s')\n"
                                       "       (signal is %s)\n"
                                       "       line: %d..%d, column: %d..%d\n"
                                      ,LATEXT(1)
                                      ,signal2descr(_signal)
                                      ,zzline
                                      ,zzreal_line
                                      ,zzendcol
                                      ,zzbegcol);

                                /* pass signal to caller */
                                zzsetSignal(Unwind); /* replaces: zzexportSignal; */
                             >>



  
const_string_value:
                             <<
                                $const_string_value.token_id = 5000;
                                $const_string_value.token_descr = "const_string_value";
                                $const_string_value.string_value = "";
                                $const_string_value.dupped_string_value = strdup("");
                             >>
    (
      str:STRING_VALUE
                             <<
                                $const_string_value.token_id++;
                                $const_string_value.string_value = $str.string_value;
                                {
                                  int len = strlen($const_string_value.dupped_string_value)
                                            + strlen($str.dupped_string_value) 
                                            + 1;

                                  $const_string_value.dupped_string_value = realloc($const_string_value.dupped_string_value, len);
                                  if ($const_string_value.dupped_string_value == NULL)
                                  {
                                    /* failure --> exception! */
                                    zzsetSignal(UnsupportedInitialization); /* fake and incorrect! */
                                    /* goto _handler; ???????????????? */
                                  }
                                  else
                                  {
                                    strcat($const_string_value.dupped_string_value, $str.dupped_string_value);
                                  }
                                }
                             >>
    )+        /* C-style string concatenation: "hello " "world" */
    ;

implementation:
    IMPLEMENTATION
                             << TRACE(("start of implementation")); >>
    ( statement )+
    ;

statement:
    assignment_statement
  | conditional_statement
  | loop_statement
  | block_statement
  | return_statement
  | break_statement
  | label_statement
  | special_statement
    ;
exception
  catch UnsupportedStatement:
                             <<
                                printf("ERROR: Unsupported statement found.\n"
                                       "       Currently we do not yet support statements\n"
                                       "       of type: RETURN, BREAK, CONTINUE, GOTO or <label>:\n"
                                       "       (token is '%s')\n"
                                       "       (signal is %s)\n"
                                       "       line: %d..%d, column: %d..%d\n"
                                      ,LATEXT(1)
                                      ,signal2descr(_signal)
                                      ,zzline
                                      ,zzreal_line
                                      ,zzendcol
                                      ,zzbegcol);

                                zzconsumeUntilToken(SEMICOLON);
                                /* pass signal to caller */
                                zzsetSignal(Unwind); /* replaces: zzexportSignal; */
                             >>



return_statement:
                             << zzsetSignal(UnsupportedStatement); >>
    RETURN SEMICOLON         
    ;

label_statement:
                             << zzsetSignal(UnsupportedStatement); >>
    VARIABLE COLON                    /* label definition */
  | GOTO VARIABLE SEMICOLON           /* jump to label: do we support forward jumps? */
    ;

break_statement:
                             << zzsetSignal(UnsupportedStatement); >>
    /* must be located within loop or conditional statement somewhere... */
    BREAK SEMICOLON
  | CONTINUE SEMICOLON
    ;

special_statement:
    RESET SEMICOLON          /* do not return control EVER */
                             << TRACE(("RESET() opcode")); >>
  | HALT SEMICOLON           /* wait for interrupt? or wait indefinitely... */
                             << TRACE(("HALT() opcode")); >>
    ;

assignment_statement:       
    lvalue_expr
                             << TRACE(("assignment: calculate reference to lvalue")); >>
    ( op:ASSIGNMENT
                             <<  
                                TRACE(("assignment op: %d [%s] text: \"%s\", dupped: \"%s\"\n"
                                      , $op.token_id
                                      , $op.token_descr
                                      , $op.string_value
                                      , $op.dupped_string_value
                                      )); 
                             >>
      rvalue_expr 
                             << TRACE(("assignment: store(accu) in lvalue location")); >>
    | PLUS PLUS
                             << TRACE(("assignment: '++' => increment lvalue")); >>
    | MINUS MINUS 
                             << TRACE(("assignment: '--' => decrement lvalue")); >>
    )
    SEMICOLON
                             << TRACE(("end of assignment")); >>
  | VOID rvalue_expr 
    SEMICOLON
                             << TRACE(("assignment: void => discard (accu)")); >>
    ;

conditional_statement:
    IF
                             << TRACE(("start of if() mark")); >>
    bracketed_conditional_expr 
                             << TRACE(("if(): if (accu != 0: execute block")); >>
      block_statement
    (
      ELIF 
                             << TRACE(("start of elif() mark")); >>
      bracketed_conditional_expr 
                             << TRACE(("elif(): if (accu != 0: execute block")); >>
        block_statement 
    )*
    { 
      ELSE 
                             << TRACE(("start of else() mark")); >>
        block_statement 
    }
    ENDIF 
    SEMICOLON
                             << TRACE(("end of if() mark")); >>
    ;

loop_statement:
    WHILE
                             << TRACE(("start loop mark")); >>
    bracketed_conditional_expr 
                             << TRACE(("start loop: if (accu != 0: continue executing loop")); >>
    DO
      block_statement
    DONE 
    SEMICOLON
                             << TRACE(("end loop mark")); >>
  | REPEAT
                             << TRACE(("start loop mark")); >>
      block_statement
    UNTIL bracketed_conditional_expr 
                             << TRACE(("end loop: if (accu == 0: continue executing loop")); >>
    SEMICOLON
                             << TRACE(("end loop mark")); >>
    ;

bracketed_conditional_expr:
    LPARENS rvalue_expr RPARENS
    ;

block_statement:
    BEGIN ( statement )+ END
    ;

lvalue_expr:
    elemental_variable
                             << TRACE(("lvalue determined")); >>
    ;

elemental_variable:
    /* simple or array element; maybe even element of array of structs */
    basevar:VARIABLE 
    ( LBRACKET 
      rvalue_expr 
      RBRACKET 
    )* 
    ( DOT VARIABLE 
      ( LBRACKET 
        rvalue_expr 
        RBRACKET 
      )* 
    )*
                             <<
                                TRACE(("load(element); var='%s'; "
                                       "no array or struct element decoding yet"
                                      ,$basevar.dupped_string_value)); 
                             >>
    ;

rvalue_expr:
    compare_or_rvalue_expr
    ;

compare_or_rvalue_expr:
    compare_and_rvalue_expr ( BOOLEAN_OR 
                             << TRACE(("push(accu): left hand operand")); >>
                              compare_and_rvalue_expr 
                             << TRACE(("BOOLEAN_OR(accu, pop()) -> accu")); >>
                            )*
    ;

compare_and_rvalue_expr:
    bitwise_or_rvalue_expr ( BOOLEAN_AND 
                             << TRACE(("push(accu): left hand operand")); >>
                             bitwise_or_rvalue_expr 
                             << TRACE(("BOOLEAN_AND(accu, pop()) -> accu")); >>
                           )*
    ;

bitwise_or_rvalue_expr:
    bitwise_xor_rvalue_expr ( BITWISE_OR 
                             << TRACE(("push(accu): left hand operand")); >>
                              bitwise_xor_rvalue_expr 
                             << TRACE(("BITWISE_OR(accu, pop()) -> accu")); >>
                            )*
    ;

bitwise_xor_rvalue_expr:
    bitwise_and_rvalue_expr ( BITWISE_XOR 
                             << TRACE(("push(accu): left hand operand")); >>
                              bitwise_and_rvalue_expr 
                             << TRACE(("BITWISE_XOR(accu, pop()) -> accu")); >>
                            )*
    ;

bitwise_and_rvalue_expr:
    compare_ne_rvalue_expr ( BITWISE_AND 
                             << TRACE(("push(accu): left hand operand")); >>
                             compare_ne_rvalue_expr 
                             << TRACE(("BITWISE_AND(accu, pop()) -> accu")); >>
                           )*
    ;

compare_ne_rvalue_expr:
    compare_eq_rvalue_expr ( NE 
                             << TRACE(("push(accu): left hand operand")); >>
                             compare_eq_rvalue_expr 
                             << TRACE(("NE?(accu, pop()) -> accu")); >>
                           )*
    ;

compare_eq_rvalue_expr:
    compare_ge_rvalue_expr ( EQ 
                             << TRACE(("push(accu): left hand operand")); >>
                             compare_ge_rvalue_expr 
                             << TRACE(("EQ?(accu, pop()) -> accu")); >>
                           )*
    ;

compare_ge_rvalue_expr:
    compare_gt_rvalue_expr ( GE 
                             << TRACE(("push(accu): left hand operand")); >>
                             compare_gt_rvalue_expr 
                             << TRACE(("GE?(accu, pop()) -> accu")); >>
                           )*
    ;

compare_gt_rvalue_expr:
    compare_le_rvalue_expr ( GT 
                             << TRACE(("push(accu): left hand operand")); >>
                             compare_le_rvalue_expr 
                             << TRACE(("GT?(accu, pop()) -> accu")); >>
                           )*
    ;

compare_le_rvalue_expr:
    compare_lt_rvalue_expr ( LE 
                             << TRACE(("push(accu): left hand operand")); >>
                             compare_lt_rvalue_expr 
                             << TRACE(("LE?(accu, pop()) -> accu")); >>
                           )*
    ;

compare_lt_rvalue_expr:
    rshift_rvalue_expr ( LT 
                             << TRACE(("push(accu): left hand operand")); >>
                         rshift_rvalue_expr 
                             << TRACE(("LT?(accu, pop()) -> accu")); >>
                       )*
    ;

rshift_rvalue_expr:
    lshift_rvalue_expr ( RSHIFT 
                             << TRACE(("push(accu): left hand operand")); >>
                         lshift_rvalue_expr 
                             << TRACE(("RSHIFT(accu, pop()) -> accu")); >>
                       )*
    ;

lshift_rvalue_expr:
    substract_rvalue_expr ( LSHIFT 
                             << TRACE(("push(accu): left hand operand")); >>
                            substract_rvalue_expr 
                             << TRACE(("LSHIFT(accu, pop()) -> accu")); >>
                          )*
    ;

substract_rvalue_expr:
    add_rvalue_expr ( MINUS 
                             << TRACE(("push(accu): left hand operand")); >>
                      add_rvalue_expr 
                             << TRACE(("MINUS(accu, pop()) -> accu")); >>
                    )*
    ;

add_rvalue_expr:
    modulo_rvalue_expr ( PLUS 
                             << TRACE(("push(accu): left hand operand")); >>
                         modulo_rvalue_expr 
                             << TRACE(("PLUS(accu, pop()) -> accu")); >>
                       )*
    ;

modulo_rvalue_expr:
    divide_rvalue_expr ( MODULO 
                             << TRACE(("push(accu): left hand operand")); >>
                         divide_rvalue_expr 
                             << TRACE(("MODULO(accu, pop()) -> accu")); >>
                       )*
    ;
    
divide_rvalue_expr:
    multiply_rvalue_expr ( DIVIDE 
                             << TRACE(("push(accu): left hand operand")); >>
                           multiply_rvalue_expr 
                             << TRACE(("DIVIDE(accu, pop()) -> accu")); >>
                         )*
    ;
    
multiply_rvalue_expr:
    power_rvalue_expr ( MULTIPLY 
                             << TRACE(("push(accu): left hand operand")); >>
                        power_rvalue_expr 
                             << TRACE(("MULTIPLY(accu, pop()) -> accu")); >>
                      )*
    ;

power_rvalue_expr:
    unary_rvalue_expr ( POWER 
                             << TRACE(("push(accu): left hand operand")); >>
                        unary_rvalue_expr 
                             << TRACE(("POWER(accu, pop()) -> accu")); >>
                      )*
    ;

    /* do NOT allow 'i := ++j;' or else say (PLUS)* instead of {PLUS}.
     * (PLUS)* however may clash with PLUSPLUS so we'd better say then:
     * (PLUS | PLUSPLUS)*
     */
    /* do NOT allow 'i := --j;' or else say (MINUS)* instead of {MINUS}  
     * (MINUS)* however may clash with MINUSMINUS so we'd better say then:
     * (MINUS | MINUSMINUS)*
     */
    /* do NOT allow 'i := ~~j;' or else say (BITWISE_NOT)* instead of {BITWISE_NOT}   */
    /* OLD: do NOT allow 'i := !!j;' or else say (BOOLEAN_NOT)* instead of {BOOLEAN_NOT}   */
    /* we *DO* allow 'i := !!j;' but ONLY the 'twice !' variant... */
/*
unary_rvalue_expr:     
    ( op:UNARY_OPERATOR
                             << TRACE(("has: UNARY_OPERATOR: %s", $op.token_descr)); >>
    )* simple_rvalue_expr 
    ;
*/
/* [2/sep/98 i_a: why did we comment this one out and used the recursive definition instead?!] */

unary_rvalue_expr:     
    simple_rvalue_expr 
  | op:UNARY_OPERATOR
                             << TRACE(("has: UNARY_OPERATOR: %s", $op.token_descr)); >>
    unary_rvalue_expr
    ;

simple_rvalue_expr:
    @INT_VALUE             
                             << TRACE(("load(INT_VALUE)")); >>
  | @REAL_VALUE            
                             << TRACE(("load(REAL_VALUE)")); >>
  | @b:BOOLEAN_VALUE       
                             << TRACE(("load(BOOL_VALUE): %s", $b.token_descr)); >>
  | @s:const_string_value  
                             << TRACE(("load(STRING_VALUE): %s", $s.dupped_string_value)); >>
  | @elemental_variable    
                             << TRACE(("load(elemental_variable): must be in accu already!")); >>
  | @f:VARIABLE            
                             << TRACE(("prepare call to function %s", $f.dupped_string_value)); >>
    LPARENS { @param_list } RPARENS      /* function call */
                             << TRACE(("call function %s", $f.dupped_string_value)); >>
  | @LPARENS         
                             << TRACE(("'(' before expression")); >>
      rvalue_expr
    RPARENS
                             << TRACE(("')' after expression; accu already loaded")); >>
    ;   

param_list:     
                             << int cnt = 0; >>
    rvalue_expr   
                             << TRACE(("push(accu) -- as argument %d", ++cnt)); >>
    ( COMMA rvalue_expr
                             << TRACE(("push(accu) -- as argument %d", ++cnt)); >>
    )*
    ;






/*------------------------------------------------------------*/




