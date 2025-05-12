
#include <stdio.h>
#include <stdlib.h>

/*
 * WARNING: Borland C++ 5.x has it's own
 *   set.h
 * and a few other header files: we'll end up
 * with the error
 *  "Must use C++ with new.h"
 * from
 *  \BC5\include\new.h
 * UNLESS we make sure the include path ENDS
 * with the Borland include directories!
 */
#include "stdpccts.h"


/**************** MAIN ******************/
int main(int argc, char **argv)
{
  FILE *p = stdin;
  int _signal = NoSignal;     /* signal from exception handling returned by grammar */
  int i = 0;   /* benchmark counter */

  fprintf(stderr, "test tool for PCCTS\n\n\n");

  for (;i>=0;i--)
  {
    _signal = NoSignal;     /* signal from exception handling returned by grammar */

    if (argc >= 2)
    {
      fprintf(stderr, "reading script from file %s\n", argv[1]);

      p = fopen(argv[1], "r");
      if (!p)
      {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        exit(1);
      }
    }

#if 0
    ANTLR(script(&_signal), p);
#else
    zzbufsize = ZZLEXBUFSIZE;	
						zzenterANTLR(p);			
            {                                            
              zzBLOCK(zztasp1);                          
						  script(&_signal); /* ++zzasp;	[i_a] removed */			     
              /* [i_a] 14/june/98: fixup: kill the       
               * 'top' attribute (+AST stack corr.))     
               * or you'll get leakage! */               
	for (; zzasp<(zztasp1 + 1); zzasp++)				
						{ zzd_attr(&(zzaStack[zzasp])); }
            }             
						zzleaveANTLR(p);
#endif

    if (_signal != NoSignal)
    {
      printf("error while parsing!\n");
    }

    if (p != stdin)
    {
      fclose(p);
    }
  }

  return 0;
}
