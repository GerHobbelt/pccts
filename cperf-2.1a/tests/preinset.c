/* C code produced by gperf version 2.1 (ANSI C version) */
/*
 * Command-line: ../src/gperf -p -D -S1 -k1,$ -s 2 -o adapredefined.gperf 
 */



#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 17
#define MIN_HASH_VALUE 5
#define MAX_HASH_VALUE 111
/*
 *    54 keywords
 *   107 is the maximum key range
 */

static int
hash (str, len)
  register char *str;
  register unsigned int  len;
{
  static unsigned char hash_table[] =
  {
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111,   0,  35,  35,
       0,   0,  50,   5,   0,   5, 111, 111,  20,  40,
      35, 111,  15, 111,  60,  10,   5, 111,  45,  25,
      40, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111, 111, 111, 111, 111,
     111, 111, 111, 111, 111, 111,
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
      if (key <= 111)
      {
        char *resword;
        

        switch (key - 5)
        {
        case    0:
          resword = "delta";
          break;
        case    3:
          resword = "aft";
          break;
        case    4:
          resword = "true";
          break;
        case    5:
          resword = "image";
          break;
        case    9:
          resword = "size";
          break;
        case   10:
          resword = "terminated";
          break;
        case   11:
          resword = "digits";
          break;
        case   12:
          resword = "address";
          break;
        case   14:
          resword = "pred";
          break;
        case   15:
          resword = "safe_large";
          break;
        case   16:
          resword = "string";
          break;
        case   17:
          resword = "storage_size";
          break;
        case   18:
          resword = "positive";
          break;
        case   20:
          resword = "large";
          break;
        case   21:
          resword = "length";
          break;
        case   23:
          resword = "pos";
          break;
        case   24:
          resword = "last";
          break;
        case   25:
          resword = "width";
          break;
        case   27:
          resword = "lastbit";
          break;
        case   30:
          resword = "small";
          break;
        case   34:
          resword = "base";
          break;
        case   35:
          resword = "safe_small";
          break;
        case   37:
          resword = "epsilon";
          break;
        case   38:
          resword = "callable";
          break;
        case   39:
          resword = "emax";
          break;
        case   40:
          resword = "count";
          break;
        case   41:
          resword = "constrained";
          break;
        case   43:
          resword = "mantissa";
          break;
        case   44:
          resword = "succ";
          break;
        case   45:
          resword = "value";
          break;
        case   49:
          resword = "fore";
          break;
        case   50:
          resword = "false";
          break;
        case   51:
          resword = "machine_mantissa";
          break;
        case   53:
          resword = "position";
          break;
        case   54:
          resword = "safe_emax";
          break;
        case   55:
          resword = "first";
          if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
          resword = "float";
          if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
          return 0;
        case   57:
          resword = "natural";
          break;
        case   58:
          resword = "firstbit";
          break;
        case   59:
          resword = "machine_rounds";
          break;
        case   60:
          resword = "range";
          break;
        case   62:
          resword = "machine_overflows";
          break;
        case   63:
          resword = "val";
          break;
        case   67:
          resword = "integer";
          break;
        case   72:
          resword = "boolean";
          break;
        case   73:
          resword = "tasking_error";
          break;
        case   78:
          resword = "storage_error";
          break;
        case   82:
          resword = "machine_emin";
          break;
        case   83:
          resword = "program_error";
          break;
        case   87:
          resword = "machine_emax";
          break;
        case   88:
          resword = "machine_radix";
          break;
        case   99:
          resword = "character";
          break;
        case  103:
          resword = "numeric_error";
          break;
        case  106:
          resword = "constraint_error";
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
