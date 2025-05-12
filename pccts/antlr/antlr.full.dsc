Cross Reference:

Rule              grammar referenced by { }
Rule            class_def referenced by { grammar }
Rule                 rule referenced by { grammar }
Rule              laction referenced by { grammar }
Rule              lmember referenced by { grammar }
Rule              lprefix referenced by { grammar }
Rule                aPred referenced by { grammar }
Rule           predOrExpr referenced by { aPred predPrimary }
Rule          predAndExpr referenced by { predOrExpr }
Rule          predPrimary referenced by { predAndExpr predPrimary }
Rule            aLexclass referenced by { grammar }
Rule                error referenced by { grammar }
Rule               tclass referenced by { grammar }
Rule                token referenced by { grammar }
Rule                block referenced by { rule element }
Rule                  alt referenced by { block }
Rule        element_label referenced by { element }
Rule              element referenced by { alt }
Rule default_exception_handler referenced by { grammar }
Rule      exception_group referenced by { rule block default_exception_handler }
Rule    exception_handler referenced by { exception_group }
Rule            enum_file referenced by { }
Rule              defines referenced by { enum_file }
Rule             enum_def referenced by { enum_file }

grammar :
	  ( "{\\}#header" Action /* [1] { "{\\}#header" } */
 | "{\\}#first" Action /* [2] { "{\\}#first" } */
 | "{\\}#parser" QuotedTerm /* [3] { "{\\}#parser" } */
 | "{\\}#tokdefs" QuotedTerm /* [4] { "{\\}#tokdefs" } */
 /* Opt { Action "\}" "class" NonTerminal "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } */
 )* ( Action /* [1] { Action } */
 | laction /* [2] { "{\\}#lexaction" } */
 | lmember /* [3] { "{\\}#lexmember" } */
 | lprefix /* [4] { "{\\}#lexprefix" } */
 | aLexclass /* [5] { "{\\}#lexclass" } */
 | token /* [6] { "{\\}#token" } */
 | error /* [7] { "{\\}#errclass" } */
 | tclass /* [8] { "{\\}#tokclass" } */
 | aPred /* [9] { "{\\}#pred" } */
 | default_exception_handler /* [10] { "exception" } */
 | class_def /* [11] { "class" } */
 | "\}" /* [12] { "\}" } */
 /* Opt { NonTerminal } */
 )* rule ( rule /* [1] { NonTerminal } */
 | aLexclass /* [2] { "{\\}#lexclass" } */
 | token /* [3] { "{\\}#token" } */
 | error /* [4] { "{\\}#errclass" } */
 | tclass /* [5] { "{\\}#tokclass" } */
 | aPred /* [6] { "{\\}#pred" } */
 | class_def /* [7] { "class" } */
 | "\}" /* [8] { "\}" } */
 /* Opt { Eof Action "\}" "class" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#errclass" "{\\}#tokclass" } */
 )* ( Action /* [1] { Action } */
 | laction /* [2] { "{\\}#lexaction" } */
 | lmember /* [3] { "{\\}#lexmember" } */
 | lprefix /* [4] { "{\\}#lexprefix" } */
 | error /* [5] { "{\\}#errclass" } */
 | tclass /* [6] { "{\\}#tokclass" } */
 | class_def /* [7] { "class" } */
 | aPred /* [8] { "{\\}#pred" } */
 | "\}" /* [9] { "\}" } */
 /* Opt { Eof } */
 )* Eof /* [0] { Action "{\\}#header" "{\\}#first" "{\\}#parser" "{\\}#tokdefs" "\}" "class" NonTerminal "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } */

	;

class_def :
	  "class" ( NonTerminal /* [1] { NonTerminal } */
 | TokenTerm /* [2] { TokenTerm } */
 ) ( "\{" /* [0] { QuotedTerm "\n|\r|\r\n" "\\(\n|\r|\r\n)" "\\~[]" "~[\n\r\"\\]+" "\"" "\n|\r|\r\n" "\\(\n|\r|\r\n)" "\\~[]" "~[\n\r\"\\]+" "'" "\n|\r|\r\n" "\\~[]" "~[\n\r'\\]+" "\*/" "\*" "\n|\r|\r\n" "~[\n\r\*]+" "\*/" "\*" "\n|\r|\r\n" "~[\n\r\*]+" "\n|\r|\r\n" "~[\n\r]+" "\n|\r|\r\n" "~[\n\r]+" "\n|\r|\r\n" "~[\n\r]+" "\*/" "\*" "\n|\r|\r\n" "~[\n\r\*]+" Action Pred PassAction "consumeUntil\( [\ \t]* \{~[\}]+\} [\ \t]* \)" "consumeUntil\( ~[\)]+ \)" "\n|\r|\r\n" "\>" "$" "$$" "$\[\]" "$\[" "$[0-9]+" "$[0-9]+." "$[0-9]+.[0-9]+" "$[_a-zA-Z][_a-zA-Z0-9]*" "#0" "#\[\]" "#\(\)" "#[0-9]+" "#line[\ \t]* [0-9]+ {[\ \t]* \"~[\"]+\" ([\ \t]* [0-9]*)* } (\n|\r|\r\n)" "#line ~[\n\r]* (\n|\r|\r\n)" "#[_a-zA-Z][_a-zA-Z0-9]*" "#\[" "#\(" "#" "\)" "\[" "\(" "\\\]" "\\\)" "\\>" "'" "\"" "\\$" "\\#" "\\(\n|\r|\r\n)" "\\~[\]\)>$#]" "/" "/\*" "\*/" "//" "~[\n\r\)\(\\$#\>\]\[\"'/]+" "[\t\ ]+" "\n|\r|\r\n" "\[" "\<\<" "\"" "/\*" "\*/" "//" "#line[\ \t]* [0-9]+ {[\ \t]* \"~[\"]+\" ([\ \t]* [0-9]*)* } (\n|\r|\r\n)" "#line ~[\n\r]* (\n|\r|\r\n)" "\>\>" WildCard "\@" LABEL Pragma FirstSetSymbol "{\\}#header" "{\\}#first" "{\\}#parser" "{\\}#tokdefs" "\}" "class" NonTerminal TokenTerm "!" "\<" "\>" ":" ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "\|\|" "&&" "\(" "\)" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" ".." "{\\}#token" "=" "[0-9]+" "\|" "\~" "^" "approx" "LL\(1\)" "LL\(2\)" "\*" "\+" "?" "=>" "exception" "default" "catch" "{\\}#[A-Za-z0-9_]*" "[\t\ ]+" "\n|\r|\r\n" "//" "/\*" "#ifdef" "#if" "#ifndef" "#else" "#endif" "#undef" "#import" ID "#define" INT "enum" "\{" "=" "," "\}" ";" } */
 /* Opt { "\{" } */
 )* "\{" /* [0] { "class" } */

	;

rule :
	  NonTerminal { "!" /* [1] { "!" } */
 /* [2] { QuotedTerm PassAction "\<" "\>" ":" } (optional branch) */
 } { { "\<" /* [1] { "\<" } */
 /* [2] { PassAction } (optional branch) */
 } PassAction /* [1] { PassAction "\<" } */
 /* [2] { QuotedTerm "\>" ":" } (optional branch) */
 } { "\>" PassAction /* [1] { "\>" } */
 /* [2] { QuotedTerm ":" } (optional branch) */
 } { QuotedTerm /* [1] { QuotedTerm } */
 /* [2] { ":" } (optional branch) */
 } ":" block ";" { Action /* [1] { Action } */
 /* [2] { Eof Action "\}" "class" NonTerminal "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } (optional branch) */
 } ( exception_group /* [0] { "exception" } */
 /* Opt { Eof Action "\}" "class" NonTerminal "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" } */
 )* /* [0] { NonTerminal } */

	;

laction :
	  "{\\}#lexaction" Action /* [0] { "{\\}#lexaction" } */

	;

lmember :
	  "{\\}#lexmember" Action /* [0] { "{\\}#lexmember" } */

	;

lprefix :
	  "{\\}#lexprefix" Action /* [0] { "{\\}#lexprefix" } */

	;

aPred :
	  "{\\}#pred" TokenTerm ( Pred { predOrExpr /* [1] { TokenTerm "!" "\(" } */
 /* [2] { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } (optional branch) */
 } /* [1] { Pred } */
 | predOrExpr /* [2] { TokenTerm "!" "\(" } */
 ) { ";" /* [1] { ";" } */
 /* [2] { Eof Action "\}" "class" NonTerminal "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } (optional branch) */
 } /* [0] { "{\\}#pred" } */

	;

predOrExpr :
	  predAndExpr ( "\|\|" predAndExpr /* [0] { "\|\|" } */
 /* Opt { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "\)" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } */
 )* /* [0] { TokenTerm "!" "\(" } */

	;

predAndExpr :
	  predPrimary ( "&&" predPrimary /* [0] { "&&" } */
 /* Opt { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "\|\|" "\)" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } */
 )* /* [0] { TokenTerm "!" "\(" } */

	;

predPrimary :
	  TokenTerm /* [1] { TokenTerm } */

	| "\(" predOrExpr "\)" /* [2] { "\(" } */

	| "!" predPrimary /* [3] { "!" } */

	;

aLexclass :
	  "{\\}#lexclass" TokenTerm /* [0] { "{\\}#lexclass" } */

	;

error :
	  "{\\}#errclass" ( TokenTerm /* [1] { TokenTerm } */
 | QuotedTerm /* [2] { QuotedTerm } */
 ) "\{" ( NonTerminal /* [1] { NonTerminal } */
 | TokenTerm /* [2] { TokenTerm } */
 | QuotedTerm /* [3] { QuotedTerm } */
 ) ( ( NonTerminal /* [1] { NonTerminal } */
 | TokenTerm /* [2] { TokenTerm } */
 | QuotedTerm /* [3] { QuotedTerm } */
 ) /* [0] { QuotedTerm NonTerminal TokenTerm } */
 /* Opt { "\}" } */
 )* "\}" /* [0] { "{\\}#errclass" } */

	;

tclass :
	  "{\\}#tokclass" TokenTerm { "\(" QuotedTerm "\)" /* [1] { "\(" } */
 /* [2] { "\{" } (optional branch) */
 } "\{" ( ( TokenTerm { ".." TokenTerm /* [1] { ".." } */
 /* [2] { QuotedTerm "\}" TokenTerm } (optional branch) */
 } /* [1] { TokenTerm } */
 | QuotedTerm /* [2] { QuotedTerm } */
 ) /* [1] { QuotedTerm TokenTerm } */
 )+ "\}" /* [0] { "{\\}#tokclass" } */

	;

token :
	  "{\\}#token" { TokenTerm { "\(" QuotedTerm "\)" /* [1] { "\(" } */
 /* [2] { Eof QuotedTerm Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "=" "exception" } (optional branch) */
 } { "=" "[0-9]+" /* [1] { "=" } */
 /* [2] { Eof QuotedTerm Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } (optional branch) */
 } /* [1] { TokenTerm } */
 /* [2] { Eof QuotedTerm Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } (optional branch) */
 } { QuotedTerm /* [1] { QuotedTerm } */
 /* [2] { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } (optional branch) */
 } { Action /* [1] { Action } */
 /* [2] { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } (optional branch) */
 } { ";" /* [1] { ";" } */
 /* [2] { Eof Action "\}" "class" NonTerminal "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "exception" } (optional branch) */
 } /* [0] { "{\\}#token" } */

	;

block :
	  alt ( exception_group /* [0] { "exception" } */
 /* Opt { "\}" ";" "\)" "\|" } */
 )* ( "\|" alt ( exception_group /* [0] { "exception" } */
 /* Opt { "\}" ";" "\)" "\|" } */
 )* /* [0] { "\|" } */
 /* Opt { "\}" ";" "\)" } */
 )* /* [0] { QuotedTerm Action Pred PassAction WildCard "\@" LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } */

	;

alt :
	  { "\@" /* [1] { "\@" } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } (optional branch) */
 } ( { "\~" /* [1] { "\~" } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol NonTerminal TokenTerm "\{" "\>" "\(" "\*" "\+" } (optional branch) */
 } element /* [0] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol NonTerminal TokenTerm "\{" "\>" "\(" "\~" "\*" "\+" } */
 /* Opt { "\}" ";" "\)" "\|" "exception" } */
 )* /* [0] { QuotedTerm Action Pred PassAction WildCard "\@" LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } */

	;

element_label :
	  LABEL ":" /* [0] { LABEL } */

	;

element :
	  { element_label /* [1] { LABEL } */
 /* [2] { QuotedTerm WildCard NonTerminal TokenTerm } (optional branch) */
 } ( TokenTerm { ".." ( QuotedTerm /* [1] { QuotedTerm } */
 | TokenTerm /* [2] { TokenTerm } */
 ) /* [1] { ".." } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard "\@" LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "!" "\>" ";" "\(" "\)" "\|" "\~" "^" "\*" "\+" "exception" } (optional branch) */
 } ( "^" /* [1] { "^" } */
 | /* [2] { QuotedTerm Action Pred PassAction WildCard "\@" LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } */
 | "!" /* [3] { "!" } */
 ) { "\@" /* [1] { "\@" } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } (optional branch) */
 } /* [1] { TokenTerm } */
 | QuotedTerm { ".." ( QuotedTerm /* [1] { QuotedTerm } */
 | TokenTerm /* [2] { TokenTerm } */
 ) /* [1] { ".." } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard "\@" LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "!" "\>" ";" "\(" "\)" "\|" "\~" "^" "\*" "\+" "exception" } (optional branch) */
 } ( "^" /* [1] { "^" } */
 | /* [2] { QuotedTerm Action Pred PassAction WildCard "\@" LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } */
 | "!" /* [3] { "!" } */
 ) { "\@" /* [1] { "\@" } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } (optional branch) */
 } /* [2] { QuotedTerm } */
 | WildCard ( "^" /* [1] { "^" } */
 | /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } */
 | "!" /* [3] { "!" } */
 ) /* [3] { WildCard } */
 | NonTerminal { "!" /* [1] { "!" } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\<" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } (optional branch) */
 } { { "\<" /* [1] { "\<" } */
 /* [2] { PassAction } (optional branch) */
 } PassAction /* [1] { PassAction "\<" } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } (optional branch) */
 } { "\>" PassAction /* [1] { "\>" } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } (optional branch) */
 } /* [4] { NonTerminal } */
 ) /* [1] { QuotedTerm WildCard LABEL NonTerminal TokenTerm } */

	| Action /* [2] { Action } */

	| Pred { PassAction /* [1] { PassAction } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } (optional branch) */
 } /* [3] { Pred } */

	| { Pragma ( "approx" /* [1] { "approx" } */
 | "LL\(1\)" /* [2] { "LL\(1\)" } */
 | "LL\(2\)" /* [3] { "LL\(2\)" } */
 ) /* [1] { Pragma } */
 /* [2] { FirstSetSymbol "\{" "\(" } (optional branch) */
 } { FirstSetSymbol "\(" ( NonTerminal /* [1] { NonTerminal } */
 | TokenTerm /* [2] { TokenTerm } */
 ) "\)" /* [1] { FirstSetSymbol } */
 /* [2] { "\{" "\(" } (optional branch) */
 } ( "\(" block "\)" ( "\*" /* [1] { "\*" } */
 | "\+" /* [2] { "\+" } */
 | "?" ( ( "=>" /* [1] { "=>" } */
 | "&&" /* [2] { "&&" } */
 ) Pred { PassAction /* [1] { PassAction } */
 /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } (optional branch) */
 } /* [1] { "&&" "=>" } */
 | /* [2] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } */
 ) /* [3] { "?" } */
 | /* [4] { QuotedTerm Action Pred PassAction WildCard LABEL Pragma FirstSetSymbol "\}" NonTerminal TokenTerm "\{" "\>" ";" "\(" "\)" "\|" "\~" "\*" "\+" "exception" } */
 ) /* [1] { "\(" } */
 | "\{" block "\}" /* [2] { "\{" } */
 ) /* [4] { Pragma FirstSetSymbol "\{" "\(" } */

	| "\*" /* [5] { "\*" } */

	| "\+" /* [6] { "\+" } */

	| "\>" /* [7] { "\>" } */

	| PassAction /* [8] { PassAction } */

	;

default_exception_handler :
	  exception_group /* [0] { "exception" } */

	;

exception_group :
	  "exception" { PassAction /* [1] { PassAction } */
 /* [2] { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "\)" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "\|" "exception" "default" "catch" } (optional branch) */
 } ( exception_handler /* [0] { "catch" } */
 /* Opt { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "\)" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "\|" "exception" "default" } */
 )* { "default" ":" Action /* [1] { "default" } */
 /* [2] { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "\)" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "\|" "exception" } (optional branch) */
 } /* [0] { "exception" } */

	;

exception_handler :
	  "catch" ( NonTerminal /* [1] { NonTerminal } */
 | TokenTerm /* [2] { TokenTerm } */
 ) ":" { Action /* [1] { Action } */
 /* [2] { Eof Action "\}" "class" NonTerminal ";" "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred" "\)" "{\\}#lexclass" "{\\}#errclass" "{\\}#tokclass" "{\\}#token" "\|" "exception" "default" "catch" } (optional branch) */
 } /* [0] { "catch" } */

	;

enum_file :
	  { "#ifndef" ID { "#define" ID { INT /* [1] { INT } */
 /* [2] { "#define" "enum" } (optional branch) */
 } /* [1] { "#define" } */
 /* [2] { "#define" "enum" } (optional branch) */
 } /* [1] { "#ifndef" } */
 /* [2] { "#define" "enum" } (optional branch) */
 } ( ( enum_def /* [1] { "enum" } */
 )+ /* [1] { "enum" } */
 | defines /* [2] { "#define" } */
 ) /* [1] { "#ifndef" "#define" "enum" } */

	|
	 /* [2] { Eof } */

	;

defines :
	  ( "#define" ID INT /* [1] { "#define" } */
 )+ /* [0] { "#define" } */

	;

enum_def :
	  "enum" ID "\{" ID ( "=" INT /* [1] { "=" } */
 | /* [2] { "," "\}" } */
 ) ( "," { ID { "=" INT /* [1] { "=" } */
 /* [2] { "," "\}" } (optional branch) */
 } /* [1] { ID } */
 | ID ( "=" INT /* [1] { "=" } */
 | /* [2] { "," "\}" } */
 ) /* [2] { ID } */
 /* [2] { "," "\}" } (optional branch) */
 } /* [0] { "," } */
 /* Opt { "\}" } */
 )* "\}" ";" /* [0] { "enum" } */

	;


Dump of First/Follow Cache

rule aLexclass First[1]

     "{\\}#lexclass" 

rule aPred First[1]

     "{\\}#pred"     

rule aPred Follow[1]

     Eof              Action           "\}"             "class"         
     NonTerminal      "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix"
     "{\\}#pred"      "{\\}#lexclass"  "{\\}#errclass"  "{\\}#tokclass" 
     "{\\}#token"     "exception"     

rule alt First[1]

     QuotedTerm       Action           Pred             PassAction      
     WildCard         "\@"             LABEL            Pragma          
     FirstSetSymbol   NonTerminal      TokenTerm        "\{"            
     "\>"             "\("             "\~"             "\*"            
     "\+"            

rule alt Follow[1]

     "\}"             ";"              "\)"             "\|"            
     "exception"     

rule block Follow[1]

     "\}"             ";"              "\)"            

rule class_def First[1]

     "class"         

rule default_exception_handler First[1]

     "exception"     

rule default_exception_handler Follow[1]

     Action           "\}"             "class"          NonTerminal     
     "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix" "{\\}#pred"     
     "{\\}#lexclass"  "{\\}#errclass"  "{\\}#tokclass"  "{\\}#token"    
     "exception"     

rule defines First[1]

     "#define"       

rule defines Follow[1]

     Eof             

rule element First[1]

     QuotedTerm       Action           Pred             PassAction      
     WildCard         LABEL            Pragma           FirstSetSymbol  
     NonTerminal      TokenTerm        "\{"             "\>"            
     "\("             "\*"             "\+"            

rule element Follow[1]

     QuotedTerm       Action           Pred             PassAction      
     WildCard         LABEL            Pragma           FirstSetSymbol  
     "\}"             NonTerminal      TokenTerm        "\{"            
     "\>"             ";"              "\("             "\)"            
     "\|"             "\~"             "\*"             "\+"            
     "exception"     

rule element_label First[1]

     LABEL           

rule enum_def First[1]

     "enum"          

rule enum_file Follow[1]

     Eof             

rule error First[1]

     "{\\}#errclass" 

rule exception_group First[1]

     "exception"     

rule exception_group Follow[1]

     Eof              Action           "\}"             "class"         
     NonTerminal      ";"              "{\\}#lexaction" "{\\}#lexmember"
     "{\\}#lexprefix" "{\\}#pred"      "\)"             "{\\}#lexclass" 
     "{\\}#errclass"  "{\\}#tokclass"  "{\\}#token"     "\|"            
     "exception"     

rule exception_handler First[1]

     "catch"         

rule exception_handler Follow[1]

     Eof              Action           "\}"             "class"         
     NonTerminal      ";"              "{\\}#lexaction" "{\\}#lexmember"
     "{\\}#lexprefix" "{\\}#pred"      "\)"             "{\\}#lexclass" 
     "{\\}#errclass"  "{\\}#tokclass"  "{\\}#token"     "\|"            
     "exception"      "default"        "catch"         

rule laction First[1]

     "{\\}#lexaction"

rule lmember First[1]

     "{\\}#lexmember"

rule lprefix First[1]

     "{\\}#lexprefix"

rule predAndExpr First[1]

     TokenTerm        "!"              "\("            

rule predAndExpr Follow[1]

     Eof              Action           "\}"             "class"         
     NonTerminal      ";"              "{\\}#lexaction" "{\\}#lexmember"
     "{\\}#lexprefix" "{\\}#pred"      "\|\|"           "\)"            
     "{\\}#lexclass"  "{\\}#errclass"  "{\\}#tokclass"  "{\\}#token"    
     "exception"     

rule predOrExpr First[1]

     TokenTerm        "!"              "\("            

rule predOrExpr Follow[1]

     Eof              Action           "\}"             "class"         
     NonTerminal      ";"              "{\\}#lexaction" "{\\}#lexmember"
     "{\\}#lexprefix" "{\\}#pred"      "\)"             "{\\}#lexclass" 
     "{\\}#errclass"  "{\\}#tokclass"  "{\\}#token"     "exception"     

rule predPrimary First[1]

     TokenTerm        "!"              "\("            

rule rule First[1]

     NonTerminal     

rule rule Follow[1]

     Eof              Action           "\}"             "class"         
     NonTerminal      "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix"
     "{\\}#pred"      "{\\}#lexclass"  "{\\}#errclass"  "{\\}#tokclass" 
     "{\\}#token"    

rule tclass First[1]

     "{\\}#tokclass" 

rule token First[1]

     "{\\}#token"    

rule token Follow[1]

     Eof              Action           "\}"             "class"         
     NonTerminal      "{\\}#lexaction" "{\\}#lexmember" "{\\}#lexprefix"
     "{\\}#pred"      "{\\}#lexclass"  "{\\}#errclass"  "{\\}#tokclass" 
     "{\\}#token"     "exception"     

End dump of First/Follow Cache
