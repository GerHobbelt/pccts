
#include <stdarg.h>

#include "stdpccts.h"


/**********************************************************
 *                    Trace Routines                      *
 **********************************************************/
#ifdef __USE_PROTOS
void i_a_zzTraceIn(char * rule)
#else
void i_a_zzTraceIn(rule)
  char  *rule;
#endif
{
#ifdef zzTRACE_RULES

  int           doIt=0;

  zzTraceDepth++;
  zzTraceCurrentRuleName=rule;

  if (zzTraceOptionValue <= 0) 
  {
    doIt=0;
#ifdef ZZCAN_GUESS
  }
  else if (zzguessing && zzTraceGuessOptionValue <= 0) 
  {
    doIt=0;
#endif
  }
  else 
  {
    doIt=1;
  }

  if (doIt) 
  {
#if 0
    fprintf(stdout,"enter rule %s {\"%s\"} depth %d",
            rule,
            LA(1)==1 ? "@" : LATEXT(1),
            zzTraceDepth);
#ifdef ZZCAN_GUESS
    if (zzguessing)
      fprintf(stdout," guessing");
#endif
    fprintf(stdout,"\n");
#endif
  }
#endif
  return;
}

#ifdef __USE_PROTOS
void i_a_zzTraceOut(char * rule)
#else
void i_a_zzTraceOut(rule)
  char  *rule;
#endif
{
#ifdef zzTRACE_RULES
  int       doIt=0;

  zzTraceDepth--;

  if (zzTraceOptionValue <= 0) 
  {
    doIt=0;
#ifdef ZZCAN_GUESS
  }
  else if (zzguessing && zzTraceGuessOptionValue <= 0) 
  {
    doIt=0;
#endif
  } 
  else 
  {
    doIt=1;
  }

  if (doIt) 
  {
#if 0
    fprintf(stdout,"exit rule %s {\"%s\"} depth %d",
            rule,
            LA(1)==1 ? "@" : LATEXT(1),
            zzTraceDepth+1);
#ifdef ZZCAN_GUESS
    if (zzguessing)
      fprintf(stdout," guessing");
#endif
    fprintf(stdout,"\n");
#endif
  }
#endif
}


void i_a_Trace(char *msg, ...)
{
  va_list lst;

  va_start(lst, msg);

#if 01
  fprintf(stdout, "TRACE: ");
  vfprintf(stdout, msg, lst);
  if (msg != NULL
      && strlen(msg) > 0
      && msg[strlen(msg) - 1] != '\n')
    fprintf(stdout, "\n");
#endif

  va_end(lst);
  return;
}



#ifdef USER_ZZSYN

#undef zzsyn

/* copy of standard error reporting function */
void
#ifdef __USE_PROTOS
zzsyn(char *text, int tok, char *egroup, SetWordType *eset, int etok, int k, char *bad_text)
#else
zzsyn(text, tok, egroup, eset, etok, k, bad_text)
char *text, *egroup, *bad_text;
int tok;
int etok;
int k;
SetWordType *eset;
#endif
{
  zzSyntaxErrCount++;                             /* MR11 */
	fprintf(stderr, "line %d: syntax error at \"%s\"", zzline, (tok==zzEOF_TOKEN)?"EOF":bad_text);
	if ( !etok && !eset ) {fprintf(stderr, "\n"); return;}
	if ( k==1 ) fprintf(stderr, " missing");
	else
	{
		fprintf(stderr, "; \"%s\" not", bad_text);
		if ( zzset_deg(eset)>1 ) fprintf(stderr, " in");
	}
	if ( zzset_deg(eset)>0 ) zzedecode(eset);
	else fprintf(stderr, " %s", zztokens[etok]);
	if ( strlen(egroup) > 0 ) fprintf(stderr, " in %s", egroup);
	fprintf(stderr, "\n");
}
#endif
