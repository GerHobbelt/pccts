/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	Copyright (c) 1995 John D. Mitchell -- All Rights Reserved

PROJECT:	PCCTS
MODULE:		Contrib
FILE:		cstr.g

AUTHOR:		John D. Mitchell, Jun 13, 1995
		johnm@alumni.EECS.Berkeley.EDU

LICENSE:
	Permission to use, copy, modify, and distribute this software
	and its documentation for any purpose, without fee, and
	without written agreement is hereby granted, provided that the
	above copyright notice and this license agreement appears in
	all copies of this software. 

	IN NO EVENT SHALL JOHN D. MITCHELL, ("THE AUTHOR"), BE LIABLE
	TO ANY PARTY FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
	CONSEQUENTIAL DAMAGES SUFFERED BY LICENSEE AS A RESULT OF
	USING, MODIFYING, OR DISTRIBUTING THIS SOFTWARE, ITS
	DOCUMENTATION, OR ITS DERIVATIVES EVEN IF THE AUTHOR HAS BEEN
	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	THE AUTHOR MAKES NO REPRESENTATIONS ABOUT THE SUTIABILITY OF
	THE SOFTWARE AND SPECIFICALLY DISCLAIMS ANY WARRANTIES,
	INCLUDING, BUT NOT LIMITED TO, EITHER EXPRESS OR IMPLIED 
	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
	PURPOSE, OR NON-INFRINGEMENT.  THE SOFTWARE PROVIDED HEREUNDER
	IS ON AN "AS IS" BASIS, AND THE AUTHOR HAS NO OBLIGATION TO
	PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
	MODIFICATIONS.

REVISION HISTORY:
	Name	Date		Description
	----	----		-----------
	JDM	95.06.13	Initial version.
	JDM	95.06.14	Added support for C style comments.
	JDM	95.06.14	Released v1.0a1
	THM	95.06.15	Changed printf statements
	JDM	95.06.15	Added adjacent string literal concatenation.
	JDM	95.06.16	Released v1.0a2.
	JDM	95.06.19	Incorporated THM's error handling changes
				into baseline.  Excellent!
	JDM	95.06.19	Released v1.0a3.
	JDM	95.06.20	Cleanup pass.
	JDM	95.06.21	Released v1.0.
	JDM	95.07.06	Added unexpected EOF support.
	JDM	95.07.11	Added full C++ style comment support.
	JDM	95.07.12	Added junk/catch-all handling.
	JDM	95.07.15	Tcl command interface.
	JDM	95.07.19	Parsing statistics.

DESCRIPTION:
	This file parses the ISO/ANSI Standard C characters, strings,
	and comments.  It deals robustly with malformed versions of those
	constructs as well as random garbage input.

	As an added bonus, this package has been extended to support it's
	use as a 'parser server' by being incorporated into a Tcl/Tk
	application shell which contains Tcl-DP, a distributed programming
	package.  A parser daemon can be built (see the makefile) which
	will enhance the normal Tcl/Tk/Tcl-DP shell with a command called
	'parse' will can be passed a string.  The 'parse' command will
	parse the given string and return it's output as the result of
	the command.  A client application written in Tcl/Tk/Tcl-DP is
	also included which sucks in the specified file and remotely
	invokes the parser passing on the contents of that file and
	displaying the result locally.

	Note clearly that this sample grammar does *NOT* deal with anything
	else.  Including things like trigraphs (since they are a function
	of the 'preprocessor' phases of translation).  Nor does this
	grammar deal with multi-byte characters nor strings containing
	multi-byte characters [these constructs are "exercises for the
	reader" as it were :-)]. 

	Also note that this grammar is written assuming you're using
	ANTLR's C mode output (*not* C++).

	Please refer to the ISO/ANSI C Language Standard if you believe
	this grammar to be in error.  Please cite chapter and verse in any
	correspondence to the author to back up your claim.   Arguments of
	the form '...but XX brand compiler accepts [pet shme here]...'
	shall be summarily disregarded. 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		Include Files
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#header
<<
#include <stddef.h>			/* Standard C/C++.	*/
#include <stdlib.h>

/*
 * Use bigger string buffers.
 *
 * Note that this is a horrible, fixed size hack.  Any code that this
 * gets sucked into that has aspirations of being 'production quality'
 * had better use something better.  You have been warned.
 */
#define	D_TextSize	(250)
#include <charbuf.h>
>>

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		Tokens
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*
 * Eat whitespace.
 */
#token			"[\t\ ]+"	<< zzskip (); >>
#token			"[\r\n]"	<< zzskip (); zzline++; >>


/*
 * EOF for START lexical class.
 */
#token	EndOfFile	"@"


/*
 * Start of C-style comments.  Switch to LC_COMMENT lexical class and
 * continue... 
 */
#token	"/\*"		<< zzskip (); zzmode (LC_COMMENT); >>

#lexclass	LC_COMMENT

/*
 * End of the comment so switch back into STARTing lexical class.
 *
 * Note that nothing will be 'returned' as the token ID because
 * we're 'skipping' over the input.
 *
 * Note that this method of dealing with comments was lifted from
 * Tom Moog's PCCTS Notes for New Users of PCCTS.
 *
 * Note the trick of using "@@" to fool DLG.  This is discussed
 * in the PCCTS Notes v2.02 as item #33.
 */
#token			"\*/"		<< zzskip (); zzmode (START);  >>
#token			"[\r\n]"	<< zzskip (); zzline++; >>
#token	BAD_EOF		"@@"		<< zzmode (START); >>
#token			"~[]"		<< zzskip (); >>

/*
 * Switch back to the starting lexical class.
 */
#lexclass	START


/*
 * Note that if you want C++ style you can uncomment the following token
 * definition.
 *
 * Note that a simplistic usage of something like:
 *	#token	"//~[\n]*\n"	<< zzskip (); zzline++; >>
 * may seem correct but that will not handle the (nasty) case where
 * the end of file is before the end of the line.
 *
 * Note:  In the following code I declare (by implementors fiat :-) that 
 * this is an error and therefore return an error indicator rather than
 * just accepting it as another comment terminator.
 *
 *
 * Start of C++-style comments.  Switch to LC_CPPCOMMENT lexical class and
 * continue... 
 */
#token	DBLSLASH	"//"	<< zzmore (); zzmode (LC_CPPCOMMENT); >>

#lexclass	LC_CPPCOMMENT

/*
 * End of the comment so switch back into STARTing lexical class.
 *
 * Note that CPP_COMMENT will be 'returned' as the token ID.  This allows
 * us to catch this heinous (non-standard) usage of C++ style comments
 * within C code but we can suppress the error (or make it a warning or
 * just ignore it) in the parser rather than having the lexer spew.
 *
 * Note that in a more forgiving world/translator I'd suggest that you
 * treat the end of file case as just another valid way to terminate the
 * comment rather than raising an error but hey, do what you want. :-)
 *
 * Note that we just suck up a single character in the catch all case
 * at the bottom.
 */
#token	CPP_COMMENT	"[\r\n]"	<< zzline++; zzmode (START); >>
#token	BAD_EOF		"@@"		<< zzmode (START); >>
#token			"~[]"		<< zzmore (); >>

/*
 * Switch back to the starting lexical class.
 */
#lexclass	START


/*
 * Start of string literals.  Switch to LC_STRING lexical class and
 * continue...
 */
#token	DBLQUOTE	"\""	<< zzmore (); zzmode (LC_STRING); >>

#lexclass	LC_STRING

/*
 * End of the string literal so switch back into STARTing lexical class.
 *
 * Note that STRING_CONST will be the 'returned' token ID and that
 * the token *will* contain the delimiting quotes.
 */
#token	STRING_CONST	"\""	<< zzmode (START); >>

/* Handle the various character escape sequences.	*/
#token	"\\\""		<< zzreplchar ('\"'); zzmore (); >>
#token	"\\'"		<< zzreplchar ('\''); zzmore (); >>
#token	"\\?"		<< zzreplchar ('\?'); zzmore (); >>
#token	"\\\\"		<< zzreplchar ('\\'); zzmore (); >>
#token	"\\a"		<< zzreplchar ('\a'); zzmore (); >>
#token	"\\b"		<< zzreplchar ('\b'); zzmore (); >>
#token	"\\f"		<< zzreplchar ('\f'); zzmore (); >>
#token	"\\n"		<< zzreplchar ('\n'); zzmore (); >>
#token	"\\r"		<< zzreplchar ('\r'); zzmore (); >>
#token	"\\t"		<< zzreplchar ('\t'); zzmore (); >>
#token	"\\v"		<< zzreplchar ('\v'); zzmore (); >>

/*
 * Handle the various numeric escape sequences.
 *
 * Note carefully that these numeric escape *sequences* are *not* of the 
 * same form as the C language numeric *constants*.
 *
 * There is no such thing as a binary numeric escape sequence.
 * Octal escape sequences are either 1, 2, or 3 octal digits exactly.
 * There is no such thing as a decimal escape sequence.
 * Hexadecimal escape sequences are begun with a leading \x and continue
 * until a non-hexadecimal character is found.
 */
#token	"\\[0-7][0-7][0-7]"	<< zzreplchar ((char)
					strtol (zzbegexpr+1, NULL, 8));
				   zzmore (); >>
#token	"\\[0-7][0-7]"		<< zzreplchar ((char)
					strtol (zzbegexpr+1, NULL, 8));
				   zzmore (); >>
#token	"\\[0-7]"		<< zzreplchar ((char)
					strtol (zzbegexpr+1, NULL, 8));
				   zzmore (); >>

#token	"\\x[0-9a-fA-F]+"	<< zzreplchar ((char)
					strtol (zzbegexpr+2, NULL, 16));
				    zzmore (); >>

/*
 * Match anything that doesn't get matched above and is illegal and switch
 * into a special 'error' token mode so that the grammar can deal with the
 * error and perform any cleanup, error handling, ignore it, etc.
 *
 * First, can't have imbedded raw newlines.  A strict reading of the
 * language standard just nukes the newline and does *not* restrict the
 * carriage return.  Hence, the dichtomy below.
 */
#token	"\r"		<< zzline++; zzmore (); >>
#token	"\n"		<< zzline++; zzmore ();
			   zzmode (LC_BAD_STRING_CONST); >>

/* Catch invalid hexadecimal escapes.	*/
#token	"\\x"		<< zzmore (); zzmode (LC_BAD_STRING_CONST); >>

/* Catch the rest of the invalid escape sequences.	*/
#token	"\\"		<< zzmore (); zzmode (LC_BAD_STRING_CONST); >>

/* Catch unexpected End-of-File...	*/
#token	BAD_EOF	"@@"	<< zzmode (START); >>

/*
 * Suck up everything else.
 * 
 * Note that the items which stop the input consumption are the
 * prefixes of all of the REs in this lexclass.  This is because we
 * want to suck up as much as possible in this nice, fast lexer
 * construct but don't want to overrun any 'important' tokens.
 */
#token	"~[\"\\\n\r]+"		<< zzmore (); >>


/*
 * Start of LC_BAD_STRING_CONST.
 *
 * Try to eat up the badly formed string literal so we can continue
 * gracefully.
 */
#lexclass	LC_BAD_STRING_CONST

#token	BAD_STRING_CONST	"\""		<< zzmode (START); >>
#token				"[\r\n]"	<< zzline++; zzmore (); >>
#token	BAD_EOF			"@@"		<< zzmode (START); >>
#token				"~[\r\n\"]+"	<< zzmore (); >>

/*
 * Switch back to the starting lexical class.
 */
#lexclass	START


/*
 * Start of character constants.  Switch to LC_CHARS lexical class and
 * continue... 
 */
#token	SGLQUOTE	"'"	<< zzmore (); zzmode (LC_CHARS); >>

#lexclass	LC_CHARS 

/*
 * Note clearly that character constants may *not* be empty in C (even
 * though C strings may).  So you can *not* have the naive:
 *
 * 	#token CHARACTER "'"	<< zzmode (START); >>
 *
 * to end the lexical class.
 *
 * The trick to end this character constant is to switch to a secondary
 * 'helper' lexical class after finding any valid character definition
 * which only looks for the ending tick (').
 */

/*
 * Handle the various character escape sequences.
 *
 * Note clearly the switch into the helper lexical class to force
 * the recognition of only a single character.
 */
#token	"\\\""		<< zzreplchar ('\"');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\'"		<< zzreplchar ('\'');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\?"		<< zzreplchar ('\?');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\\\"		<< zzreplchar ('\\');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\a"		<< zzreplchar ('\a');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\b"		<< zzreplchar ('\b');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\f"		<< zzreplchar ('\f');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\n"		<< zzreplchar ('\n');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\r"		<< zzreplchar ('\r');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\t"		<< zzreplchar ('\t');
			   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\v"		<< zzreplchar ('\v');
			   zzmore (); zzmode (LC_CHAR_DONE); >>

/*
 * Handle the various numeric escape sequences.
 *
 * Note carefully that these numeric escape *sequences* are *not* of the 
 * same form as the C language numeric *constants*.
 *
 * There is no such thing as a binary numeric escape sequence.
 * Octal escape sequences are either 1, 2, or 3 octal digits exactly.
 * There is no such thing as a decimal escape sequence.
 * Hexadecimal escape sequences are begun with a leading \x and continue
 * until a non-hexadecimal character is found.
 */
#token	"\\[0-7][0-7][0-7]"	<< zzreplchar ((char)
					strtol (zzbegexpr+1, NULL, 8));
				   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\[0-7][0-7]"		<< zzreplchar ((char) 
					strtol (zzbegexpr+1, NULL, 8));
				   zzmore (); zzmode (LC_CHAR_DONE); >>
#token	"\\[0-7]"		<< zzreplchar ((char) 
					strtol (zzbegexpr+1, NULL, 8));
				   zzmore (); zzmode (LC_CHAR_DONE); >>

#token	"\\x[0-9a-fA-F]+"	<< zzreplchar ((char)
					strtol (zzbegexpr+2, NULL, 16));
				   zzmore (); zzmode (LC_CHAR_DONE); >>

/*
 * Match stuff that doesn't get matched above but which is illegal and
 * switch into a special 'error' token mode so that the grammar can deal
 * with the error and perform any cleanup, error handling, ignore it, etc.
 *
 * First, can't have imbedded raw newlines.  A strict reading of the
 * language standard just nukes the newline and does *not* restrict the
 * carriage return.  Hence, the dichtomy below.
 */
#token	"\r"		<< zzline++; zzmore ();
			   zzmode (LC_CHAR_DONE); >>
#token	"\n"		<< zzline++; zzmore ();
			   zzmode (LC_BAD_CHAR_CONST); >>

/* Can't have raw single quotes in character constants.	*/
#token	"\'"		<< zzmore (); zzmode (LC_BAD_CHAR_CONST); >>

/* Catch invalid hexadecimal escapes.	*/
#token	"\\x"		<< zzmore (); zzmode (LC_BAD_CHAR_CONST); >>

/* Catch all other invalid escape sequences.	*/
#token	"\\"		<< zzmore (); zzmode (LC_BAD_CHAR_CONST); >>

/* Catch unexpected End-of-File...	*/
#token	BAD_EOF	"@@"	<< zzmode (START); >>

/*
 * Suck up everything else.
 *
 * Note how we're *not* using the trick that we used in the
 * LC_STRING class above.  This is because we're *only* sucking
 * up a single character and all of the 'interesting' ones have
 * already been matched above.
 */
#token	"~[]"		<< zzmore (); zzmode (LC_CHAR_DONE); >>


/*
 * Start of LC_BAD_CHAR_CONST.
 *
 * Try to eat up the badly formed character literal so we can continue
 * or exit gracefully.
 *
 * The plan here is to eat stuff until we find the (hopefully) intended
 * terminating single quote.  To keep from eating up the input we'll
 * stop if we reach the end of the current input line.
 */
#lexclass	LC_BAD_CHAR_CONST

#token	BAD_CHAR_CONST	"\'"		<< zzmode (START); >>
#token			"[\r\n]"	<< zzline++; zzmode (START);
					   NLA = BAD_CHAR_CONST; >>
#token	BAD_EOF		"@@"		<< zzmode (START); >>
#token			"~[\r\n\']+"	<< zzmore (); >>

/*
 * Start of LC_CHAR_DONE.
 *
 * Try to end the character literal.
 *
 * The plan here is to look for the ending single quote.  If we
 * find anything else then return an error token instead.
 */

#lexclass LC_CHAR_DONE

#token	CHAR_CONST	"\'"		<< zzmode (START); >>
#token	BAD_CHAR_CONST	"[\r\n]"	<< zzline++; zzmode (START); >>
#token	BAD_EOF		"@@"		<< zzmode (START); >>
#token			"~[]"		<< zzmore ();
					   zzmode (LC_BAD_CHAR_CONST); >>

/*
 * Switch back to the starting lexical class.
 */
#lexclass	START


/*
 * Suck up everything that is *not* already matched so that all
 * error handling is handled in the parser rather than in the lexer.
 * This makes for (potentially) much nicer error messages.  This is
 * of crucial importance (IMO :-) for folks imbedding their parsers 
 * within other tools, applications, etc.
 *
 * Note that I have *not* placed this catch all rule at the end of
 * the grammar file (as is so strongly recommended in the Notes for
 * Newbies) because I wish to strongly advocate a corollary which
 * says:  All tokens should be explicitly specified.
 *
 * Also note that I have placed an empty/dummy action on the token
 * so that the global action which contains 'main' isn't attaced
 * to this rule instead.
 */
#token	JUNK	"~[]"	<< /* No action.	*/ >>


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		Rules
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

<<
/*
 * Parser Statistics
 */
static int	numGoodChars	= 0;
static int	numBadChars	= 0;
static int	numGoodStrings	= 0;
static int	numBadStrings	= 0;
static int	numCPPComments	= 0;
static int	numJunk		= 0;

static int	badEOF		= 0;


#if !defined(TCL_PARSER)

/*
 * Main routine if building a standalone executable.
 */
main ()
{
    /* Invoke ANTLR to parse the given input file.	*/
    ANTLR (start (), stdin);

    /* Display parsing statistics.	*/
    fprintf (stderr, "\ncstr:  Parsing statistics...\n");
    fprintf (stderr, "    Category         Count\n\n");
    fprintf (stderr, "   Total Lines         %d\n", zzline);
    fprintf (stderr, "   Good Chars          %d\n", numGoodChars);
    fprintf (stderr, "   Bad Chars           %d\n", numBadChars);
    fprintf (stderr, "   Good Strings        %d\n", numGoodStrings);
    fprintf (stderr, "   Bad Strings         %d\n", numBadStrings);
    fprintf (stderr, "   C++ Comments        %d\n", numCPPComments);
    fprintf (stderr, "   Ramdom Junk         %d\n", numJunk);
    fprintf (stderr, "   Unexpected EOF      %s\n\n", (badEOF)? "YES": "NO");
}	/* End of main().	*/

/*
 * Encapsulate printing output.
 */
#define	put_str(str)	(fputs (str, stdout))
#define	put_num(fmat,i)	(fprintf (stdout, fmat, i))

#else

#include <tcl.h>

Tcl_Interp *tclInterp = NULL;

/*
 * Encapsulate printing output.
 */
#define	put_str(str)	(Tcl_AppendResult (tclInterp, str, (char *) NULL))
void put_num (const char *format, const int i)
{
    char buff [32];	/* Scratch pad.	*/

    /* Build the string reprsentation.	*/
    sprintf (buff, format, i);
    put_str (buff);
}


/*
 * Tcl command to invoke to run this parser on the given string.
 */
int ParserCmd (ClientData clientData,
	       Tcl_Interp *interp,
	       int argc,
	       char *argv[])
{
    int	displayStats	= 0;	/* 0 ==> do parsing.	*/
    char *usageMsg = "Usage: parser (stat | (parse stringToParse))";

    /* Keep ahold of the interpreter...	*/
    tclInterp = interp;

    /* Check argument list.	*/
    if (2 == argc)
	{
	/* Statistics request proper keyword?	*/
	if (strcmp ("stats", argv[1]))
	    {
	    /* Nope.	*/
	    interp->result = usageMsg;
	    return TCL_ERROR;
	    }
	else
	    {
	    displayStats = 1;
	    }
	}
    else if (3 == argc)
	{
	/* Parse string request proper keyword?	*/
	if (strcmp ("parse", argv[1]))
	    {
	    /* Nope.	*/
	    interp->result = usageMsg;
	    return TCL_ERROR;
	    }
	else
	    {
	    displayStats = 0;
	    }
	}
    else
	{
	interp->result = usageMsg;
	return TCL_ERROR;
	}

    /* Perform request action.	*/
    if (displayStats)
	{
	put_str ("\nParsing statistics...\n");
	put_str ("    Category         Count\n\n");
	put_str ("   Total Lines         ");
	put_num ("%d", zzline);
	put_str ("\n   Good Chars          ");
	put_num ("%d", numGoodChars);
	put_str ("\n   Bad Chars           ");
	put_num ("%d", numBadChars);
	put_str ("\n   Good Strings        ");
	put_num ("%d", numGoodStrings);
	put_str ("\n   Bad Strings         ");
	put_num ("%d", numBadStrings);
	put_str ("\n   Random Junk         ");
	put_num ("%d", numJunk);
	put_str ("\n   Unexpected EOF      ");
	put_str ((badEOF) ? "YES" : "NO");
	return TCL_OK;
	}
    else
	{
	/*
	 * Invoke the parser on the string.
	 * Note that the result is set elsewhere.
	 */
	ANTLRs (start(), argv[2]);
	return TCL_OK;
	}
}	/* End of ParserCmd ().	*/

#endif

>>

start
	: (shme)*
	;

shme
	: err:BAD_EOF
		<<
			{
			badEOF = 1;
			put_str ("\nUnexpected End-of-File!!!\n");
			};
		>>
	| cppc:CPP_COMMENT
		<<
			{
			numCPPComments++;
			put_str ("\nC++-style comment\n");
			put_str ("Line ");
			put_num ("%d", zzline);
			put_str (": Comment (");
			put_str ($cppc.text);
			put_str (")\n");
			}
		>>
	| cbad:BAD_CHAR_CONST
		<<
			{
			int c;

			numBadChars++;
			c = $cbad.text[1] & 0xff;
			put_str ("\nBad char constant\n");
			put_str ("Line ");
			put_num ("%d", zzline);
			put_str (": Char: (");
			put_str ($cbad.text);
			put_str (")\n");
			};
		>>
	| ch:CHAR_CONST
		<<
			{
			int c;

			numGoodChars++;
			c = $ch.text[1] & 0xff;
			put_str ("\nGood character constant\n");
			put_str ("Line ");
			put_num ("%d", zzline);
			put_str (": Char: CHAR(");
			put_num ("%c", c);
			put_str (") DEC(");
			put_num ("%d", c);
			put_str (") OCT(");
			put_num ("%o", c);
			put_str (") HEX(");
			put_num ("%x", c);
			put_str (") STR(");
			put_str ($ch.text);
			put_str (")\n");
			};
		>>
	| sbad:BAD_STRING_CONST
		<<
			{
			numBadStrings++;
			put_str ("\nBad string constant\n");
			put_str ("Line ");
			put_num ("%d", zzline);
			put_str (": String (");
			put_str ($sbad.text);
			put_str (")\n");
			}
		>>
	| << int numStrings = 1; >>
	  (s:STRING_CONST
		<<
			{
			char * p;
			int c;

			numGoodStrings++;
			put_str ("\nGood string constant part #");
			put_num ("%d", numStrings++);
			put_str ("\nLine ");
			put_num ("%d", zzline);
			put_str (": Octal version ");
		        for (p = $s.text; *p != 0; p++)
			    {
			    c = (*p & 0xff);
			    if ('\n' == c)
				put_str ("{newline}");
			    else if (isprint (c))
				put_num ("%c", c);
			    else
				{
				put_str ("{");
				put_num ("%o", c);
				put_str ("}");
				}
			    };

			put_str ("\nLine ");
			put_num ("%d", zzline);
			put_str (": Hex version ");
			for (p = $s.text; *p != 0; p++)
			    {
			    c = (*p & 0xff);
			    if ('\n' == c)
				put_str ("{newline}");
			    else if (isprint (c))
				put_num ("%c", c);
			    else
				{
				put_str ("{");
				put_num ("%x", c);
				put_str ("}");
				}
			    };
			put_str ("\n");
			};
		>>
	  )+
	| << int junkChars = 1; >>
	  (junk:JUNK
		<<
			{
			if (junkChars++ == 1)
			    {
			    put_str ("\nRandom Junk!");
			    put_str ("\nLine ");
			    put_num ("%d", zzline);
			    put_str (": Junk (");
			    }
			put_num ("%c", $junk.text[0] & 0xff);
			}
		>>
	  )+	<<
			{
			numJunk++;
			put_str (")\n");
			}
		>>
	;

