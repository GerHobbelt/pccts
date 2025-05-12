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
	  ( header | tokdef )* ( Action )* { class_def } ( Action )* ( rule )* ( Action )* { "\}" } ( Action )* Eof
	;

header :
	  Header Action
	;

tokdef :
	  Tokdef RExpr
	;

class_def :
	  "class" ( NonTerm | Token ) OPT
	;

rule :
	  NonTerm { "!" } ( { "\<" } PassAction | ) { "\>" PassAction } LABEL block ";"
	;

block :
	  alt ( "\|" alt )*
	;

alt :
	  { "!" } { ( labeled_element | element | tree )+ }
	;

element :
	  token
	| NonTerm { "!" } { { "\<" } PassAction } { "\>" PassAction }
	| Action { PRED_OP }
	| "\(" block "\)" ( CLOSURE | POS_CLOSURE | PRED_OP | )
	| OPT block "\}"
	| WILD { "!" }
	;

labeled_element :
	  ( Token | NonTerm ) LABEL ( token | NonTerm { "!" } { { "\<" } PassAction } { "\>" PassAction } | WILD { "!" } | ( "\|" | ";" | PassAction | Action | Eof | "\(" | OPT | "\)" | "\}" | BT ) )
	;

token :
	  Token { ".." Token { "!" } | "!" }
	;

tree :
	  BT ( Token { ".." Token { "!" } | "!" } | WILD { "!" } | ( Token | NonTerm ) LABEL ( Token { ".." Token { "!" } | "!" } | WILD { "!" } ) ) ( labeled_element | element | tree )* "\)"
	;

enum_file :
	  { "#ifndef" ID { "#define" ID } } ( enum_def )+
	| defines
	|
	
	;

defines :
	  ( "#define" ID INT )+
	;

enum_def :
	  "enum" { ID } "\{" ID ( "=" INT | ) ( "," { "DLGminToken" { "=" INT } | "DLGmaxToken" { "=" INT } | ID ( "=" INT | ) } )* "\}" ";"
	;
