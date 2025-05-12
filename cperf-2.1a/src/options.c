/* Handles parsing the Options provided to the user.
   Copyright (C) 1989 Free Software Foundation, Inc.
   written by Douglas C. Schmidt (schmidt@ics.uci.edu)

This file is part of GNU GPERF.

GNU GPERF is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 1, or (at your option)
any later version.

GNU GPERF is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU GPERF; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "options.h"
#include "iterator.h"
#include "stderr.h"
#include "keylist.h"

/* Size to jump on a collision. */
#define DEFAULT_JUMP_VALUE 5

/* Default name for generated lookup function. */
#define DEFAULT_NAME "in_word_set"

/* Default name for the key component. */
#define DEFAULT_KEY "name"

/* Default name for generated hash function. */
#define DEFAULT_HASH_NAME "hash"

/* Globally visible OPTIONS object. */
OPTIONS option;

/* Default delimiters that separate keywords from their attributes. */
#define DEFAULT_DELIMITERS ",\n"



FILE *report_file = NULL;



/* Prints program usage to standard error stream. */

void 
usage (void)
{ 
  report_error ("usage: %n "
                "[-acCdDef[num]gGhH<hashname>i<init>jk<keys>]\n"
                "    [-K<keyname>lnN<name>oprs<size>S<switches>tTv]\n"
                "\n"
                "  (type %n -h for help)\n");
}

/* Sorts the key positions *IN REVERSE ORDER!!*
   This makes further routines more efficient.  Especially when generating code.
   Uses a simple Insertion Sort since the set is probably ordered.
   Returns 1 if there are no duplicates, 0 otherwise. */

static int 
key_sort (char *base, int len)
{
  int i, j;

  for (i = 0, j = len - 1; i < j; i++) 
    {
      int curr, tmp;
      
      for (curr = i + 1,tmp = base[curr]; curr > 0 && tmp >= base[curr - 1]; curr--) 
        if ((base[curr] = base[curr - 1]) == tmp) /* oh no, a duplicate!!! */
          return 0;

      base[curr] = tmp;
    }

  return 1;
}

/* Dumps option status when debug is set. */

void
options_destroy (void)
{ 
  if (OPTION_ENABLED (option, DEBUG))
    {
      char *ptr;

      fprintf (report_file,
                       "\n"
                       "dumping Options:\n"
                       "DEBUG is....................: %s\n"
                       "ORDER is....................: %s\n"
                       "ANSI is.....................: %s\n"
                       "TYPE is.....................: %s\n"
                       "GNU is......................: %s\n"
                       "RANDOM is...................: %s\n"
                       "DEFAULTCHARS is.............: %s\n"
                       "SWITCH is...................: %s\n"
                       "POINTER is..................: %s\n"
                       "NOLENGTH is.................: %s\n"
                       "LENTABLE is.................: %s\n"
                       "DUP is......................: %s\n"
                       "COMP is.....................: %s\n"
                       "FAST is.....................: %s\n"
                       "NOTYPE is...................: %s\n"
                       "GLOBAL is...................: %s\n"
                       "CONST is....................: %s\n"
                       "VERBOSE_C_STATISTICS is ....: %s\n"
                       "iterations = %d\n"
                       "lookup function name = %s\n"
                       "hash function name = %s\n"
                       "key name = %s\n"
                       "jump value = %d\n"
                       "max associcated value = %d\n"
                       "initial associated value = %d\n"
                       "delimiters = %s\n"
                       "number of switch statements = %d\n"
                       "approximate switch statement size = %d\n",
               OPTION_ENABLED (option, DEBUG) ? "enabled" : "disabled", 
               OPTION_ENABLED (option, ORDER) ? "enabled" : "disabled",
               OPTION_ENABLED (option, ANSI) ? "enabled" : "disabled",
               OPTION_ENABLED (option, TYPE) ? "enabled" : "disabled",
               OPTION_ENABLED (option, GNU) ? "enabled" : "disabled",
               OPTION_ENABLED (option, RANDOM) ? "enabled" : "disabled",
               OPTION_ENABLED (option, DEFAULTCHARS) ? "enabled" : "disabled",
               OPTION_ENABLED (option, SWITCH) ? "enabled" : "disabled",
               OPTION_ENABLED (option, POINTER) ? "enabled" : "disabled",
               OPTION_ENABLED (option, NOLENGTH) ? "enabled" : "disabled",
               OPTION_ENABLED (option, LENTABLE) ? "enabled" : "disabled",
               OPTION_ENABLED (option, DUP) ? "enabled" : "disabled",
               OPTION_ENABLED (option, COMP) ? "enabled" : "disabled",
               OPTION_ENABLED (option, FAST) ? "enabled" : "disabled",
               OPTION_ENABLED (option, NOTYPE) ? "enabled" : "disabled",
               OPTION_ENABLED (option, GLOBAL) ? "enabled" : "disabled",
               OPTION_ENABLED (option, CONST) ? "enabled" : "disabled",
               OPTION_ENABLED (option, VERBOSE_C_STATISTICS) ? "enabled" : "disabled",
               option.iterations, option.function_name, option.hash_name,
               option.key_name, option.jump, option.size - 1, 
               option.initial_asso_value, option.delimiters, option.total_switches,
               keyword_list_length () / option.total_switches);

      if (OPTION_ENABLED (option, ALLCHARS)) 
        fprintf (report_file, "all characters are used in the hash function\n");
      fprintf (report_file, "maximum charset size = %d\n"
                       "key positions are: \n", 
               option.total_charset_size);

      for (ptr = option.key_positions; *ptr != EOS; ptr++) 
        if (*ptr == WORD_END) 
          fprintf (report_file, "$\n");
        else 
          fprintf (report_file, "%d\n", *ptr);

      fprintf (report_file, "finished dumping Options\n");
    }
}

/* Parses the command line Options and sets appropriate flags in option.option_word. */

void
options_init (int argc, char **argv)
{ 
  int   option_char;
  
  option.key_positions[0]   = WORD_START;
  option.key_positions[1]   = WORD_END;
  option.key_positions[2]   = EOS;
  option.total_charset_size = 2;
  option.jump               = DEFAULT_JUMP_VALUE;
  option.option_word        = (int) DEFAULTCHARS;
  option.function_name      = DEFAULT_NAME;
  option.hash_name          = DEFAULT_HASH_NAME;
  option.key_name           = DEFAULT_KEY;
  option.delimiters         = DEFAULT_DELIMITERS;
  option.initial_asso_value = option.size = option.iterations = 0;
  option.total_switches     = 1;
  option.argument_count     = argc;
  option.argument_vector    = argv;
  set_program_name (argv[0]);
  
  while ((option_char = getopt (argc, argv, "adcCDe:f:gGhH:i:j:k:K:lnN:oprs:S:tTvV")) != EOF)
    {
      switch (option_char)
        {
        case 'a':               /* Generated coded uses the ANSI prototype format. */
          { 
            SET_OPTION (option, ANSI);
            break;
          }
        case 'c':               /* Generate strncmp rather than strcmp. */
          {
            SET_OPTION (option, COMP);
            break;
          }
        case 'C':               /* Make the generated tables readonly (const). */
          {
            SET_OPTION (option, CONST);
            break;
          }
        case 'd':               /* Enable debugging option. */
          { 
            SET_OPTION (option, DEBUG);
            report_error ("starting program %n, version %s, with debugging on.\n",
                          version_string);
            break;
          }   
        case 'D':               /* Enable duplicate option. */
          { 
            SET_OPTION (option, DUP);
            /* [i_a] fix: -D forces -S1 if not already set by user! */
            if (!OPTION_ENABLED (option, SWITCH))
            {
              SET_OPTION (option, SWITCH);
              option.total_switches = 1;
            }
            break;
          }   
        case 'e': /* Allows user to provide keyword/attribute separator */
          {
            SET_DELIMITERS (option, optarg);
            break;
          }
        case 'f':               /* Generate the hash table ``fast.'' */
          {
            SET_OPTION (option, FAST);
            if ((option.iterations = atoi (optarg)) < 0) 
              {
                report_error ("iterations value must not be negative, assuming 0\n");
                option.iterations = 0;
              }
            break;
          }
        case 'g':               /* Use the ``inline'' keyword for generated sub-routines. */
          { 
            SET_OPTION (option, GNU);
            break;
          }
        case 'G':               /* Make the keyword table a global variable. */
          { 
            SET_OPTION (option, GLOBAL);
            break;
          }
        case 'h':               /* Displays a list of helpful Options to the user. */
          { 
            report_error (""
"-a  Generate ANSI standard C output code, i.e., function prototypes.\n"
"-c  Generate comparison code using strncmp rather than strcmp.\n"
"-C  Make the contents of generated lookup tables constant, i.e., readonly.\n"
"-d  Enables the debugging option (produces verbose output to StdErr).\n"
"-D  Handle keywords that hash to duplicate values.  This is useful\n"
"    for certain highly redundant keyword sets.  It enables the -S option.\n"
"-e  Allow user to provide a string containing delimiters used to separate\n"
"    keywords from their attributes.  Default is \",\\n\"\n"
"-f  Generate the perfect hash function ``fast.''  This decreases GPERF's\n"
"    running time at the cost of minimizing generated table-size.\n"
"    The numeric argument represents the number of times to iterate when\n"
"    resolving a collision.  `0' means ``iterate by the number of keywords''.\n"
"-g  Assume a GNU compiler, e.g., g++ or gcc.  This makes all generated\n"
"    routines use the ``inline'' keyword to remove cost of function calls.\n"
"-G  Generate the static table of keywords as a static global variable,\n"
"    rather than hiding it inside of the lookup function (which is the\n"
"    default behavior).\n"
"-h  Prints this mesage.\n");
        report_error (
"-H  Allow user to specify name of generated hash function. Default is `hash'.\n"
"-i  Provide an initial value for the associate values array.  Default is 0.\n"
"    Setting this value larger helps inflate the size of the final table.\n"
"-j  Affects the ``jump value,'' i.e., how far to advance the associated\n"
"    character value upon collisions.  Must be an odd number, default is %d.\n"
"-k  Allows selection of the key positions used in the hash function.\n"
"    The allowable choices range between 1-%d, inclusive.  The positions\n"
"    are separated by commas, ranges may be used, and key positions may\n"
"    occur in any order.  Also, the meta-character '*' causes the generated\n"
"    hash function to consider ALL key positions, and $ indicates the\n"
"    ``final character'' of a key, e.g., $,1,2,4,6-10.\n"
"    Note: instead of '$' you may use the '@' character for those systems\n"
"          that have trouble passing a '$' character in a commandline\n"
"          argument.\n"
"-K  Allow user to select name of the keyword component in the keyword\n"
"    structure.\n"
"-l  Compare key lengths before trying a string comparison.  This helps\n"
"    cut down on the number of string comparisons made during the lookup.\n"
"-n  Do not include the length of the keyword when computing the hash function\n"
"-N  Allow user to specify name of generated lookup function.  Default\n"
"    name is `in_word_set.'\n"
"-o  Reorders input keys by frequency of occurrence of the key sets.\n"
"    This should decrease the search time dramatically.\n"
"-p  Changes the return value of the generated function ``in_word_set''\n"
"    from its default boolean value (i.e., 0 or 1), to type ``pointer\n"
"    to wordlist array''  This is most useful when the -t option, allowing\n"
"    user-defined structs, is used.\n",
                    DEFAULT_JUMP_VALUE, MAX_KEY_POS - 1);
      report_error (
"-r  Utilizes randomness to initialize the associated values table.\n"
"-s  Affects the size of the generated hash table.  The numeric argument\n"
"    for this option indicates ``how many times larger'' the table range\n"
"    should be, in relationship to the number of keys, e.g. a value of 3\n"
"    means ``make the table about 3 times larger than the number of input\n"
"    keys.''  A larger table should decrease the time required for an\n"
"    unsuccessful search, at the expense of extra table space.  Default\n"
"    value is 1.  This actual table size may vary somewhat.\n"
"-S  Causes the generated C code to use a switch statement scheme, rather\n"
"    than an array lookup table.  This can lead to a reduction in both\n"
"    time and space requirements for some keyfiles.  The argument to\n"
"    this option determines how many switch statements are generated.\n"
"    A value of 1 generates 1 switch containing all the elements, a value of 2\n"
"    generates 2 tables with 1/2 the elements in each table, etc.  This\n"
"    is useful since many C compilers cannot correctly generate code for\n"
"    large switch statements.\n"
"    the expense of longer time for each lookup.  Mostly important for\n"
"    *large* input sets, i.e., greater than around 100 items or so.\n"
"-t  Allows the user to include a structured type declaration for \n"
"    generated code. Any text before %%%% is consider part of the type\n"
"    declaration.  Key words and additional fields may follow this, one\n"
"    group of fields per line.\n"
"-T  Prevents the transfer of the type declaration to the output file.\n"
"    Use this option if the type is already defined elsewhere.\n"
"-v  Prints out the current version number\n%e%a\n"
"-V  write all statistics to StdOut (generated C-file)\n",
                    usage);
          }
        case 'H':               /* Sets the name for the hash function */
          {
            option.hash_name = optarg;
            break;
          }
        case 'i':               /* Sets the initial value for the associated values array. */
          { 
            if ((option.initial_asso_value = atoi (optarg)) < 0) 
              report_error ("initial value %d must be non-zero, ignoring and continuing\n", 
                            option.initial_asso_value);
            if (OPTION_ENABLED (option, RANDOM))
              report_error ("warning, -r option superceeds -i, ignoring -i option and continuing\n");
            break;
          }
        case 'j':               /* Sets the jump value, must be odd for later algorithms. */
          { 
            if ((option.jump = atoi (optarg)) < 0)
              report_error ("jump value %d must be a positive number\n"
                            "%e%a", 
              option.jump, usage);
            else if (option.jump && EVEN (option.jump))
              report_error ("jump value %d should be odd, adding 1 and continuing...\n",
              option.jump++);
            break;
          }
        case 'k':               /* Sets key positions used for hash function. */
          {
            int BAD_VALUE = -1;
            int value;

            iterator_init (optarg, 1, MAX_KEY_POS - 1, WORD_END, BAD_VALUE, EOS);

            if (*optarg == '*') /* Use all the characters for hashing!!!! */
              {
                UNSET_OPTION (option, DEFAULTCHARS);
                SET_OPTION (option, ALLCHARS);
              }
            else
              {
                char *key_pos;

                for (key_pos = option.key_positions; (value = next ()) != EOS; key_pos++)
                  if (value == BAD_VALUE)
                    report_error ("illegal key value or range, use 1,2,3-%d,'$','@' or '*'.\n"
                                  "%e%a",
                    (MAX_KEY_POS - 1),usage);
                  else
                    *key_pos = value;;

                *key_pos = EOS;

                if (! (option.total_charset_size = (key_pos - option.key_positions)))
                  report_error ("no keys selected\n"
                                "%e%a", usage);
                else if (! key_sort (option.key_positions, option.total_charset_size))
                  report_error ("duplicate keys selected\n"
                                "%e%a", usage);

                if (option.total_charset_size != 2
                    || (option.key_positions[0] != 1 || option.key_positions[1] != WORD_END))
                  UNSET_OPTION (option, DEFAULTCHARS);
              }
            break;
          }
        case 'K':               /* Make this the keyname for the keyword component field. */
          {
            option.key_name = optarg;
            break;
          }
        case 'l':               /* Create length table to avoid extra string compares. */
          {
            SET_OPTION (option, LENTABLE);
            break;
          }
        case 'n':               /* Don't include the length when computing hash function. */
          {
            SET_OPTION (option, NOLENGTH);
            break; 
          }
        case 'N':               /* Make generated lookup function name be optarg */
          { 
            option.function_name = optarg;
            break;
          }
        case 'o':               /* Order input by frequency of key set occurrence. */
          { 
            SET_OPTION (option, ORDER);
            break;
          }   
        case 'p':               /* Generated lookup function now a pointer instead of int. */
          { 
            SET_OPTION (option, POINTER);
            break;
          }
        case 'r':               /* Utilize randomness to initialize the associated values table. */
          { 
            SET_OPTION (option, RANDOM);
            if (option.initial_asso_value != 0)
              report_error ("warning, -r option superceeds -i, disabling -i option and continuing\n");
            break;
          }
        case 's':               /* Range of associated values, determines size of final table. */
          {
            if ((option.size = atoi (optarg)) <= 0) 
              report_error ("improper range argument %s\n"
                            "%e%a"
                           , optarg, usage);
            else if (option.size > 50) 
              report_error ("%d is excessive, did you really mean this?! (type %n -h for help)\n", 
              option.size);
            break; 
          }       
        case 'S':               /* Generate switch statement output, rather than lookup table. */
          { 
            SET_OPTION (option, SWITCH);
            if ((option.total_switches = atoi (optarg)) <= 0)
              report_error ("number of switches %s must be a positive number\n"
                            "%e%a"
                           , optarg, usage);
            break;
          }
        case 't':               /* Enable the TYPE mode, allowing arbitrary user structures. */
          { 
            SET_OPTION (option, TYPE);
            break;
          }
        case 'T':               /* Don't print structure definition. */
          {
            SET_OPTION (option, NOTYPE);
            break;
          }
        case 'v':               /* Print out the version and quit. */
          report_error ("%n: version %s\n"
                        "%e%a\n"
                       , version_string, usage);
        case 'V':               /* write all statistics to stdout as C comment. */
          {
            SET_OPTION (option, VERBOSE_C_STATISTICS);
            break;
          }
        default: 
          report_error ("%e%a", usage);
        }
    }

  if (argv[optind] && ! freopen (argv[optind], "r", stdin))
  {
    report_error ("unable to read key word file %s\n"
                  "%e%a"
                 , argv[optind], usage);
  }
  if (argv[optind])
  {
    optind++;
  }

  if (argv[optind] && ! freopen (argv[optind], "w", stdout))
  {
    report_error ("unable to write destination .C file %s\n"
                  "%e%a"
                 , argv[optind], usage);
  }
  if (argv[optind])
  {
    optind++;
  }

  if (optind++ < argc) 
  {
    report_error ("extra trailing arguments to %n\n"
                  "%e%a"
                 , usage);
  }

  if (OPTION_ENABLED (option, VERBOSE_C_STATISTICS))
  {
    report_file = stdout;
  }
}

/* Output command-line Options. */
void 
print_options (void)
{ 
  int i;

  printf ("/*\n"
          " * Command-line: ");

  for (i = 0; i < option.argument_count; i++) 
    printf ("%s ", option.argument_vector[i]);
   
  printf ("\n"
          " */\n"
          "\n");
}

