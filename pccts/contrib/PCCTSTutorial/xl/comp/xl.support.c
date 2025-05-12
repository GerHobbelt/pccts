// xl.support.c   -- support routines for parser
//    Note: this file is actually included in the parser after ANTLR generates the c code

// Main compiler routine
   main(int argc, char *argv[])
   {
      AST *root=NULL;   // root of parse tree -- not used -- pccts requires it, though...
      int i;            // to loop through arguments
      file_name = NULL; // the name of the object file
      
      // check for flags in parameters
      for (i=1; i <=argc; i++)
      {
         if (argv[i][0] == '-')
            // -t -- walk through the generated AST after it's complete
            if(argv[i][1] == 't') 
               walk_tree = 1;      
               
            // -d -- display the identifiers as they are being defined, and what they are defined as
            else if (argv[i][1] == 'd') 
               show_definition = 1;      
               
            // -v -- list all variables used by a procedure after the procedure is compiled
            else if (argv[i][1] == 'v') 
               list_variables   = 1;      
               
            // -z -- trace the flow of the recursive descent parse through the rules
            else if (argv[i][1] == 'z') 
               trace = 1;      
               
            // -o <name> -- set the name of the object file
            else if (argv[i][1] == 'o')
               file_name = strdup(argv[i+1]);
      }               
      
      // if the object file name is not set, use "a.out"
      if (!file_name)
         file_name = strdup("a.out");
         
      // Initialze the symbol table
      zzs_init(HashTableSize, StringTableSize);
      
      // Call the main rule
      ANTLR(program(&root), stdin);
      
      // Free the memory allocated to the file name
      free(file_name);
   }
   
   
   // Override the pccts defined "default AST creation from attributes" routine
   void create_ast(AST *ast, Attrib *attr, int tok, char *text)   
   {
      Sym *s;
      ast->token = tok;             // set the token name
      if (text)                     // if the token has a name
      {
         s = zzs_get(text);         //    look it up in the symbol table
         ast->level = s->level;     //    copy it's level
         strcpy(ast->str, text);    //    copy the name
      }
      ast->type = NULL;             // don't know the type yet
      ast->ref = 0;                 // it's not a "var" parameter
      ast->size = 0;                // size not known yet
   }
                                    
   // Override the pccts default "explicitly create an AST node" function                                 
   AST *zzmk_ast(AST *node, int token, char *str)   
   {
      Sym *s;
      va_list ap;
      
      node->token = token;             // copy the token number
      if (str)                         // if a name was specifed
      {
         s = zzs_get(str);             //    look it up in the symbol table
         node->level = s->level;       //    copy the level
         strcpy(node->str, str);       //    copy the name
      }
      node->type = NULL;               // type not known yet
      node->ref = 0;                   // not a "var" parm
      node->size = 0;                  // size not known yet
      return node;
   }
   
   
// walk -- walk through the AST
   void walk(AST *tree)   
   {
      int i, right_count = 0;
      walk_indent++;
      
      // For each node in the tree...
      while(tree != NULL)
      {
         // start a new line
         printf("\n");
         
         // indent the line
         for(i=0;i<walk_indent;i++)
            printf("   ");
            
         // visually open a node 
         printf("(");
         
         // write the name of the token of the node
         printf(" %s",zztokens[tree->token]);
         
         // if the node has a name, print it in []
         if (tree->str != NULL && tree->str[0] != '\0')
            printf(" [%s]", tree->str);
            
         // Write what a reference refers to
         if (tree->token == Ref)
            printf(" %s ",tree->down->str);
            
         // If the node has a type, list it
         if (tree->type != NULL)
            printf(" >>  Type: %s",tree->type->str);
            
         // If the node has an initailizer, list it
         if (tree->init != NULL)
            if (tree->init->token == Ref)
               printf(" >>  InitialValue: %s",tree->init->down->str);
            else
               printf(" >>  InitialValue: %s",tree->init->str);

         // walk through the children of the node
         if (tree->token != Ref && tree->down != NULL)
            walk(tree->down);
          
         // move to the next sibling node
         tree = tree->right;
         
         // close the node
         printf(")");
      }
      walk_indent--;
   }
   
   
// pScope -- print all variables defined at a given scope (example pccts code)
   void pScope(Sym *p)
   {
      while(p!=NULL)   
      {
         printf("\tlevel %d |%-12s | %-15s\n",p->level,zztokens[p->token],p->symbol);
         p = p->scope;
      }
   }
   
   
// sasTRACEIN, sasTRACEOUT -- override default pccts trace routine
   void sasTRACEIN(char *text)
   {
      int i;   
      // indent the routine name
      for(i=0;i<indent;i++)
         printf("  ");
      // write the routine name
      printf(">>> %s\n",text);
       indent++;
   }
   
   void sasTRACEOUT(char *text)
   {
      int i;   
      indent--;
      // indent the routine name
      for(i=0;i<indent;i++)
         printf("  ");
      // write the routine name
      printf("<   %s\n",text);
   }
   
   
// strip_quotes -- strip leading/trailing quotes from string literal, and make "" be just one "
   void strip_quotes()
   {
      int to = 0, num_quotes_removed = 2; 
      int from;
      int old_len = strlen(NLATEXT);
      for(from = 1; from < old_len; from++)
      {
         NLATEXT[to++] = NLATEXT[from];
         if (NLATEXT[from] == '"' && NLATEXT[from+1] == '"')
         {
            from++;
            num_quotes_removed++;
         }
      }
      old_len -= num_quotes_removed;
      NLATEXT[old_len] = '\0';
   }


// print_expression -- print an expression for an error message
   void print_expression(AST *expr)
   {
      AST *child1 = zzchild(expr);        // get the children of the current node
      AST *child2 = zzsibling(child1);
      int x=0;
      
      // check the token type
      switch (TokenOf(expr))
      {
         case Op:  // any operator
            printf("(");
            // If there are two children, this is a binary operator -- print left first
            if (child2 != NULL)
               print_expression(child1);
               
            // print the name of the operator
            printf(" %s ", NameOf(expr));
            
            // if there is a second expression, print it
            if (child2)
               print_expression(child2);
            else
               print_expression(child1);
            printf(")");
           break;
           
         case Ref:
            // just print the kid
            print_expression(child1);
            break;
            
         case Index:
            // print the base variable with the index
            print_expression(child1);
            printf("[");
            print_expression(child2);
            printf("]");
            break;
            
         case Field:
            // print the base variable with the field
            print_expression(child1);
            printf(".");
            print_expression(child2);
            break;
            
         case Value:
            // just print the variable
            print_expression(child1);
            break;
            
         default: 
            // if boolean, print TRUE or FALSE; otherwise, just print the name
            if (TypeOf(expr) == boolean_type)
               if (NameOf(expr)[0] == '0')
                  printf("FALSE");
               else
                  printf("TRUE");
            else
               printf(NameOf(expr));
            break;
      }
   }
   
// syntax_error -- print an error message   
   void syntax_error(int line, char *loc_word, char *expl)
   {
      printf("line %d: syntax error at \"%s\" -- %s\n", line, loc_word, expl);
      error_occurred = 1;
   }

// find_val -- find the value of a constant in a given subtree
//   this routine will keep looking through the children until it finally finds a literal
//   that was used to define a constant
//   for example, if the code were
//       constant x : Integer := 1;
//       constant y : Integer := x;
//       constant z : Integer := y;
//   and we wanted to know the value of z, we would need to look at y, then x, then find the "1"
//   (an INTLIT node) in the AST
AST *find_val(AST *tree)
{
   // until we find a literal...
   while(tree && TokenOf(tree) != INTLIT && TokenOf(tree) != CHARLIT)
      if (Init(tree))            // if there is an initializer for this node
         tree = Init(tree);      //    follow it...
      else                       // otherwise
         tree = zzchild(tree);   //    follow the child of this node
   if (!tree)                    // if there was a problem, report it
      printf("Error retrieving value of constant\n");
   return tree;
}

// is_modifiable -- report whether or not a node represents a modifiable variable, or something like an expression/constant
int is_modifiable(AST *tree)
{
   // if we are on our way to finding the base variable, keep going...
   if (TokenOf(tree) == Value || TokenOf(tree) == Ref || TokenOf(tree) == Index || TokenOf(tree) == Field)
      return is_modifiable(zzchild(tree));
   // otherwise, return whether or not we are at a variable...
   else
      return (TokenOf(tree) == VAR);
}
