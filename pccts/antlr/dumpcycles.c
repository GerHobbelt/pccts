#include <stdio.h>
#include <ctype.h>

#include "set.h"
#include "syn.h"
#include "hash.h"
#include "generic.h"

void 
#ifdef __USE_PROTOS
dumpcycles(void)
#else
dumpcycles()
#endif
{
  Cycle         *c;
  CacheEntry    *f;
  ListNode      *p;
  int           i=0;
  int           k;
  int           degree;

  for (k=1; k <= CLL_k; k++) {
    if (Cycles[k] == NULL) continue;

    for (p = Cycles[k]->next; p!=NULL; p=p->next) {
  	  c = (Cycle *) p->elem;
      degree=set_deg(c->cyclicDep);
	  printf_stderr_continued("Cycle %d: (degree %d) %s -->\n", i++, degree, RulePtr[c->croot]->rname);
      printf_stderr_continued("    *self*\n");
      MR_dumpRuleSet(c->cyclicDep);
      printf_stderr_continued("\n");
	  f = (CacheEntry *)
			hash_get(Fcache,Fkey(RulePtr[c->croot]->rname,'o',k));
      if (f == NULL) {
        printf_stderr_continued("    *** FOLLOW(%s) must be in cache but isn't ***\n",
                                         RulePtr[c->croot]->rname);
      }
    }
  }
}

void 
#ifdef __USE_PROTOS
dumpfostack(int k) 
#else
dumpfostack(k) 
int k;
#endif
{
  int   i=0;
  int   *pi;

  printf_stderr_continued("\n");
  if (FoStack[k] == NULL) {
    printf_stderr_continued("FoStack[%d] is null\n",k);
  }
  if (FoTOS[k] == NULL) {
    printf_stderr_continued("FoTOS[%d] is null\n",k);
  }
  if (FoTOS[k] != NULL && FoStack[k] != NULL) {
    for (pi=FoStack[k]; pi <= FoTOS[k]; pi++) {
      i++;
      printf_stderr_continued("#%d  rule %d  %s\n",i,*pi,RulePtr[*pi]->rname);
    }
  }
}
