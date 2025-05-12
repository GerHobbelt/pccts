Cross Reference:

Rule              sordesc referenced by { }
Rule               header referenced by { sordesc }
Rule               tokdef referenced by { sordesc }
Rule            class_def referenced by { sordesc }
Rule                 rule referenced by { sordesc }
Rule                block referenced by { rule element }
Rule                  alt referenced by { block }
Rule              element referenced by { alt tree }
Rule      labeled_element referenced by { alt tree }
Rule                token referenced by { element labeled_element }
Rule                 tree referenced by { alt tree }
Rule            enum_file referenced by { }
Rule              defines referenced by { enum_file }
Rule             enum_def referenced by { enum_file }

sordesc :
	  ( header /* [1] { Header } */
 | tokdef /* [2] { Tokdef } */
 /* Opt { Eof Action "\}" "class" NonTerm } */
 )* ( Action /* [0] { Action } */
 /* Opt { Eof Action "\}" "class" NonTerm }, { Eof Action PassAction LABEL "\}" NonTerm Token "!" "\<" "\>" } */
 )* { class_def /* [1] { "class" } */
 /* [2] { Eof Action "\}" NonTerm } (optional branch) */
 } ( Action /* [0] { Action } */
 /* Opt { Eof Action "\}" NonTerm }, { Eof Action PassAction LABEL "\}" "!" "\<" "\>" } */
 )* ( rule /* [0] { NonTerm } */
 /* Opt { Eof Action "\}" } */
 )* ( Action /* [0] { Action } */
 /* Opt { Eof Action "\}" }, { Eof Action } */
 )* { "\}" /* [1] { "\}" } */
 /* [2] { Eof Action } (optional branch) */
 } ( Action /* [0] { Action } */
 /* Opt { Eof } */
 )* Eof /* [0] { Eof Action Header Tokdef "\}" "class" NonTerm } */

	;

header :
	  Header Action /* [0] { Header } */

	;

tokdef :
	  Tokdef RExpr /* [0] { Tokdef } */

	;

class_def :
	  "class" ( NonTerm /* [1] { NonTerm } */
 | Token /* [2] { Token } */
 ) OPT /* [0] { "class" } */

	;

rule :
	  NonTerm { "!" /* [1] { "!" } */
 /* [2] { PassAction LABEL "\<" "\>" } (optional branch) */
 } ( { "\<" /* [1] { "\<" } */
 /* [2] { PassAction } (optional branch) */
 } PassAction /* [1] { PassAction "\<" } */
 | /* [2] { LABEL "\>" } */
 ) { "\>" PassAction /* [1] { "\>" } */
 /* [2] { LABEL } (optional branch) */
 } LABEL block ";" /* [0] { NonTerm } */

	;

block :
	  alt ( "\|" alt /* [0] { "\|" } */
 /* Opt { "\}" ";" "\)" } */
 )* /* [0] { Action OPT WILD BT "\}" NonTerm Token "!" ";" "\|" "\(" "\)" } */

	;

alt :
	  { "!" /* [1] { "!" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } (optional branch) */
 } { ( labeled_element /* [1] { NonTerm Token }, { LABEL } */
 | element /* [2] { Action OPT WILD NonTerm Token "\(" }, { Action PassAction OPT WILD PRED_OP BT "\}" NonTerm Token "!" "\<" "\>" ";" "\|" "\(" "\)" ".." } */
 | tree /* [3] { BT } */
 )+ /* [1] { Action OPT WILD BT NonTerm Token "\(" } */
 /* [2] { "\}" ";" "\|" "\)" } (optional branch) */
 } /* [0] { Action OPT WILD BT "\}" NonTerm Token "!" ";" "\|" "\(" "\)" } */

	;

element :
	  token /* [1] { Token } */

	| NonTerm { "!" /* [1] { "!" } */
 /* [2] { Action PassAction OPT WILD BT "\}" NonTerm Token "\<" "\>" ";" "\|" "\(" "\)" } (optional branch) */
 } { { "\<" /* [1] { "\<" } */
 /* [2] { PassAction } (optional branch) */
 } PassAction /* [1] { PassAction "\<" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token "\>" ";" "\|" "\(" "\)" } (optional branch) */
 } { "\>" PassAction /* [1] { "\>" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } (optional branch) */
 } /* [2] { NonTerm } */

	| Action { PRED_OP /* [1] { PRED_OP } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } (optional branch) */
 } /* [3] { Action } */

	| "\(" block "\)" ( CLOSURE /* [1] { CLOSURE } */
 | POS_CLOSURE /* [2] { POS_CLOSURE } */
 | PRED_OP /* [3] { PRED_OP } */
 | /* [4] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } */
 ) /* [4] { "\(" } */

	| OPT block "\}" /* [5] { OPT } */

	| WILD { "!" /* [1] { "!" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } (optional branch) */
 } /* [6] { WILD } */

	;

labeled_element :
	  ( Token /* [1] { Token } */
 | NonTerm /* [2] { NonTerm } */
 ) LABEL ( token /* [1] { Token } */
 | NonTerm { "!" /* [1] { "!" } */
 /* [2] { Action PassAction OPT WILD BT "\}" NonTerm Token "\<" "\>" ";" "\|" "\(" "\)" } (optional branch) */
 } { { "\<" /* [1] { "\<" } */
 /* [2] { PassAction } (optional branch) */
 } PassAction /* [1] { PassAction "\<" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token "\>" ";" "\|" "\(" "\)" } (optional branch) */
 } { "\>" PassAction /* [1] { "\>" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } (optional branch) */
 } /* [2] { NonTerm } */
 | WILD { "!" /* [1] { "!" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } (optional branch) */
 } /* [3] { WILD } */
 | ( "\|" /* [1] { "\|" } */
 | ";" /* [2] { ";" } */
 | PassAction /* [3] { PassAction } */
 | Action /* [4] { Action } */
 | Eof /* [5] { Eof } */
 | "\(" /* [6] { "\(" } */
 | OPT /* [7] { OPT } */
 | "\)" /* [8] { "\)" } */
 | "\}" /* [9] { "\}" } */
 | BT /* [10] { BT } */
 ) /* [4] { Eof Action PassAction OPT BT "\}" ";" "\|" "\(" "\)" } */
 ) /* [0] { NonTerm Token } */

	;

token :
	  Token { ".." Token { "!" /* [1] { "!" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } (optional branch) */
 } /* [1] { ".." } */
 | "!" /* [2] { "!" } */
 /* [2] { Action OPT WILD BT "\}" NonTerm Token ";" "\|" "\(" "\)" } (optional branch) */
 } /* [0] { Token } */

	;

tree :
	  BT ( Token { ".." Token { "!" /* [1] { "!" } */
 /* [2] { Action OPT WILD BT NonTerm Token "\(" "\)" } (optional branch) */
 } /* [1] { ".." } */
 | "!" /* [2] { "!" } */
 /* [2] { Action OPT WILD BT NonTerm Token "\(" "\)" } (optional branch) */
 } /* [1] { Token }, { Action OPT WILD BT NonTerm Token "!" "\(" "\)" ".." } */
 | WILD { "!" /* [1] { "!" } */
 /* [2] { Action OPT WILD BT NonTerm Token "\(" "\)" } (optional branch) */
 } /* [2] { WILD } */
 | ( Token /* [1] { Token } */
 | NonTerm /* [2] { NonTerm } */
 ) LABEL ( Token { ".." Token { "!" /* [1] { "!" } */
 /* [2] { Action OPT WILD BT NonTerm Token "\(" "\)" } (optional branch) */
 } /* [1] { ".." } */
 | "!" /* [2] { "!" } */
 /* [2] { Action OPT WILD BT NonTerm Token "\(" "\)" } (optional branch) */
 } /* [1] { Token } */
 | WILD { "!" /* [1] { "!" } */
 /* [2] { Action OPT WILD BT NonTerm Token "\(" "\)" } (optional branch) */
 } /* [2] { WILD } */
 ) /* [3] { NonTerm Token }, { LABEL } */
 ) ( labeled_element /* [1] { NonTerm Token }, { LABEL } */
 | element /* [2] { Action OPT WILD NonTerm Token "\(" }, { Action PassAction OPT WILD PRED_OP BT "\}" NonTerm Token "!" "\<" "\>" "\|" "\(" "\)" ".." } */
 | tree /* [3] { BT } */
 /* Opt { "\)" } */
 )* "\)" /* [0] { BT } */

	;

enum_file :
	  { "#ifndef" ID { "#define" ID /* [1] { "#define" } */
 /* [2] { "enum" } (optional branch) */
 } /* [1] { "#ifndef" } */
 /* [2] { "enum" } (optional branch) */
 } ( enum_def /* [1] { "enum" } */
 )+ /* [1] { "#ifndef" "enum" } */

	| defines /* [2] { "#define" } */

	|
	 /* [3] { Eof } */

	;

defines :
	  ( "#define" ID INT /* [1] { "#define" } */
 )+ /* [0] { "#define" } */

	;

enum_def :
	  "enum" { ID /* [1] { ID } */
 /* [2] { "\{" } (optional branch) */
 } "\{" ID ( "=" INT /* [1] { "=" } */
 | /* [2] { "," "\}" } */
 ) ( "," { "DLGminToken" { "=" INT /* [1] { "=" } */
 /* [2] { "," "\}" } (optional branch) */
 } /* [1] { "DLGminToken" } */
 | "DLGmaxToken" { "=" INT /* [1] { "=" } */
 /* [2] { "," "\}" } (optional branch) */
 } /* [2] { "DLGmaxToken" } */
 | ID ( "=" INT /* [1] { "=" } */
 | /* [2] { "," "\}" } */
 ) /* [3] { ID } */
 /* [2] { "," "\}" } (optional branch) */
 } /* [0] { "," } */
 /* Opt { "\}" } */
 )* "\}" ";" /* [0] { "enum" } */

	;

Tree Nodes:  peak 45  created 146  lost 24


Dump of First/Follow Cache

rule alt First[1]

     Action           OPT              WILD             BT              
     NonTerm          Token            "!"              "\("            

rule alt Follow[1]

     "\}"             ";"              "\|"             "\)"            

rule block First[1]

     Action           OPT              WILD             BT              
     NonTerm          Token            "!"              "\|"            
     "\("            

rule block Follow[1]

     "\}"             ";"              "\)"            

rule class_def First[1]

     "class"         

rule class_def First[2]

     NonTerm          Token           

rule defines First[1]

     "#define"       

rule defines Follow[1]

     Eof             

rule element First[1]

     Action           OPT              WILD             NonTerm         
     Token            "\("            

rule element First[2]

     Action           PassAction       OPT              WILD            
     PRED_OP          BT               "\}"             NonTerm         
     Token            "!"              "\<"             "\>"            
     "\|"             "\("             "\)"             ".."            

rule element Follow[1]

     Action           OPT              WILD             BT              
     "\}"             NonTerm          Token            ";"             
     "\|"             "\("             "\)"            

rule enum_def First[1]

     "enum"          

rule enum_file Follow[1]

     Eof             

rule header First[1]

     Header          

rule labeled_element First[1]

     NonTerm          Token           

rule labeled_element First[2]

     LABEL           

rule labeled_element Follow[1]

     Action           OPT              WILD             BT              
     "\}"             NonTerm          Token            ";"             
     "\|"             "\("             "\)"            

rule rule First[1]

     NonTerm         

rule rule First[2]

     PassAction       LABEL            "!"              "\<"            
     "\>"            

rule sordesc Follow[1]

     Eof             

rule tokdef First[1]

     Tokdef          

rule token First[1]

     Token           

rule token First[2]

     "!"              ".."            

rule token Follow[1]

     Action           OPT              WILD             BT              
     "\}"             NonTerm          Token            ";"             
     "\|"             "\("             "\)"            

rule tree First[1]

     BT              

End dump of First/Follow Cache
