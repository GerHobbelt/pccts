/* Attrib & related definitions */

#ifndef __Attrib_Defs_H__
#define __Attrib_Defs_H__


/* ANTLR hack: we've defined an additional exception code here... */
#define UnsupportedStatement                    10
#define UnsupportedTypedef                      11
#define UnsupportedInitialization               12



typedef enum
{
  UNKNOWN_ATTRIB = 0,

  /* reserved keywords/tokens */
  KEYWORD_ATTRIB,

  /* constant values */
  INT_VALUE_ATTRIB,
  DOUBLE_VALUE_ATTRIB,
  BOOLEAN_VALUE_ATTRIB,

  /* variables for storing values */
  VARIABLE_ATTRIB,

  /* (user-)defined types */
  TYPE_ATTRIB,

  /* subroutines, library calls, etc. */
  FUNCTION_ATTRIB,

  /* labels for GOTO */
  JUMPLABEL_ATTRIB,

  /* just rules that deliver code... */
  RULE_ATTRIB,
} AttribTypeId;

typedef struct
{
  AttribTypeId type;   /* indicates which values are valid within this struct... */

  /* keyword */
  short int token_id;  /* # for token code */
  const char *token_descr;

  /* integer value */
  long int_value;

  /* floating point value */
  double float_value;

  /* string value */
  const char *string_value;
  char *dupped_string_value;

  int zzasp;
  int stack_depth;
} Attrib;




#define zzcr_attr(attr,tok,t)    i_a_zzcr_attr(attr, tok, t)
#define zzd_attr(attr)           i_a_zzd_attr(attr)
#define zzdef0(attr)             i_a_zzdef0_attr(attr)


#define zzcopy_attr(dst, src)    i_a_zzcopy_attr(dst, src)

  
void i_a_zzcr_attr(Attrib *attr, int tok, const char *t);
void i_a_zzd_attr(Attrib *attr);
void i_a_zzdef0_attr(Attrib *attr);
void i_a_zzcopy_attr(Attrib *dst, const Attrib *src);


short int get_reserved_keyword(const char *str, register int len);


/* EXCEPTION_HANDLING          n   Causes Antlr to supply exception related code. */
/* USER_ZZSYN                  y   User will override default zzsyn syntax error routine. */
/* ZZA_STACKSIZE               y   Override default number of Attr structs to allocate for the attribute stack. */
/* ZZCOL                       y   User requests scanner to maintain column information. */
/* ZZCOPY                      y   Code to override default action when lexical buffer is too small for token. */
/* ZZINTERACTIVE               n   Tells DLG to generate interactive scanner. */
/* ZZLEXBUFSIZE                y   Override size (in characters) of largest token expected. */
/* ZZSTACK_MAX_MODE            y   Overrides the default size of the mode stack. Inclusion of mode stack routines is enabled by the symbol USER_ZZMODE_STACK. */
/* zzTRACEIN                   y   When Antlr -gd switch is specified this macro is invoked at the start of each rule. Default definition prints out rule name. */
/* zzTRACEOUT                  y   Same as zzTRACEOUT, but at the exit of each rule. Default definition prints out rule name. */
/* zzfailed_pred               y   Code to print a message when a semantic predicate fails. Default version prints error message to stderr. */

/* DLG parser must process strings specially as those may easily overflow 32 character buffers! */
#define ZZLEXBUFSIZE           133

#if defined(zzTRACEIN) || defined(zzTRACEOUT)
#error zzTRACEIN/OUT already defined!
#endif

#define zzTRACEIN(r)	zzTracePrevRuleName=zzTraceCurrentRuleName;i_a_zzTraceIn(r);
#define zzTRACEOUT(r)	i_a_zzTraceOut(r);zzTraceCurrentRuleName=zzTracePrevRuleName;



#if defined(_DEBUG) || defined(DEBUG)
#define TRACE(args)         i_a_Trace args
#else
#define TRACE(args)         (void)0
#endif

void i_a_zzTraceIn(char * rule);
void i_a_zzTraceOut(char * rule);
void i_a_Trace(char *msg, ...);

#endif
