/*
debug.obj : error LNK2001: unresolved external symbol zztextLA
err.obj : error LNK2001: unresolved external symbol _zztextLA
main.obj : error LNK2001: unresolved external symbol _zztextLA
script.obj : error LNK2001: unresolved external symbol _zztextLA
debug.obj : error LNK2001: unresolved external symbol _zztokenLA
err.obj : error LNK2001: unresolved external symbol _zztokenLA
script.obj : error LNK2001: unresolved external symbol _zztokenLA
lexer.obj : error LNK2001: unresolved external symbol _zztokenLA
debug.obj : error LNK2001: unresolved external symbol _zzlabase
err.obj : error LNK2001: unresolved external symbol _zzlabase
main.obj : error LNK2001: unresolved external symbol _zzlabase
script.obj : error LNK2001: unresolved external symbol _zzlabase
err.obj : error LNK2001: unresolved external symbol _zzlap
main.obj : error LNK2001: unresolved external symbol _zzlap
script.obj : error LNK2001: unresolved external symbol _zzlap
lexer.obj : error LNK2001: unresolved external symbol _zzlap
lexer.obj : error LNK2001: unresolved external symbol _zzskip
Debug/script.exe : fatal error LNK1120: 5 unresolved externals
*/

/*
 * Plug-in replacement for DLG lexer: not DFA table based so eats much less memory.
 *
 * WARNING: hand-coded! update whenever you update the DLG grammar!
 */

/* ------------------------------------------------------------------------- */
/*                        (C) copyright Insh_Allah                           */
/* ------------------------------------------------------------------------- */
/* $Logfile:: /prj_vc/projects/scripting/lexer.c                           $ */
/* $Workfile:: lexer.c                                                     $ */
/* $Header:: /prj_vc/projects/scripting/lexer.c 3     7/02/98 12:24a I_a   $ */
/* $Date:: 7/02/98 12:24a                                                  $ */
/* $Revision:: 3                                                           $ */
/* $Modtime:: 6/14/98 5:38p                                                $ */
/* $Author:: I_a                                                           $ */
/*
*  GNU IAS is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 1, or (at your option)
*  any later version.
*
*  GNU IAS is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with GNU IAS; see the file COPYING.  If not, write to
*  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*
* $Log: /prj_vc/projects/scripting/lexer.c $
 * 
 * 3     7/02/98 12:24a I_a
 * 
 * 2     7/01/98 2:33a I_a
 * 
 * 1     6/13/98 4:37p I_a
*/
#if !defined(_NO_VSS_STRING) 
#if defined(_WIN32) && (defined(_MSC_VER) && (_MSC_VER > 800))
#pragma comment (exestr, "$Header: /prj_vc/projects/scripting/lexer.c 3     7/02/98 12:24a I_a $" )
#endif
#endif
/* $NoKeywords: $ */
/* ------------------------------------------------------------------------- */


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

LOOKAHEAD




void
#ifdef __USE_PROTOS
zzerraction(void)
#else
zzerraction()
#endif
{
	(*zzerr)("invalid token");
	zzadvance();
	/* zzskip(); */
}








zzchar_t	*zzlextext;	/* text of most recently matched token */
zzchar_t	*zzbegexpr;	/* beginning of last reg expr recogn. */
zzchar_t	*zzendexpr;	/* beginning of last reg expr recogn. */
int	zzbufsize = 0;	/* number of characters in zzlextext */          /* MR7 */
int	zzbegcol = 0;	/* column that first character of token is in*/
int	zzendcol = 0;	/* column that last character of token is in */
int	zzline = 1;	/* line current token is on */
int	zzreal_line=1;	/* line of 1st portion of token that is not skipped */
int	zzchar;		/* character to determine next state */
int	zzbufovf;	/* indicates that buffer too small for text */
int	zzcharfull = 0;
static zzchar_t	*zznextpos;/* points to next available position in zzlextext*/
static int 	zzclass;

#ifdef __USE_PROTOS
void	zzerrstd(const char *);
void	(*zzerr)(const char *)=zzerrstd;/* pointer to error reporting function */
extern int	zzerr_in(void);
#else
void	zzerrstd();
void	(*zzerr)()=zzerrstd;	/* pointer to error reporting function */
extern int	zzerr_in();
#endif

static FILE	*zzstream_in=0;
#ifdef __USE_PROTOS
static int	(*zzfunc_in)(void) = zzerr_in;
#else
static int	(*zzfunc_in)() = zzerr_in;
#endif
static zzchar_t	*zzstr_in=0;

#ifdef USER_ZZMODE_STACK
int 	         zzauto = 0;
#else
static int     zzauto = 0;
#endif

#ifdef ZZCOL
#define ZZINC (++zzendcol)
#else
#define ZZINC
#endif


#define ZZGETC_FUNC {zzchar = (*zzfunc_in)();}

#ifndef ZZCOPY
#define ZZCOPY	\
	/* Truncate matching buffer to size (not an error) */	\
	if (zznextpos < lastpos){				\
		*(zznextpos++) = zzchar;			\
	}else{							\
		zzbufovf = 1;					\
	}
#endif

/*
 * different from DLG: fetch character ALWAYS using function.
 */
int zz_getc_from_file(void)
{
  return getc(zzstream_in);
}

int zz_getc_from_str(void)
{
	if (*zzstr_in)
  {
		return *zzstr_in++;
  }
	return EOF;
}


void
#ifdef __USE_PROTOS
zzrdstream( FILE *f )
#else
zzrdstream( f )
FILE *f;
#endif
{
	/* make sure that it is really set to something, otherwise just
	   leave it be.
	*/
	if (f){
		/* make sure that there is always someplace to get input
		   before closing zzstream_in
		*/
#if 0
		if (zzstream_in && zzstream_in!=stdin) fclose( zzstream_in );
#endif
		zzline = 1;
#ifdef ZZCOL
    zzendcol = 0;
#endif
		zzstream_in = f;
		zzfunc_in = zz_getc_from_file;
		zzstr_in = 0;
		zzcharfull = 0;
	}
}

void
#ifdef __USE_PROTOS
zzrdfunc( int (*f)(void) )
#else
zzrdfunc( f )
int (*f)();
#endif
{
	/* make sure that it is really set to something, otherwise just
	   leave it be.
	*/
	if (f){
		/* make sure that there is always someplace to get input
		   before closing zzstream_in
		*/
#if 0
		if (zzstream_in && zzstream_in!=stdin) fclose( zzstream_in );
#endif
		zzline = 1;
#ifdef ZZCOL
    zzendcol = 0;
#endif
		zzstream_in = NULL;
		zzfunc_in = f;
		zzstr_in = 0;
		zzcharfull = 0;
	}
}


void
#ifdef __USE_PROTOS
zzrdstr( zzchar_t *s )
#else
zzrdstr( s )
zzchar_t *s;
#endif
{
	/* make sure that it is really set to something, otherwise just
	   leave it be.
	*/
	if (s){
		/* make sure that there is always someplace to get input
		   before closing zzstream_in
		*/
#if 0
		if (zzstream_in && zzstream_in!=stdin) fclose( zzstream_in );
#endif
		zzline = 1;
#ifdef ZZCOL
    zzendcol = 0;
#endif
		zzstream_in = NULL;
		zzfunc_in = zz_getc_from_str;
		zzstr_in = s;
		zzcharfull = 0;
	}
}


void
#ifdef __USE_PROTOS
zzclose_stream(void)
#else
zzclose_stream()
#endif
{
#if 0
	fclose( zzstream_in );
	zzstream_in = NULL;
	zzfunc_in = NULL;
#endif
}

/* saves dlg state, but not what feeds dlg (such as file position) */
void
#ifdef __USE_PROTOS
zzsave_dlg_state(struct zzdlg_state *state)
#else
zzsave_dlg_state(state)
struct zzdlg_state *state;
#endif
{
	state->stream = zzstream_in;
	state->func_ptr = zzfunc_in;
	state->str = zzstr_in;
	state->auto_num = zzauto;
	state->add_erase = 0; 
	state->lookc = zzchar;
	state->char_full = zzcharfull;
	state->begcol = zzbegcol;
	state->endcol = zzendcol;
	state->line = zzline;
	state->lextext = zzlextext;
	state->begexpr = zzbegexpr;
	state->endexpr = zzendexpr;
	state->bufsize = zzbufsize;
	state->bufovf = zzbufovf;
	state->nextpos = zznextpos;
	state->class_num = zzclass;
}

void
#ifdef __USE_PROTOS
zzrestore_dlg_state(struct zzdlg_state *state)
#else
zzrestore_dlg_state(state)
struct zzdlg_state *state;
#endif
{
	zzstream_in = state->stream;
	zzfunc_in = state->func_ptr;
	zzstr_in = state->str;
	zzauto = state->auto_num;
	/* zzadd_erase = state->add_erase; */
	zzchar = state->lookc;
	zzcharfull = state->char_full;
	zzbegcol = state->begcol;
	zzendcol = state->endcol;
	zzline = state->line;
	zzlextext = state->lextext;
	zzbegexpr = state->begexpr;
	zzendexpr = state->endexpr;
	zzbufsize = state->bufsize;
	zzbufovf = state->bufovf;
	zznextpos = state->nextpos;
	zzclass = state->class_num;
}

void
#ifdef __USE_PROTOS
zzmode( int m )
#else
zzmode( m )
int m;
#endif
{
	/* points to base of dfa table */
  zzauto = m;
  zzclass = m; /* differs from DLG! */
}


static void fetch_next_char(void)
{
	register zzchar_t *lastpos;

	lastpos = &zzlextext[zzbufsize-1];

  ZZGETC_FUNC;
  zzcharfull = 1; 
  ZZINC;
  ZZCOPY;
}

static void discard_token_text(void)
{
	zzreal_line = zzline;
	zzbufovf = 0;
	zznextpos = zzlextext;
	zzbegcol = zzendcol+1;
	zzbegexpr = zznextpos;
}

/*
 * We ALWAYS act as an 'interactive' lexer... 
 */
void
#ifdef __USE_PROTOS
zzgettok(void)
#else
zzgettok()
#endif
{
#ifdef ZZINTERACTIVE
#endif

  discard_token_text();

  /* interactive version of automaton */
	/* if there is something in zzchar, process it */
	if (!zzcharfull)
  {
  	fetch_next_char();
  }
  else
  {
	  register zzchar_t *lastpos;

	  lastpos = &zzlextext[zzbufsize-1];

    ZZCOPY;
  }
  	
  /* decode token */
  assert(zzcharfull != 0);
  for (;;)
  {
	  if (!zzcharfull)
    {
  	  fetch_next_char();
    }
    zzcharfull = 0;
    switch (zzclass)
    {
    case START:
      switch (zzchar)
      {
      case '}':
        NLA = END;
        break;

      case '{':
        NLA = BEGIN;
        break;

      case '.':
        /* '.', '...' */
        fetch_next_char();
        if (zzchar == '.')
        {
          fetch_next_char();
          if (zzchar == '.')
          {
            zzcharfull = 0;
            NLA = TRIPLE_DOT;
            break;
          }
          NLA = UNKNOWN_CHAR;
          break;
        }
        NLA = DOT;
        break;

      case '(':
        NLA = LPARENS;
        break;

      case ')':
        NLA = RPARENS;
        break;

      case '[':
        NLA = LBRACKET;
        break;

      case ']':
        NLA = RBRACKET;
        break;

      case ',':
        NLA = COMMA;
        break;

      case ';':
        NLA = SEMICOLON;
        break;

      case '&':
        /* '&&', '&&=', '&=', '&' */
        fetch_next_char();
        switch (zzchar)
        {
        case '&':
          fetch_next_char();
          if (zzchar == '=')
          {
            zzcharfull = 0;
            NLA = ASSIGN_BOOLEAN_AND;
            break;
          }
          NLA = BOOLEAN_AND;
          break;

        case '=':
          zzcharfull = 0;
          NLA = ASSIGN_BITWISE_AND;
          break;

        default:
          NLA = BITWISE_AND;
          break;
        }
        break;

      case '|':
        /* '||', '||=', '|=', '|' */
        fetch_next_char();
        switch (zzchar)
        {
        case '|':
          fetch_next_char();
          if (zzchar == '=')
          {
            zzcharfull = 0;
            NLA = ASSIGN_BOOLEAN_OR;
            break;
          }
          NLA = BOOLEAN_OR;
          break;

        case '=':
          zzcharfull = 0;
          NLA = ASSIGN_BITWISE_OR;
          break;

        default:
          NLA = BITWISE_OR;
          break;
        }
        break;

      case '^':
        /* '^=', '^' */
        fetch_next_char();
        if (zzchar == '=')
        {
          zzcharfull = 0;
          NLA = ASSIGN_BITWISE_XOR;
          break;
        }
        NLA = BITWISE_XOR;
        break;

      case ':':
        /* ':=', ':' */
        fetch_next_char();
        if (zzchar == '=')
        {
          zzcharfull = 0;
          NLA = ASSIGN;
          break;
        }
        NLA = COLON;
        break;

      case '+':
        /* '+=', '+' */
        fetch_next_char();
        if (zzchar == '=')
        {
          zzcharfull = 0;
          NLA = ASSIGN_PLUS;
          break;
        }
        NLA = PLUS;
        break;

      case '-':
        /* '-=', '-' */
        fetch_next_char();
        if (zzchar == '=')
        {
          zzcharfull = 0;
          NLA = ASSIGN_MINUS;
          break;
        }
        NLA = MINUS;
        break;

      case '!':
        /* '!=', '!' */
        fetch_next_char();
        if (zzchar == '=')
        {
          zzcharfull = 0;
          NLA = NE;
          break;
        }
        NLA = BOOLEAN_NOT;
        break;

      case '~':
        assert(zzcharfull == 0);
        NLA = BITWISE_NOT;
        break;

      case '/':
        /* '/=', '/', '/\*', '//' */
        fetch_next_char();
        switch (zzchar)
        {
        case '=':
          zzcharfull = 0;
          NLA = ASSIGN_DIVIDE;
          break;

        case '*':
          zzcharfull = 0;
          zzmode(COMMENT);
          continue;

        case '/':
          zzcharfull = 0;
          zzmode(CPPCOMMENT);
          continue;

        default:
          NLA = DIVIDE;
          break;
        }
        break;

      case '#':
        zzcharfull = 0;
        zzmode(CPPCOMMENT);
        continue;

      case '%':
        /* '%=', '%' */
        fetch_next_char();
        if (zzchar == '=')
        {
          zzcharfull = 0;
          NLA = ASSIGN_MODULO;
          break;
        }
        NLA = MODULO;
        break;

      case '*':
        /* '**', '**=', '*=', '*' */
        fetch_next_char();
        switch (zzchar)
        {
        case '*':
          fetch_next_char();
          if (zzchar == '=')
          {
            zzcharfull = 0;
            NLA = ASSIGN_POWER;
            break;
          }
          NLA = POWER;
          break;

        case '=':
          zzcharfull = 0;
          NLA = ASSIGN_MULTIPLY;
          break;

        default:
          NLA = MULTIPLY;
          break;
        }
        break;

      case '<':
        /* '<<', '<<=', '<=', '<' */
        fetch_next_char();
        switch (zzchar)
        {
        case '<':
          fetch_next_char();
          if (zzchar == '=')
          {
            zzcharfull = 0;
            NLA = ASSIGN_LSHIFT;
            break;
          }
          NLA = LSHIFT;
          break;

        case '=':
          zzcharfull = 0;
          NLA = LE;
          break;

        default:
          NLA = LT;
          break;
        }
        break;

      case '>':
        /* '>>', '>>=', '>=', '>' */
        fetch_next_char();
        switch (zzchar)
        {
        case '>':
          fetch_next_char();
          if (zzchar == '=')
          {
            zzcharfull = 0;
            NLA = ASSIGN_RSHIFT;
            break;
          }
          NLA = RSHIFT;
          break;

        case '=':
          zzcharfull = 0;
          NLA = GE;
          break;

        default:
          NLA = GT;
          break;
        }
        break;

      case '=':
        /* '==', '=' */
        fetch_next_char();
        if (zzchar == '=')
        {
          zzcharfull = 0;
          NLA = EQ;
          break;
        }
        NLA = ASSIGN;
        break;

      case '\"':
        zzcharfull = 0;
        /* discard_token_text(); */
        zzmode(STRING_VALUES);
        continue;

      case '0':
        /* octal or HEX */
        fetch_next_char();
        if (toupper(zzchar) == 'X')
        {
          fetch_next_char();
          if (!isxdigit(zzchar))
          {
            NLA = UNKNOWN_CHAR; /* incomplete hexadecimal number: just header '0x' */
            break;
          }
          while (isxdigit(zzchar))
          {
            fetch_next_char();
          }
        }
        else
        {
          while (isdigit(zzchar) 
                 && (zzchar != '8') 
                 && (zzchar != '9'))
          {
            fetch_next_char();
          }
        }
        NLA = INT_VALUE;
        break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        do
        {
          fetch_next_char();
        } while (isdigit(zzchar));

        NLA = INT_VALUE;
        break;

      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'r':
      case 's':
      case 't':
      case 'u':
      case 'v':
      case 'w':
      case 'x':
      case 'y':
      case 'z':
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      case '_':
      case '$':
        /* identifier, type of reserved keyword */
        do
        {
          fetch_next_char();
        } while (isalnum(zzchar)
                 || (zzchar == '_')
                 || (zzchar == '$'));

        NLA = VARIABLE;
        /*
         * check if this is a reserved word: return
         * different token for that!
         */
        {
          /* we ASSUME no keywords will be longer than 31 characters! */
          char keyword[32]; 
          size_t keyword_len = zznextpos - zzbegexpr - 1;

          if (keyword_len < sizeof(keyword)
              && keyword_len > 1)
          {
            short int res;
            
            strncpy(keyword, zzbegexpr, keyword_len);
            keyword[keyword_len] = 0;

            /* convert to all lowercase for hash-table routine */
#if 0
            strlwr(keyword + 1);
#else
            {
              char *p = keyword + 1;

              while (*p)
              {
                *p++ = tolower(*p);
              }
            }
#endif
            keyword[0] = toupper(keyword[0]);

            res = get_reserved_keyword(keyword, keyword_len);
            if (res)
            {
              NLA = res;
            }
          }
        }
        break;

      case EOF:
        discard_token_text();
        zzcharfull = 0;
        NLA = SCRIPT_EOF;
        break;

      case '\n':
        discard_token_text();
        zzcharfull = 0;
        zzline++;
#ifdef ZZCOL
        zzendcol = 0;
#endif
        continue;

      case ' ':
      case '\t':
      case '\r':
        discard_token_text();
        zzcharfull = 0;
        continue;

      default:
        zzcharfull = 0;
        NLA = UNKNOWN_CHAR;
        break;
      }
      break;

    /* STRING decoding! */
    case STRING_VALUES:
      switch (zzchar)
      {
      case '\\':
        /* quoted characters */
        fetch_next_char();
        switch (zzchar)
        {
        case 'a':
        case 'b':
        case 'f':
        case 'r':
        case 'n':
        case 't':
        case 'v':
        case '\'':
        case '\"':
          zzcharfull = 0;
          continue;

        case '0':
          {
            int value_base;
            int val;

            /* octal or HEX */
            fetch_next_char();
            if (toupper(zzchar) == 'X')
            {
              fetch_next_char();
              value_base = 16;
            }
            else
            {
              value_base = 8;
            }
            val = 0;

            if (0)
            {
              /* fall through! */
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
              value_base = 10;
              val = zzchar - '0';
              fetch_next_char();
            }

            while (isdigit(zzchar))
            {
              val *= value_base;
              val += zzchar - '0';
              fetch_next_char();
            }

            /* fully decoded value in val: write as replacement character into string! */
            (void)0;
          }
          continue;

        case '\r':
          fetch_next_char();
          if (zzchar != '\n')
          {
            /* don't accept loose '\r' in our string! */
            NLA = ERROR_ITS_TOKEN;
            zzmode(START);
            break;
          }
          /* fall through! */

        case '\n':
          zzcharfull = 0;
          zzline++;
#ifdef ZZCOL
          zzendcol = 0;
#endif

          /* string continued on next line: remove '\n' and '\r' (if existant) and '\\' */
          (void)0;

          continue;

        default:
          zzcharfull = 0;
          continue;
        }
        break;

      case '\r':
        fetch_next_char();
        if (zzchar == '\n')
        {
          /* fall through! */

      case '\n':
          zzcharfull = 0;
          zzline++;
#ifdef ZZCOL
          zzendcol = 0;
#endif
        }

        NLA = ERROR_ITS_TOKEN;
        zzmode(START);
        break;

      case '\"':
        zzcharfull = 0;
        NLA = STRING_VALUE;
        zzmode(START);
        break;

      case EOF:
        zzcharfull = 0;
        NLA = ERROR_ITS_EOF_TOKEN;
        zzmode(START);
        break;

      default:
        zzcharfull = 0;
        continue;
      }
      break;

    case COMMENT:
      switch (zzchar)
      {
      case '\n':
        zzline++;
#ifdef ZZCOL
        zzendcol = 0;
#endif
        assert(zzcharfull == 0);
        continue;

      case '*':
        fetch_next_char();
        if (zzchar == '/')
        {
          zzmode(START);
          zzcharfull = 0;
          discard_token_text();
          continue;
        }
        continue;

      case EOF:
        zzcharfull = 0;
        NLA = ERROR_ITC_TOKEN;
        zzmode(START);
        break;

      default:
        assert(zzcharfull == 0);
        continue;
      }
      break;

    case CPPCOMMENT:
      switch (zzchar)
      {
      case '\n':
        zzline++;
#ifdef ZZCOL
        zzendcol = 0;
#endif
        /* fall through */

      case EOF:
        zzmode(START);
        zzcharfull = 0;
        break;

      default:
        zzcharfull = 0;
        continue;
      }
      discard_token_text();
      continue;

    default:
      assert(0);
      break;
    }
    break;
  }

  /* we've a valid token written to NLA by now! */

  /* fix 'token string' */
  if (zzcharfull)
    zznextpos--;
  zzendexpr = zznextpos - 1;
  *zznextpos = 0;

  return;
}




void
#ifdef __USE_PROTOS
zzadvance(void)
#else
zzadvance()
#endif
{
	if (zzfunc_in) 
  { 
    ZZGETC_FUNC; 
    zzcharfull = 1; 
    ZZINC;
  }
	else
  {
		zzerr_in();
	}
}

void
#ifdef __USE_PROTOS
zzerrstd(const char *s)
#else
zzerrstd(s)
char *s;
#endif
{
        zzLexErrCount++;                /* MR11 */
        fprintf(stderr,
                "%s near line %d (text was '%s')\n",
                ((s == NULL) ? "Lexical error" : s),
                zzline,zzlextext);
}

int
#ifdef __USE_PROTOS
zzerr_in(void)
#else
zzerr_in()
#endif
{
	fprintf(stderr,"No input stream, function, or string\n");
	/* return eof to get out gracefully */
	return EOF;
}

