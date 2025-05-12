/* C code produced by gperf version 2.1 (ANSI C version) */
/*
 * Command-line: ../src/gperf -p -c -l -S1 -C -o c.gperf 
 */



#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 8
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 41
/*
 *    24 keywords
 *    40 is the maximum key range
 */

static int
hash (str, len)
  register char *str;
  register unsigned int  len;
{
  static const unsigned char hash_table[] =
  {
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 25, 41, 10,
     15,  0,  0,  5, 25,  0, 41, 41, 10, 41,
     25,  0, 41, 41,  5, 10,  0,  0,  5,  5,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
     41, 41, 41, 41, 41, 41,
  };
  return len + hash_table[str[len - 1]] + hash_table[str[0]];
}

const char *
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
      if (key <= 41)
      {
        const char *resword;
        int key_len;

        switch (key - 2)
        {
        case   0:
          resword = "if";
          key_len = 2;
          break;
        case   1:
          resword = "int";
          key_len = 3;
          break;
        case   2:
          resword = "else";
          key_len = 4;
          break;
        case   3:
          resword = "float";
          key_len = 5;
          break;
        case   5:
          resword = "typedef";
          key_len = 7;
          break;
        case   6:
          resword = "for";
          key_len = 3;
          break;
        case   7:
          resword = "goto";
          key_len = 4;
          break;
        case   8:
          resword = "while";
          key_len = 5;
          break;
        case   9:
          resword = "repeat";
          key_len = 6;
          break;
        case  11:
          resword = "volatile";
          key_len = 8;
          break;
        case  12:
          resword = "case";
          key_len = 4;
          break;
        case  13:
          resword = "until";
          key_len = 5;
          break;
        case  14:
          resword = "struct";
          key_len = 6;
          break;
        case  15:
          resword = "do";
          key_len = 2;
          break;
        case  17:
          resword = "char";
          key_len = 4;
          break;
        case  19:
          resword = "double";
          key_len = 6;
          break;
        case  21:
          resword = "unsigned";
          key_len = 8;
          break;
        case  22:
          resword = "void";
          key_len = 4;
          break;
        case  24:
          resword = "static";
          key_len = 6;
          break;
        case  27:
          resword = "auto";
          key_len = 4;
          break;
        case  28:
          resword = "union";
          key_len = 5;
          break;
        case  29:
          resword = "signed";
          key_len = 6;
          break;
        case  34:
          resword = "return";
          key_len = 6;
          break;
        case  39:
          resword = "switch";
          key_len = 6;
          break;
        default:
          return 0;
        }
        if (len == key_len
            && *str == *resword && !strncmp (str + 1, resword + 1, len - 1))
          return resword;
        return 0;
      }
    }
  }
  return 0;
}
