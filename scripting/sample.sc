/*
 * sample source file
 *
 *       for
 *
 * I_A's Script Language Compiler
 */
script test_script ()

definitions

/*
   uncomment the line below to see 'unsupported' message by ANTLR parser 
   using our own special custom exception. 
 */
//define quadword_t as integer * 8;

  const boo_boo = 5;

declarations   /* or: 'var' */
  i: integer;

implementation

  i := 0;

  if (i < 10) 
  {
    //
    // uh-huh. we accept 'VMS'-style identifiers. 
    // It's in the C/C++ standards too, so why shouldn't we allow it, eh? ;-)
    //
    void lib$display("(1) i < 10 ...\n");
    i++;
    if (i < 10) 
    {
      void lib$display("(2) i < 10 ...\n");
      i++;
    }
    endif;
  }
  else
  {
    void lib$display("hello world!\n");
  }
  endif;

  i += 42;
  i **= 3;
  i := -!-~!~i;
  i := i +i +i +i +i +i +i +i ++i;
  void lib$display(i);

endscript

      

