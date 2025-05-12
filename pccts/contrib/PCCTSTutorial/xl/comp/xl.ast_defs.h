// xl.ast_defs.h -- definitions that make setting up ASTs in pccts more readable
//   AST normally uses a syntax like     
//       #(#[Array, NULL], #(#[Lower, NULL], lower), #(#[Upper, NULL], upper)) 
//   which would just be
//       AST_Array(lower, upper)
//   using these definitions.   (It generates the same code)  A bit easier to read...

   #define AST_File(defs, program)           AST_List2(AST_Tok(File), defs, program)
   #define AST_Program(name, body)           AST_List1(AST_Node(Program, name), body)
   #define AST_Ref(thing)                    AST_List1(AST_Tok(Ref), thing)
   #define AST_IntLiteral(name)              AST_Node(INTLIT,    name)
   #define AST_CharLiteral(name)             AST_Node(CHARLIT,   name)
   #define AST_StringLiteral(name)           AST_Node(STRINGLIT, name)
   #define AST_Enum(list)                    AST_List1(AST_Tok(Enum), list)
   #define AST_Record(fields)                AST_List1(AST_Tok(Record), fields)
   #define AST_Array(lower, upper)           AST_List2(AST_Tok(Array), AST_List1(AST_Tok(Lower), lower), AST_List1(AST_Tok(Upper), upper))
   #define AST_Index(index, variable)        AST_List2(AST_Tok(Index), index, variable)
   #define AST_Field(field, variable)        AST_List2(AST_Tok(Field), field, variable)
   #define AST_ProcCall(proc, parms)         AST_List2(AST_Tok(ProcedureCall), proc, parms)
   #define AST_Exit(condition)               AST_List1(AST_Tok(Exit), condition)
   #define AST_Return                        AST_Tok(Return)
   #define AST_Selector(name)                name
   #define AST_If(cond, then_st, else_st)    AST_List3(AST_Tok(If), cond, AST_List1(AST_Tok(ThenPart), then_st), AST_List1(AST_Tok(ElsePart), else_st))
   #define AST_Then(then_st)                 then_st
   #define AST_Else(else_st)                 else_st
   #define AST_Make_Siblings(left, right)    left = AST_List2(NULL, left, right)
   #define AST_While(cond)                   AST_List1(AST_Tok(While), cond)   
   #define AST_Operand(op)                   AST_Node(Op, op)
   #define AST_BinaryOp(op, left, right)     AST_List2(op, left, right)
   #define AST_UnaryOp(op, right)            AST_List1(op, right)
   #define AST_Left(thing)                   thing
   #define AST_Right(thing)                  thing
   #define AST_Loop(content)                 AST_List1(AST_Tok(Loop), content)
   #define AST_Define(thing)                 AST_List1(AST_Tok(Define), thing)
   #define AST_Parms(stuff)                  AST_List1(AST_Tok(Parms),  stuff)
   #define AST_Type(thing)                   AST_Node(TYPE,  thing)
   #define AST_Constant(thing)               AST_Node(CONST, thing)
   #define AST_Variable(thing)               AST_Node(VAR,   thing)
   #define AST_Procedure(name, parms, body)  AST_List2(AST_Node(Procedure,  name), parms, body)
   #define AST_StartProcedure(name,parms)    AST_List1(AST_Node(Procedure,  name), parms)
   #define AST_Undefined                     AST_Node(Undefined, "<<**Undefined**>>")
   #define AST_Body(stuff)                   AST_List1(AST_Tok(Body), stuff)
   #define AST_Name(name)                    name
   #define AST_All_Are_Siblings              NULL
   #define AST_Get(var)                      AST_List1(AST_Tok(Get), var)
   #define AST_Put(var)                      AST_List1(AST_Tok(Put), var)
   #define AST_SkipLine                      AST_Tok(SkipLine)
   #define AST_NewLine                       AST_Tok(NewLine)
   #define AST_Assignment(var, val)          AST_List2(AST_Tok(Assign), var, val)
   #define AST_Value(thing)                  AST_List1(AST_Tok(Value), thing)
