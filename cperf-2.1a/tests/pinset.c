/* C code produced by gperf version 2.1 (ANSI C version) */
/*
 * Command-line: ../src/gperf -o -S1 -p 
 */



#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 63
/*
 *    36 keywords
 *    62 is the maximum key range
 */

static int
hash (str, len)
  register char *str;
  register unsigned int  len;
{
  static unsigned char hash_table[] =
  {
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 40,  5,  5,
      0,  0, 40, 15, 15, 10, 63, 63,  0, 30,
     15,  0, 25, 63,  5, 10, 10, 10,  5,  5,
     63,  0, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
     63, 63, 63, 63, 63, 63,
  };
  return len + hash_table[str[len - 1]] + hash_table[str[0]];
}

char *
in_word_set (str, len)
  register char *str;
  register unsigned int len;
{
  if (len <= MAX_WORD_LENGTH
      && len >= MIN_WORD_LENGTH)
  {
    register int key = hash (str, len);

    if (key <= MAX_HASH_VALUE
        && key >= MIN_HASH_VALUE)
    {
      if (key <= 63)
      {
        char *resword;
        

        switch (key - 2)
        {
        case   0:
          resword = "do";
          break;
        case   1:
          resword = "end";
          break;
        case   2:
          resword = "else";
          break;
        case   3:
          resword = "label";
          break;
        case   4:
          resword = "downto";
          break;
        case   5:
          resword = "or";
          break;
        case   6:
          resword = "div";
          break;
        case   7:
          resword = "case";
          break;
        case   8:
          resword = "while";
          break;
        case   9:
          resword = "record";
          break;
        case  10:
          resword = "to";
          break;
        case  11:
          resword = "var";
          break;
        case  12:
          resword = "type";
          break;
        case  13:
          resword = "until";
          break;
        case  16:
          resword = "nil";
          break;
        case  17:
          resword = "goto";
          break;
        case  18:
          resword = "const";
          break;
        case  19:
          resword = "repeat";
          break;
        case  21:
          resword = "set";
          break;
        case  22:
          resword = "with";
          break;
        case  23:
          resword = "begin";
          break;
        case  25:
          resword = "in";
          break;
        case  26:
          resword = "not";
          break;
        case  27:
          resword = "then";
          break;
        case  29:
          resword = "packed";
          break;
        case  31:
          resword = "mod";
          break;
        case  32:
          resword = "procedure";
          break;
        case  40:
          resword = "of";
          break;
        case  41:
          resword = "and";
          break;
        case  42:
          resword = "file";
          break;
        case  43:
          resword = "array";
          break;
        case  45:
          resword = "forward";
          break;
        case  46:
          resword = "for";
          break;
        case  50:
          resword = "if";
          break;
        case  60:
          resword = "program";
          break;
        case  61:
          resword = "function";
          break;
        default:
          return 0;
        }
        if (*str == *resword && !strcmp (str + 1, resword + 1))
          return resword;
        return 0;
      }
    }
  }
  return 0;
}
