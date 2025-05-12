
#include <stdlib.h>


#include "stdpccts.h"





/* copy attributes to structure */
void i_a_zzcr_attr(Attrib *attr, int tok, const char *t)
{
  attr->type = KEYWORD_ATTRIB;

  attr->token_id = tok;
  attr->token_descr = zztokens[tok];

  if (!t) t = "(null)";
  attr->string_value = t;
  attr->dupped_string_value = strdup(t);

  attr->zzasp = zzasp;
  attr->stack_depth = ZZA_STACKSIZE - zzasp;


#if 0
  TRACE(("create Attrib(tok[%d]: %d [%s], text: \"%s\", dupped: \"%s\")\n"
        ,attr->stack_depth
        ,attr->token_id
        ,attr->token_descr
        ,attr->string_value
        ,attr->dupped_string_value));
#endif
  return;
}


/* destruct attributes */
void i_a_zzd_attr(Attrib *attr)
{
#if 0
  TRACE(("destruct Attrib(tok[%d]: %d [%s], text: \"%s\", dupped: \"%s\")\n"
        ,attr->stack_depth
        ,attr->token_id
        ,attr->token_descr
        ,attr->string_value
        ,attr->dupped_string_value));
#endif

  /* perform necessary cleanups... */
  assert(attr != NULL);
  assert(attr->dupped_string_value != NULL);
  free((void *)attr->dupped_string_value);

  memset(attr, 0, sizeof(*attr));

  return;
}


/*
 * Must define this one or zzd_attr will barf on 'invalid Attrib stack elements'! 
 */
void i_a_zzdef0_attr(Attrib *attr)
{
  i_a_zzcr_attr(attr, BOGUS1, "zzdef0");
}

/*
 * Personal addition as attributes with malloc'ed cannot be simply assigned 
 * to each other! We need to discard old 'dst' data and 'dup' SRC data!
 */
void i_a_zzcopy_attr(Attrib *dst, const Attrib *src)
{
  i_a_zzd_attr(dst);

  *dst = *src;
  /* but redo = 'dup' malloced data! */
  dst->dupped_string_value = strdup(src->dupped_string_value);

  return;
}

