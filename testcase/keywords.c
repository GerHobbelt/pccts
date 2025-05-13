
/***************************************************************************


dumping the hash table
  total elements = 256,
  bytes = 1024
  location[250] has charset "Or" and keyword "Or"
  location[246] has charset "Bginn" and keyword "Begin"
  location[231] has charset "Eees" and keyword "Else"
  location[230] has charset "Aaryy" and keyword "Array"
  location[228] has charset "Raept" and keyword "Repeat"
  location[227] has charset "Do" and keyword "Do"
  location[209] has charset "Ecdist" and keyword "Endscript"
  location[204] has charset "Weeil" and keyword "While"
  location[199] has charset "Defin" and keyword "Define"
  location[196] has charset "Iegrrt" and keyword "Integer"
  location[171] has charset "Edd" and keyword "End"
  location[167] has charset "As" and keyword "As"
  location[166] has charset "Deen" and keyword "Done"
  location[164] has charset "Uillt" and keyword "Until"
  location[159] has charset "Scrtu" and keyword "Struct"
  location[151] has charset "Feels" and keyword "False"
  location[149] has charset "Vddi" and keyword "Void"
  location[147] has charset "Sbeort" and keyword "Subroutine"
  location[135] has charset "Restt" and keyword "Reset"
  location[132] has charset "Siprt" and keyword "Script"
  location[126] has charset "If" and keyword "If"
  location[117] has charset "Ayy" and keyword "Any"
  location[106] has charset "Vrr" and keyword "Var"
  location[104] has charset "Rnrtu" and keyword "Return"
  location[102] has charset "Edffi" and keyword "Endif"
  location[100] has charset "Dfinst" and keyword "Definitions"
  location[97] has charset "Ebdsu" and keyword "Endsub"
  location[95] has charset "Baekk" and keyword "Break"
  location[94] has charset "Of" and keyword "Of"
  location[84] has charset "Add" and keyword "And"
  location[82] has charset "Daacls" and keyword "Declarations"
  location[80] has charset "Ieelnp" and keyword "Implementation"
  location[75] has charset "Ntt" and keyword "Not"
  location[69] has charset "Hltt" and keyword "Halt"
  location[60] has charset "Rall" and keyword "Real"
  location[53] has charset "Effi" and keyword "Elif"
  location[51] has charset "Belnno" and keyword "Boolean"
  location[49] has charset "Cdee" and keyword "Code"
  location[42] has charset "Sginr" and keyword "String"
  location[36] has charset "Cnstt" and keyword "Const"
  location[20] has charset "Goot" and keyword "Goto"
  location[10] has charset "Edsttu" and keyword "Endstruct"
  location[6] has charset "Teeu" and keyword "True"
  location[1] has charset "Ceintu" and keyword "Continue"

  total collisions during hashing = 17
end dumping hash table


 ***************************************************************************/

/* C code produced by gperf version 2.1 (ANSI C version) */
/*
 * Command-line: ..\cperf-2.1a\gperf -VpotTD -e@ -j1 -k1,3,4,5,7,$ -aCdgH decode_keyword -N in_reserved_keyword_set i_a_script.gperf keywords.c 
 */


/***************************************************************************

number of keys = 44
maximum associated value is 64
maximum possible size of generated hash table is 398

 ***************************************************************************/


 /* starting time is 20:50:57 */


/***************************************************************************

bool array size = 398,
total bytes = 1592
collision on keyword #3, prior="Reset", curr="Const", hash=5
- resolved by changing asso_value['C'] (char #1) to 1
collision on keyword #4, prior="Continue", curr="Endstruct", hash=9
- resolved by changing asso_value['C'] (char #1) to 2
collision on keyword #9, prior="Const", curr="Integer", hash=7
- resolved by changing asso_value['C'] (char #1) to 7
collision on keyword #11, prior="Code", curr="Definitions", hash=11
- resolved by changing asso_value['C'] (char #1) to 8
collision on keyword #12, prior="Else", curr="Done", hash=4
- resolved by changing asso_value['D'] (char #1) to 4
collision on keyword #14, prior="Reset", curr="Endif", hash=5
- resolved by changing asso_value['R'] (char #1) to 12
collision on keyword #15, prior="Else", curr="Elif", hash=4
- resolved by changing asso_value['f'] (char #1) to 9
collision on keyword #20, prior="Script", curr="String", hash=6
- resolved by changing asso_value['g'] (char #1) to 14
collision on keyword #21, prior="Script", curr="Endsub", hash=6
- resolved by changing asso_value['b'] (char #1) to 19
collision on keyword #22, prior="Script", curr="Do", hash=6
- resolved by changing asso_value['p'] (char #1) to 1
collision on keyword #23, prior="While", curr="False", hash=5
- resolved by changing asso_value['F'] (char #1) to 5
collision on keyword #24, prior="Script", curr="Boolean", hash=7
- resolved by changing asso_value['B'] (char #1) to 7
collision on keyword #26, prior="Endstruct", curr="Endscript", hash=9
- resolved by changing asso_value['c'] (char #1) to 18
collision on keyword #27, prior="Definitions", curr="Struct", hash=24
- resolved by changing asso_value['c'] (char #1) to 21
collision on keyword #28, prior="Define", curr="Repeat", hash=19
- resolved by changing asso_value['p'] (char #1) to 22
collision on keyword #30, prior="Continue", curr="Real", hash=16
- resolved by changing asso_value['C'] (char #1) to 27
collision on keyword #31, prior="While", curr="Until", hash=5
- resolved by changing asso_value['U'] (char #1) to 2
collision on keyword #32, prior="Else", curr="Halt", hash=4
- resolved by changing asso_value['H'] (char #1) to 8
collision on keyword #33, prior="Else", curr="True", hash=4
- resolved by changing asso_value['T'] (char #1) to 9
collision on keyword #34, prior="End", curr="Not", hash=3
- resolved by changing asso_value['N'] (char #1) to 12
collision on keyword #35, prior="Else", curr="Void", hash=4
- resolved by changing asso_value['V'] (char #1) to 29
collision on keyword #36, prior="Const", curr="Var", hash=32
- resolved by changing asso_value['V'] (char #1) to 30
collision on keyword #37, prior="Halt", curr="Break", hash=12
- resolved by changing asso_value['H'] (char #1) to 34
collision on keyword #38, prior="Else", curr="Goto", hash=4
- resolved by changing asso_value['G'] (char #1) to 35
collision on keyword #39, prior="While", curr="Array", hash=5
- resolved by changing asso_value['W'] (char #1) to 36
collision on keyword #40, prior="End", curr="And", hash=3
- resolved by changing asso_value['A'] (char #1) to 39
collision on keyword #41, prior="While", curr="As", hash=41
- resolved by changing asso_value['W'] (char #1) to 38
collision on keyword #42, prior="And", curr="Any", hash=42
- resolved by changing asso_value['y'] (char #1) to 1
collision on keyword #44, prior="If", curr="Of", hash=11
- resolved by changing asso_value['O'] (char #1) to 43

dumping boolean array information
iteration number = 385
end of array dump

 ***************************************************************************/


/*
-VpotTD -e@ -j1 -k1,3,4,5,7,$ -aCdgH decode_keyword -N in_reserved_keyword_set .\scripting\i_a_script.gperf .\scripting\keywords.c
*/
/* Command-line: gperf -VpotT -lj1 -k1,3,$ -aCdgH decode_keyword -N in_reserved_keyword_set i_a_script.gperf .\keywords.c  */

#include "stdpccts.h"

struct reserved_word { char *name; short int token_id; };

/* prototype */
#ifdef __GNUC__
  inline
#endif
const struct reserved_word *
in_reserved_keyword_set (register const char *str, register int len);


/* return 0 if no valid keyword was matched. */
short int get_reserved_keyword(const char *str, register int len)
{
  const struct reserved_word *p = NULL;
                                                                             
  if (!*str) return 0;
  p = in_reserved_keyword_set(str, len);   
  
  return (short int)(p ? p->token_id : 0);
}



#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 14
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 54
/*
 *    44 keywords
 *    52 is the maximum key range
 */

#ifdef __GNUC__
  inline
#endif
static int
decode_keyword (register const char *str, register int len)
{
  static const unsigned char hash_table[] =
  {
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x00 [ ] .. 0x09 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x0A [ ] .. 0x13 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x14 [ ] .. 0x1D [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x1E [ ] .. 0x27 ['] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x28 [(] .. 0x31 [1] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x32 [2] .. 0x3B [;] */
     54, 54, 54, 54, 54, 39,  7, 27,  4,  0, /* 0x3C [<] .. 0x45 [E] */
      5, 35, 34,  0, 54, 54, 54, 54, 12, 43, /* 0x46 [F] .. 0x4F [O] */
     54, 54, 12,  0,  9,  2, 30, 38, 54, 54, /* 0x50 [P] .. 0x59 [Y] */
     54, 54, 54, 54, 54, 54, 54,  0, 19, 21, /* 0x5A [Z] .. 0x63 [c] */
      0,  0,  9, 14, 54,  0, 54,  0,  0, 54, /* 0x64 [d] .. 0x6D [m] */
      0,  0, 22, 54,  0,  0,  0,  0, 54, 54, /* 0x6E [n] .. 0x77 [w] */
     54,  1, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x78 [x] .. 0x81 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x82 [ ] .. 0x8B [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x8C [ ] .. 0x95 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0x96 [ ] .. 0x9F [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xA0 [ ] .. 0xA9 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xAA [ ] .. 0xB3 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xB4 [ ] .. 0xBD [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xBE [ ] .. 0xC7 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xC8 [ ] .. 0xD1 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xD2 [ ] .. 0xDB [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xDC [ ] .. 0xE5 [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xE6 [ ] .. 0xEF [ ] */
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54, /* 0xF0 [ ] .. 0xF9 [ ] */
     54, 54, 54, 54, 54, 54,                 /* 0xFA [ ] .. 0xFF [ ] */
  };
  register int hval = len;

  switch (hval)
  {
  default:
  case 7:
    hval += hash_table[str[6]];
  case 6:
  case 5:
    hval += hash_table[str[4]];
  case 4:
    hval += hash_table[str[3]];
  case 3:
    hval += hash_table[str[2]];
  case 2:
  case 1:
    hval += hash_table[str[0]];
  }
  return hval + hash_table[str[len - 1]];
}

#ifdef __GNUC__
  inline
#endif
const struct reserved_word *
in_reserved_keyword_set (register const char *str, register int len)
{

  static const struct reserved_word  wordlist[] =
  {
    {"End",  END},
    {"Else",  ELSE},
    {"Do",  DO},
    {"Until",  UNTIL},
    {"Done",  DONE},
    {"Endstruct",  ENDSTRUCT},
    {"False",  BOOLEAN_FALSE},
    {"If",  IF},
    {"Break",  BREAK},
    {"True",  BOOLEAN_TRUE},
    {"Boolean",  BOOLEAN},
    {"Not",  BOOLEAN_NOT},
    {"Real",  REAL},
    {"Reset",  RESET},
    {"Return",  RETURN},
    {"Define",  DEFINE},
    {"String",  STRING},
    {"Integer",  INTEGER},
    {"Elif",  ELIF},
    {"Endif",  ENDIF},
    {"Definitions",  DEFINITIONS},
    {"Endsub",  ENDSUB},
    {"Begin",  BEGIN},
    {"Struct",  STRUCT},
    {"Script",  SCRIPT},
    {"Subroutine",  SUBROUTINE},
    {"Endscript",  ENDSCRIPT},
    {"Code",  IMPLEMENTATION},
    {"Const",  CONST},
    {"Var",  DECLARATIONS},
    {"Void",  VOID},
    {"Continue",  CONTINUE},
    {"Implementation",  IMPLEMENTATION},
    {"Declarations",  DECLARATIONS},
    {"Halt",  HALT},
    {"Goto",  GOTO},
    {"Repeat",  REPEAT},
    {"As",  AS},
    {"And",  BOOLEAN_AND},
    {"While",  WHILE},
    {"Any",  ANY},
    {"Or",  BOOLEAN_OR},
    {"Array",  ARRAY},
    {"Of",  OF},
  };

  if (len <= MAX_WORD_LENGTH
      && len >= MIN_WORD_LENGTH)
  {
    register int key = decode_keyword (str, len);

    if (key <= MAX_HASH_VALUE
        && key >= MIN_HASH_VALUE)
    {
      if (key <= 54)
      {
        const struct reserved_word  *resword;
        

        switch (key - 3)
        {
        case   0: /* hash value =    3, keyword = "End" */
          resword = &wordlist[0];
          break;
        case   1: /* hash value =    4, keyword = "Else" */
          resword = &wordlist[1];
          break;
        case   3: /* hash value =    6, keyword = "Do" */
          resword = &wordlist[2];
          break;
        case   4: /* hash value =    7, keyword = "Until" */
          resword = &wordlist[3];
          break;
        case   5: /* hash value =    8, keyword = "Done" */
          resword = &wordlist[4];
          break;
        case   6: /* hash value =    9, keyword = "Endstruct" */
          resword = &wordlist[5];
          break;
        case   7: /* hash value =   10, keyword = "False" */
          resword = &wordlist[6];
          break;
        case   8: /* hash value =   11, keyword = "If" */
          resword = &wordlist[7];
          break;
        case   9: /* hash value =   12, keyword = "Break" */
          resword = &wordlist[8];
          break;
        case  10: /* hash value =   13, keyword = "True" */
          resword = &wordlist[9];
          break;
        case  11: /* hash value =   14, keyword = "Boolean" */
          resword = &wordlist[10];
          break;
        case  12: /* hash value =   15, keyword = "Not" */
          resword = &wordlist[11];
          break;
        case  13: /* hash value =   16, keyword = "Real" */
          resword = &wordlist[12];
          break;
        case  14: /* hash value =   17, keyword = "Reset" */
          resword = &wordlist[13];
          break;
        case  15: /* hash value =   18, keyword = "Return" */
          resword = &wordlist[14];
          break;
        case  16: /* hash value =   19, keyword = "Define" */
          resword = &wordlist[15];
          break;
        case  17: /* hash value =   20, keyword = "String" */
          resword = &wordlist[16];
          break;
        case  18: /* hash value =   21, keyword = "Integer" */
          resword = &wordlist[17];
          break;
        case  19: /* hash value =   22, keyword = "Elif" */
          resword = &wordlist[18];
          break;
        case  20: /* hash value =   23, keyword = "Endif" */
          resword = &wordlist[19];
          break;
        case  21: /* hash value =   24, keyword = "Definitions" */
          resword = &wordlist[20];
          break;
        case  22: /* hash value =   25, keyword = "Endsub" */
          resword = &wordlist[21];
          break;
        case  23: /* hash value =   26, keyword = "Begin" */
          resword = &wordlist[22];
          break;
        case  24: /* hash value =   27, keyword = "Struct" */
          resword = &wordlist[23];
          break;
        case  25: /* hash value =   28, keyword = "Script" */
          resword = &wordlist[24];
          break;
        case  26: /* hash value =   29, keyword = "Subroutine" */
          resword = &wordlist[25];
          break;
        case  27: /* hash value =   30, keyword = "Endscript" */
          resword = &wordlist[26];
          break;
        case  28: /* hash value =   31, keyword = "Code" */
          resword = &wordlist[27];
          break;
        case  29: /* hash value =   32, keyword = "Const" */
          resword = &wordlist[28];
          break;
        case  30: /* hash value =   33, keyword = "Var" */
          resword = &wordlist[29];
          break;
        case  31: /* hash value =   34, keyword = "Void" */
          resword = &wordlist[30];
          break;
        case  32: /* hash value =   35, keyword = "Continue" */
          resword = &wordlist[31];
          break;
        case  33: /* hash value =   36, keyword = "Implementation" */
          resword = &wordlist[32];
          break;
        case  34: /* hash value =   37, keyword = "Declarations" */
          resword = &wordlist[33];
          break;
        case  35: /* hash value =   38, keyword = "Halt" */
          resword = &wordlist[34];
          break;
        case  36: /* hash value =   39, keyword = "Goto" */
          resword = &wordlist[35];
          break;
        case  37: /* hash value =   40, keyword = "Repeat" */
          resword = &wordlist[36];
          break;
        case  38: /* hash value =   41, keyword = "As" */
          resword = &wordlist[37];
          break;
        case  39: /* hash value =   42, keyword = "And" */
          resword = &wordlist[38];
          break;
        case  40: /* hash value =   43, keyword = "While" */
          resword = &wordlist[39];
          break;
        case  41: /* hash value =   44, keyword = "Any" */
          resword = &wordlist[40];
          break;
        case  42: /* hash value =   45, keyword = "Or" */
          resword = &wordlist[41];
          break;
        case  43: /* hash value =   46, keyword = "Array" */
          resword = &wordlist[42];
          break;
        case  51: /* hash value =   54, keyword = "Of" */
          resword = &wordlist[43];
          break;
        default:
          return 0;
        }
        if (*str == *resword->name && !strcmp (str + 1, resword->name + 1))
          return resword;
        return 0;
      }
    }
  }
  return 0;
}

/***************************************************************************

dumping Options:
DEBUG is....................: enabled
ORDER is....................: enabled
ANSI is.....................: enabled
TYPE is.....................: enabled
GNU is......................: enabled
RANDOM is...................: disabled
DEFAULTCHARS is.............: disabled
SWITCH is...................: enabled
POINTER is..................: enabled
NOLENGTH is.................: disabled
LENTABLE is.................: disabled
DUP is......................: enabled
COMP is.....................: disabled
FAST is.....................: disabled
NOTYPE is...................: enabled
GLOBAL is...................: disabled
CONST is....................: enabled
VERBOSE_C_STATISTICS is ....: enabled
iterations = 0
lookup function name = in_reserved_keyword_set
hash function name = decode_keyword
key name = name
jump value = 1
max associcated value = 63
initial associated value = 0
delimiters = @
number of switch statements = 1
approximate switch statement size = 44
maximum charset size = 6
key positions are: 
7
5
4
3
1
$
finished dumping Options

Dumping key list information:
  total unique keywords = 44
  total keywords = 44
  maximum key length = 14.

List contents are:
  (hash value, key length,  index, key set, key):
            3,          3,      0,     Edd, End
            4,          4,      1,    Eees, Else
            6,          2,      2,      Do, Do
            7,          5,      3,   Uillt, Until
            8,          4,      4,    Deen, Done
            9,          9,      5,  Edsttu, Endstruct
           10,          5,      6,   Feels, False
           11,          2,      7,      If, If
           12,          5,      8,   Baekk, Break
           13,          4,      9,    Teeu, True
           14,          7,     10,  Belnno, Boolean
           15,          3,     11,     Ntt, Not
           16,          4,     12,    Rall, Real
           17,          5,     13,   Restt, Reset
           18,          6,     14,   Rnrtu, Return
           19,          6,     15,   Defin, Define
           20,          6,     16,   Sginr, String
           21,          7,     17,  Iegrrt, Integer
           22,          4,     18,    Effi, Elif
           23,          5,     19,   Edffi, Endif
           24,         11,     20,  Dfinst, Definitions
           25,          6,     21,   Ebdsu, Endsub
           26,          5,     22,   Bginn, Begin
           27,          6,     23,   Scrtu, Struct
           28,          6,     24,   Siprt, Script
           29,         10,     25,  Sbeort, Subroutine
           30,          9,     26,  Ecdist, Endscript
           31,          4,     27,    Cdee, Code
           32,          5,     28,   Cnstt, Const
           33,          3,     29,     Vrr, Var
           34,          4,     30,    Vddi, Void
           35,          8,     31,  Ceintu, Continue
           36,         14,     32,  Ieelnp, Implementation
           37,         12,     33,  Daacls, Declarations
           38,          4,     34,    Hltt, Halt
           39,          4,     35,    Goot, Goto
           40,          6,     36,   Raept, Repeat
           41,          2,     37,      As, As
           42,          3,     38,     Add, And
           43,          5,     39,   Weeil, While
           44,          3,     40,     Ayy, Any
           45,          2,     41,      Or, Or
           46,          5,     42,   Aaryy, Array
           54,          2,     43,      Of, Of
End dumping list.


dumping occurrence and associated values tables
  asso_values[A] =  39, occurrences[A] =   4
  asso_values[B] =   7, occurrences[B] =   3
  asso_values[C] =  27, occurrences[C] =   3
  asso_values[D] =   4, occurrences[D] =   5
  asso_values[E] =   0, occurrences[E] =   7
  asso_values[F] =   5, occurrences[F] =   1
  asso_values[G] =  35, occurrences[G] =   1
  asso_values[H] =  34, occurrences[H] =   1
  asso_values[I] =   0, occurrences[I] =   3
  asso_values[N] =  12, occurrences[N] =   1
  asso_values[O] =  43, occurrences[O] =   2
  asso_values[R] =  12, occurrences[R] =   4
  asso_values[S] =   0, occurrences[S] =   4
  asso_values[T] =   9, occurrences[T] =   1
  asso_values[U] =   2, occurrences[U] =   1
  asso_values[V] =  30, occurrences[V] =   2
  asso_values[W] =  38, occurrences[W] =   1
  asso_values[a] =   0, occurrences[a] =   6
  asso_values[b] =  19, occurrences[b] =   2
  asso_values[c] =  21, occurrences[c] =   3
  asso_values[d] =   0, occurrences[d] =  11
  asso_values[e] =   0, occurrences[e] =  22
  asso_values[f] =   9, occurrences[f] =   8
  asso_values[g] =  14, occurrences[g] =   3
  asso_values[i] =   0, occurrences[i] =  12
  asso_values[k] =   0, occurrences[k] =   2
  asso_values[l] =   0, occurrences[l] =  10
  asso_values[n] =   0, occurrences[n] =  12
  asso_values[o] =   0, occurrences[o] =   5
  asso_values[p] =  22, occurrences[p] =   3
  asso_values[r] =   0, occurrences[r] =  11
  asso_values[s] =   0, occurrences[s] =  10
  asso_values[t] =   0, occurrences[t] =  21
  asso_values[u] =   0, occurrences[u] =   6
  asso_values[y] =   1, occurrences[y] =   4
end table dumping

 ***************************************************************************/


  /* ending time is 20:50:57 */

