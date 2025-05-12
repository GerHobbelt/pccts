/* C code produced by gperf version 2.1 (ANSI C version) */
/*
 * Command-line: ../src/gperf -o -S2 -j1 -D -p -t 
 */


struct resword {char *name;};

#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 54
/*
 *    47 keywords
 *    53 is the maximum key range
 */

static int
hash (str, len)
  register char *str;
  register unsigned int  len;
{
  static unsigned char hash_table[] =
  {
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 41,  0, 15,
      0,  0, 27, 40, 32, 25, 54,  0,  2,  9,
      1,  0, 13, 54,  2,  5,  7, 34, 20, 32,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
     54, 54, 54, 54, 54, 54,
  };
  return len + hash_table[str[len - 1]] + hash_table[str[0]];
}

struct resword *
in_word_set (str, len)
  register char *str;
  register unsigned int len;
{

  static struct resword  wordlist[] =
  {
    "do", 
    "else", 
    "break", 
    "delete", 
    "double", 
    "extern", 
    "overload", 
    "return", 
    "operator", 
    "signed", 
    "register", 
    "enum", 
    "default", 
    "template", 
    "this", 
    "short", 
    "struct", 
    "case", 
    "private", 
    "char", 
    "protected", 
    "continue", 
    "void", 
    "class", 
    "static", 
    "const", 
    "volatile", 
    "virtual", 
    "inline", 
    "for", 
    "friend", 
    "public", 
    "int", 
    "new", 
    "while", 
    "sizeof", 
    "float", 
    "union", 
    "typedef", 
    "unsigned", 
    "switch", 
    "goto", 
    "auto", 
    "long", 
    "catch", 
    "asm", 
    "if", 
  };

  if (len <= MAX_WORD_LENGTH
      && len >= MIN_WORD_LENGTH)
  {
    register int key = hash (str, len);

    if (key <= MAX_HASH_VALUE
        && key >= MIN_HASH_VALUE)
    {
      if (key <= 25)
      {
        struct resword  *resword;
        

        switch (key - 2)
        {
        case   0:
          resword = &wordlist[0];
          break;
        case   2:
          resword = &wordlist[1];
          break;
        case   3:
          resword = &wordlist[2];
          break;
        case   4:
          resword = &wordlist[3];
          if (*str == *resword->name && !strcmp (str + 1, resword->name + 1)) return resword;
          resword = &wordlist[4];
          if (*str == *resword->name && !strcmp (str + 1, resword->name + 1)) return resword;
          return 0;
        case   5:
          resword = &wordlist[5];
          break;
        case   6:
          resword = &wordlist[6];
          break;
        case   7:
          resword = &wordlist[7];
          break;
        case   8:
          resword = &wordlist[8];
          break;
        case   9:
          resword = &wordlist[9];
          break;
        case  10:
          resword = &wordlist[10];
          break;
        case  11:
          resword = &wordlist[11];
          break;
        case  12:
          resword = &wordlist[12];
          break;
        case  13:
          resword = &wordlist[13];
          break;
        case  14:
          resword = &wordlist[14];
          break;
        case  15:
          resword = &wordlist[15];
          break;
        case  16:
          resword = &wordlist[16];
          break;
        case  17:
          resword = &wordlist[17];
          break;
        case  18:
          resword = &wordlist[18];
          break;
        case  19:
          resword = &wordlist[19];
          break;
        case  20:
          resword = &wordlist[20];
          break;
        case  21:
          resword = &wordlist[21];
          break;
        case  22:
          resword = &wordlist[22];
          break;
        case  23:
          resword = &wordlist[23];
          break;
        default:
          return 0;
        }
        if (*str == *resword->name && !strcmp (str + 1, resword->name + 1))
          return resword;
        return 0;
      }
      if (key <= 54)
      {
        struct resword  *resword;
        

        switch (key - 26)
        {
        case   0:
          resword = &wordlist[24];
          break;
        case   1:
          resword = &wordlist[25];
          break;
        case   2:
          resword = &wordlist[26];
          break;
        case   3:
          resword = &wordlist[27];
          break;
        case   5:
          resword = &wordlist[28];
          break;
        case   6:
          resword = &wordlist[29];
          break;
        case   7:
          resword = &wordlist[30];
          break;
        case   8:
          resword = &wordlist[31];
          break;
        case   9:
          resword = &wordlist[32];
          break;
        case  10:
          resword = &wordlist[33];
          break;
        case  11:
          resword = &wordlist[34];
          break;
        case  12:
          resword = &wordlist[35];
          break;
        case  13:
          resword = &wordlist[36];
          break;
        case  14:
          resword = &wordlist[37];
          break;
        case  15:
          resword = &wordlist[38];
          break;
        case  16:
          resword = &wordlist[39];
          break;
        case  17:
          resword = &wordlist[40];
          break;
        case  18:
          resword = &wordlist[41];
          break;
        case  19:
          resword = &wordlist[42];
          break;
        case  20:
          resword = &wordlist[43];
          break;
        case  26:
          resword = &wordlist[44];
          break;
        case  27:
          resword = &wordlist[45];
          break;
        case  28:
          resword = &wordlist[46];
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
