#ifndef _prototype_h
#define _prototype_h

#include <stdio.h>


#define GATHER_STATISTICS    1


typedef char boolean;

#if !defined(FALSE) || !defined(TRUE)
#undef FALSE
#undef TRUE

#define FALSE 0
#define TRUE 1
#endif

#define ODD(X) ((X) & 1)
#define EVEN(X) (!((X) & 1))



/* Current program version. */
extern char *version_string;

/* For communication from `getopt' to the caller.
   When `getopt' finds an option that takes an argument,
   the argument value is returned here.
   Also, when `ordering' is RETURN_IN_ORDER,
   each non-option ARGV-element is returned here.  */

extern char *optarg;

/* Index in ARGV of the next element to be scanned.
   This is used for communication to and from the caller
   and for communication between successive calls to `getopt'.

   On entry to `getopt', zero means this is the first call; initialize.

   When `getopt' returns EOF, this is the index of the first of the
   non-option elements that the caller should itself scan.

   Otherwise, `optind' communicates from one call to the next
   how much of ARGV has been scanned so far.  */

extern int optind;

extern FILE *report_file;




void *xmalloc (size_t size);
void xfree (void **p);
void *buffered_malloc (size_t size);

int getopt (int argc, char **argv, char *optstring);

#endif /* _prototype_h */
