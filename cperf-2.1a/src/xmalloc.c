/* Provide a useful malloc sanity checker and an efficient buffered memory
   allocator that reduces calls to malloc. 
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

#include "prototype.h"

/* Grabs SIZE bytes of dynamic memory or dies trying! */
void *xmalloc (size_t size)
{
  void *temp = malloc (size);
  
  if (temp == 0)
  {
    fprintf (stderr, "out of virtual memory\n");
    exit (1);
  }
  return temp;
}

void xfree (void **p)
{
  if (*p) 
  {
    free(*p);
    *p = NULL;
  }
  else
  {
    fprintf (stderr, "WARNING: trying to free already freed block!\n");
#if 0
    exit (1);
#endif
  }
  return;
}

/* Determine default alignment.  If your C compiler does not
   like this then try something like #define DEFAULT_ALIGNMENT 8. */
struct fooalign {char x; double d;};
#define ALIGNMENT ((char *)&((struct fooalign *) 0)->d - (char *)0)

/* Provide an abstraction that cuts down on the number of
   calls to MALLOC by buffering the memory pool from which
   items are allocated. */

void *buffered_malloc (size_t size)
{
  void *temp;
  static char *buf_start = 0;   /* Large array used to reduce calls to NEW. */
  static char *buf_end = 0;     /* Indicates end of BUF_START. */
  static size_t buf_size = 4 * BUFSIZ; /* Size of buffer pointed to by BUF_START. */

  /* Align this on correct boundaries, just to be safe... */
  size = ((size + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT;

  /* If we are about to overflow our buffer we'll just grab another
     chunk of memory.  Since we never free the original memory it
     doesn't matter that no one points to the beginning of that
     chunk.  Furthermore, as a heuristic, we double the
     size of the new buffer! */
  
  if (buf_start + size >= buf_end)
    {
      buf_size = buf_size * 2 > size ? buf_size * 2 : size;
      buf_start = (char *)xmalloc (buf_size);
      buf_end = buf_start + buf_size;
    }

  temp = buf_start;
  buf_start += size;
  return temp;
}
