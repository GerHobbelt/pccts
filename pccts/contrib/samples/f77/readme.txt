1. What is this?
	This is a translation engine which implements some translation rules
	and is ready to be customised for any other translation requirements.
	It consists of ANTLR grammars (f77.g, decl.g, expr.g and io.g) which
	builds the AST, f77tran.sor (which modifies the AST) and f77out.sor
	which prints the resulting AST.
2. 	How to compile?
	To compile the code as it is you need 

	- OS/2 V 2
	- Borland C/C++ for OS/2 V 2.0
	- PCCTS V 1.31 (and posibly above but it  has not been tested)
	
	Except for the INCLUDE statement, all the other statements are completely
	implemented. The grammar covers the full UNISYS FORTRAN. Note that you
	can write a grammar for a language in 'infinite' number of ways depending
	on the purpose. This grammar was written for the purpose of translating
	between two dialects of the same language.
	
	
3. Anything else?
	I do not know wether this files will be of any use to anybody hence I will
	not write detailed description of them. However I would like to encourage
	anybody to ask me any question about this application. I like PCCTS tools
	and would like to share the experience.
4 . How to contact me?
email- ferhath@ozemail.com.au
Name and address - 
	Ferhat Hajdarpasic
	RHO Systems Pty Limited
	Level 4, 55 Lavender Street
	Milsons Point NSW 2061
	AUSTRALIA
Phone : +(612) 954 - 1736
Fax : +(612) 922 - 2648

Best regards.
Ferhat Hajdarpasic
