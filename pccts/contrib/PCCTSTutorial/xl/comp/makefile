# makefile for xl compiler

# object files needed to produce the load module
OBJ=scan.o xl.o err.o sym.o code_gen.o

# this makefile will build the xl compiler, disassembler and interpreter
all: xl go dis
   @echo "done"

################################
#  xl compiler
################################

# main load module
xl: $(OBJ)
	sc link $(OBJ) to xl

#  convert the antlr description into a dlg description and c and h files
xl.c : xl.pccts
	antlr -ga -gd -gt -o work:comp xl.pccts

#  compile the parser
xl.o: xl.c xl.pccts.h xl.ast_defs.h xl.support.c
   sc xl.c 

# compile symbol table handling
sym.o : sym.c xl.c xl.ast_defs.h
	sc sym.c 

#  compile the scanner
scan.o : scan.c xl.ast_defs.h
   sc scan.c
   
#  create a sacnner from the dlg input (which was produced by antlr)
scan.c : xl.c 
	dlg -ga -C2 parser.dlg scan.c

#  compile the code generator
code_gen.o: code_gen.c xl.ast_defs.h xl.c opcodes.h opnames.h
   sc code_gen.c 

# link the interpreter
go: go.o
   sc link go.o to go
   
#  compile the interpreter
go.o: go.c opcodes.h
   sc go.c
   
#  link the disassembler
dis: dis.o
   sc link dis.o to dis
   
#  compile the disassembler
dis.o: dis.c opnames.h opcodes.h
   sc dis.c