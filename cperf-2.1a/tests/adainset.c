/* C code produced by gperf version 2.1 (ANSI C version) */
/*
 * Command-line: ../src/gperf -k1,4,$ ada.gperf 
 */



#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 187
/*
 *    63 keywords
 *   185 is the maximum key range
 */

static int
hash (str, len)
  register char *str;
  register unsigned int  len;
{
  static unsigned char hash_table[] =
  {
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187,  30,  25,  25,
      32,   0,  15,  25,   0,  61, 187,  15,  60,  10,
      63,  60,   0, 187,   0,   5,  20,   0,   5,  10,
       5,  15, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
     187, 187, 187, 187, 187, 187,
  };
  register int hval = len;

  switch (hval)
  {
  default:
  case 4:
    hval += hash_table[str[3]];
  case 3:
  case 2:
  case 1:
    hval += hash_table[str[0]];
  }
  return hval + hash_table[str[len - 1]];
}

char *
in_word_set (str, len)
  register char *str;
  register unsigned int len;
{

  static char * wordlist[] =
  {
    "", "", "", 
    "use", 
    "else", 
    "", "", 
    "reverse", 
    "xor", 
    "", 
    "raise", 
    "", 
    "private", 
    "rem", 
    "with", 
    "", "", "", 
    "for", 
    "", 
    "entry", 
    "", 
    "package", 
    "", 
    "type", 
    "", "", "", "", 
    "case", 
    "range", 
    "select", 
    "subtype", 
    "", 
    "procedure", 
    "end", 
    "", "", 
    "abs", 
    "terminate", 
    "", 
    "access", 
    "renames", 
    "separate", 
    "exit", 
    "mod", 
    "", "", "", "", "", "", 
    "at", 
    "", 
    "task", 
    "abort", 
    "accept", 
    "generic", 
    "constant", 
    "body", 
    "", 
    "pragma", 
    "or", 
    "", 
    "loop", 
    "and", 
    "", "", 
    "is", 
    "return", 
    "", 
    "others", 
    "exception", 
    "", "", 
    "while", 
    "new", 
    "of", 
    "if", 
    "", 
    "array", 
    "elsif", 
    "delay", 
    "out", 
    "", "", 
    "not", 
    "delta", 
    "", "", "", "", "", 
    "all", 
    "do", 
    "", "", "", 
    "record", 
    "declare", 
    "", "", "", "", 
    "digits", 
    "", "", "", "", "", "", 
    "function", 
    "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", 
    "in", 
    "", "", "", "", "", "", "", "", "", 
    "", "", "", "", 
    "when", 
    "", "", "", "", "", "", "", "", 
    "goto", 
    "then", 
    "", "", "", 
    "begin", 
    "", "", "", "", "", 
    "limited", 
    "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "", 
    "null", 
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
