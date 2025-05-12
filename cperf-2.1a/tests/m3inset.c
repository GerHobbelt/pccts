/* C code produced by gperf version 2.1 (ANSI C version) */
/*
 * Command-line: ../src/gperf -k1,2,$ -o modula3.gperf 
 */



#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 247
/*
 *   106 keywords
 *   244 is the maximum key range
 */

static int
hash (str, len)
  register char *str;
  register unsigned int  len;
{
  static unsigned char hash_table[] =
  {
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247,  25,  95,  25,  50,   0,
      85, 247,   0,  25, 247,  30,  10,  95,   5,  45,
      25, 247,   0, 120,  40,  50,  95,  30,  55,  30,
     247, 247, 247, 247, 247, 247, 247,   5,  10,  35,
      25,   0,   5, 247,  60,  20, 247,   5,   0,  10,
       0, 110,  15, 247,   0,  80,  15,  70,  82,  20,
      75,  45, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
     247, 247, 247, 247, 247, 247,
  };
  return len + hash_table[str[1]] + hash_table[str[0]] + hash_table[str[len - 1]];
}

char *
in_word_set (str, len)
  register char *str;
  register unsigned int len;
{

  static char * wordlist[] =
  {
    "", "", "", "", 
    "else", 
    "", 
    "return", 
    "", 
    "ref", 
    "", 
    "elsif", 
    "RETURN", 
    "", "", 
    "ELSE", 
    "begin", 
    "", "", "", 
    "from", 
    "", 
    "repeat", 
    "in", 
    "", 
    "procedure", 
    "", 
    "inline", 
    "", 
    "end", 
    "interface", 
    "", 
    "record", 
    "if", 
    "and", 
    "PROCEDURE", 
    "WHILE", 
    "INLINE", 
    "IN", 
    "READONLY", 
    "INTERFACE", 
    "", "", "", "", 
    "case", 
    "", 
    "REPEAT", 
    "OR", 
    "", 
    "THEN", 
    "", 
    "import", 
    "", 
    "readonly", 
    "CASE", 
    "array", 
    "RECORD", 
    "", 
    "END", 
    "WITH", 
    "ARRAY", 
    "UNSAFE", 
    "", 
    "try", 
    "type", 
    "", "", "", 
    "typecase", 
    "EXCEPTION", 
    "UNTIL", 
    "", "", 
    "TRY", 
    "TYPE", 
    "until", 
    "unsafe", 
    "finally", 
    "TYPECASE", 
    "then", 
    "", "", "", 
    "AND", 
    "exception", 
    "while", 
    "eval", 
    "", 
    "REF", 
    "LOCK", 
    "var", 
    "raises", 
    "value", 
    "NOT", 
    "exit", 
    "", 
    "except", 
    "methods", 
    "set", 
    "EXIT", 
    "ELSIF", 
    "EXCEPT", 
    "by", 
    "untraced", 
    "with", 
    "BEGIN", 
    "", "", "", 
    "EVAL", 
    "", "", 
    "or", 
    "UNTRACED", 
    "bits", 
    "CONST", 
    "", "", 
    "for", 
    "lock", 
    "", "", 
    "of", 
    "VAR", 
    "", 
    "VALUE", 
    "module", 
    "", 
    "not", 
    "", 
    "div", 
    "", 
    "TO", 
    "FOR", 
    "", "", "", "", "", "", "", 
    "object", 
    "DO", 
    "", "", "", 
    "MODULE", 
    "FINALLY", 
    "mod", 
    "", "", 
    "RAISES", 
    "", "", "", "", "", 
    "BY", 
    "", "", "", "", 
    "exports", 
    "SET", 
    "", 
    "const", 
    "IMPORT", 
    "", "", "", "", "", "", 
    "DIV", 
    "", "", "", "", "", "", "", "", 
    "EXPORTS", 
    "", 
    "FROM", 
    "", 
    "OBJECT", 
    "", "", "", "", "", "", 
    "MOD", 
    "", "", "", 
    "IF", 
    "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "", "", 
    "", "OF", 
    "", "", "", "", 
    "METHODS", 
    "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", 
    "to", 
    "", "", "", "", "", "", 
    "BITS", 
    "", "", 
    "do", 
  };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
  {
    register int key = hash (str, len);

    if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
    {
      register char *s = wordlist[key];

      if (*s == *str && !strcmp (str + 1, s + 1))
        return s;
    }
  }
  return 0;
}
