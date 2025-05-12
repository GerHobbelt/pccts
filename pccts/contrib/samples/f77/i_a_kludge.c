/* [i_a] quick kludges to get the stuff to compile :-( */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "pcctscfg.h"
#include "stdpccts.h"

#ifdef PCCTS_USE_STDARG
#include <stdarg.h>
#else
#include <varargs.h>
#endif



#ifdef PCCTS_USE_STDARG
int printf_stderr_continued(const char *fmt, ...)
#else
int printf_stderr_continued(va_alist)
va_dcl
#endif
{
  va_list args;
#ifndef PCCTS_USE_STDARG			/* MR20 */
	const char *fmt;
#endif

#ifdef PCCTS_USE_STDARG         /* MR20 */
	va_start(args, fmt);
#else
	va_start(ap);
	fmt = va_arg(ap, char *);
#endif

  vfprintf(stderr, fmt, args);
  va_end(args);

  return 0;
}
