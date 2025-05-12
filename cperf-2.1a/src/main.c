/* Driver program for the Perfect hash function generator.
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

/* Simple driver program for the Perfect.hash function generator.
   Most of the hard work is done in class Perfect and its class methods. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#include "stderr.h"
#include "options.h"
#include "perfect.h"

#if defined(_MSC_VER)
#define STRDUP _strdup /* [i_a] because __STDC__ has been defined; this one must be used... */
#else
#define STRDUP strdup 
#endif




static int add_argv_elem(int *argc, char ***argv, char *elem)
{
	if (!argv[0])
	{
		argv[0] = malloc(sizeof(argv[0]) * 2);
		if (!argv[0]) return -1;
		argc[0] = 1;
	}
	else
	{
		argv[0] = realloc(argv[0], sizeof(argv[0]) * (argc[0] + 2));
		if (!argv[0]) return -1;
		argc[0]++;
	}
	argv[0][argc[0] - 1] = STRDUP(elem);
	if (!argv[0][argc[0] - 1]) return -1;
	argv[0][argc[0]] = NULL;
	return 0;
}
	
static int release_argv_elems(int *argc, char ***argv)
{
	int i;
	for (i = *argc - 1; i >= 0; i--)
	{
		/* free strdup-ped strings */
		free(argv[0][i]);
	}
	free(*argv);
	*argv = 0;
	*argc = 0;
	return 0;
}
	
/*
 * process '@filename' commandline arguments (response files)
 */
static int handle_response_files(int *argc, char ***argv)
{
	int new_argc = 0;
	char **new_argv = NULL;
	int i;
	FILE *f;
	char str[1024];
	char *elem;
	char *endp;

	for (i = 0; i < argc[0]; i++)
	{
		if (i == 0)
		{
			if (add_argv_elem(&new_argc, &new_argv, argv[0][0]))
				return -1;
			continue;
		}
		if (argv[0][i][0] == '@')
		{
			f = fopen(argv[0][i]+1, "r");
			if (!f)
			{
				fprintf(stderr, "Cannot open responsefile %s\n", argv[0][i]+1);
				return -1;
			}
			while (!feof(f))
			{
				str[0] = 0;
				fgets(str, sizeof(str), f);
				for (elem = str; *elem; )
				{
					/* skip leading whitespace */
					while (*elem && (isspace(*elem) || !strchr(" \t\r\n", *elem)))
						elem++;
					switch (*elem)
					{
					case 0:
						break;

					case '\'':
					case '\"':
						/* quoted argument... */
						{
							char c = *elem++;

							endp = elem;
							while (*endp && *endp != c)
								endp++;
							if (*endp != c)
							{
								fprintf(stderr, "unterminated string in response file\n");
								return -1;
							}
							*endp++ = 0;
							if (add_argv_elem(&new_argc, &new_argv, elem))
								return -1;
							elem = endp;
						}
						continue;

					default:
						endp = elem;
						while (*endp && !isspace(*endp) && !strchr(" \t\r\n", *endp))
							endp++;
						if (*endp)
							*endp++ = 0;
						if (add_argv_elem(&new_argc, &new_argv, elem))
							return -1;
						elem = endp;
						continue;
					}
				}
			}
			fclose(f);
		}
		else
		{
			/* regular argument... */
			if (add_argv_elem(&new_argc, &new_argv, argv[0][i]))
				return -1;
		}
	}

	*argc = new_argc;
	*argv = new_argv;

#if defined(_DEBUG) && 0
	for (i = 0; i < argc[0]; i++)
	{
		printf("argv[%d] = \"%s\"\n", i, argv[0][i]);
	}
#endif

	return 0;
}






/* Calls the appropriate intialization routines for each
   ADT.  Note that certain initialization routines require
   initialization *after* certain values are computed.  Therefore,
   they cannot be called here. */
   
static void 
init_all (int argc, char **argv)
{
  options_init (argc, argv);    
  key_list_init ();
  perfect_init ();              
}

/* Calls appropriate destruction routines for each ADT.  These
   routines print diagnostics if the debugging option is enabled. */

static void
destroy_all (void)
{
  if (OPTION_ENABLED (option, VERBOSE_C_STATISTICS))
    fprintf(report_file, "\n"
                         "/***************************************************************************\n");

  options_destroy ();
  key_list_destroy ();
  perfect_destroy ();

  if (OPTION_ENABLED (option, VERBOSE_C_STATISTICS))
    fprintf(report_file, "\n"
                         " ***************************************************************************/\n"
                         "\n");
}

/* Driver for perfect hash function generation. */

int
main (int argc, char **argv)
{
  struct tm *tm;
  time_t     clock; 
  int        status = EXIT_SUCCESS;
  
  report_file = stderr;

  time (&clock);
  tm = localtime (&clock);

    /*
       [i_a] allow 'long commandlines' on MSDOS based systems where the commandline is limited to 127 characters.
       This code allows you to use the Borland mechanism used to overcome this limit: 'response files'.

       Any argument on your commandline, prefixed by a single '@' character, will be treated as a 'response file'
       and loaded by the commandline parser: the file is treated as a text file, where each line contains
       an additional commandline option.

       Empty lines in the reponse file are ignored, so are lines containing only whitespace.

       If your commandline argument contains mandatory whitespace, you must use quotes (' or ") to delimit the
       commandline argument on the line. Any leading or trailing whitespace on each line is ignored.

       Example:

         util @<respfilename>

       with <respfile> contents:

         a
         -x
         -o outputfile
         -e 'My regular expression with "" quotes'

       will produce the following argv list:

         a
         -x
         -o
         outputfile
         -e
         My regular expression with "" quotes

       just as if you had entered

         a -x -o outputfile -e 'My regular expression with "" quotes'

       on the commandline itself.

       If you wish to use 'response files' from inside MAKE, check out the Borland/Microsft make manuals for
       info how to do this. (Yes, this can be done; MAKE will even generate the reponse file for you.)
     */
  if (handle_response_files(&argc, &argv))
  {
    fprintf(stderr, "error preparing arguments.\n");
	status = EXIT_FAILURE;
  }
  else
  {
    /* Sets the options. */
    init_all (argc, argv);

    fprintf (report_file, "\n"
                            " /* starting time is %d:%d:%d */\n"
                            "\n", tm->tm_hour, tm->tm_min, tm->tm_sec);

    /* Generates the perfect hash table.
        Also prints generated code neatly to the output. */
    status = perfect_generate ();
    destroy_all ();

    time (&clock);
    tm = localtime (&clock);
    fprintf (report_file, "\n"
                            "  /* ending time is %d:%d:%d */\n"
                            "\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
  }
  release_argv_elems(&argc, &argv);
  return status;
}
