// go.c -- interpreter for "go" code

// include headers
#include <dos/dos.h>       // dos file stuff
#include <stdio.h>         // standard i/o
#include <fcntl.h>         // file stuff
#include <assert.h>        // assertions
#include <stdlib.h>        // for exit()
#include "opcodes.h"       // instruction codes
#include "opnames.h"       // instruction code names

#define MAX_MEM  8191      // max amount of memory available
int memory[MAX_MEM+1];     // the "computer" memory

int  pc;                   // program counter
int  bp;                   // base pointer
int  sp;                   // stack pointer
int  stackBottom;          // where is the bottom of the stack
int  running;              // are we running?
int debug = 0;             // are we in debug mode?
int line_in_progress = 0;  // is there an output line currently in progress
int file;                  // file handle

// This array is used to select which functions are called for each instruction code
void (*ops[NUMBER_OF_OPCODES+1])();


//*************************************************************************************************
// NOTE: from this point on, this is your computer code, converted to C from C++
//       I'll flag when my code comes in again...
//*************************************************************************************************
// general machine operations
void error(char* message);
int pop();
void push(int word);
int fetch();

// machine instructions
void add();
void and();
void bounds();
void branch();
void branchNonZero();
void branchZero();
void constant();
void divide();
void equal();
void greaterThan();
void greaterOrEq();
void halt();
void inputInteger();
void lessThan();
void lessOrEq();
void localVariable();
void modulo();
void multiply();
void negate();
void notEqual();
void not();
void or();
void outputInteger();
void outputNewLine();
void outputString();
void popParms();
void procedureCall();
void procedure();
void program();
void returnInst();
void simpleAssign();
void assign();
void subtract();
void simpleValue();
void skipLine();
void value();
void variable();


void error(char* message)
{
   printf("*** Error:  %s\n", message);
   running = 0;
}


int pop()
{
   int word;
   assert(sp >= 0);
   word = memory[sp];
   --sp;
   return word;
}


void push(int word)
{
   sp = sp + 1;
   assert(sp < MAX_MEM);
   memory[sp] = word;
}


int fetch()
{
   int word;
   word = memory[pc];
   ++pc;
   if (debug)
      printf("%5d ",word);
   return word;
}



// *** start machine instructions ***


void add()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   push(operand_1 + operand_2);
}


void branch()
{
   int displacement;

   displacement = fetch();
   pc += displacement;
}


void branchNonZero()
{
   int displacement, value;

   displacement = fetch();
   value = pop();
   if (value != 0)
     pc += displacement;
}


void branchZero()
{
   int displacement, value;

   displacement = fetch();
   value = pop();
   if (value == 0)
     pc += displacement;
}


void constant()
{
   int value;

   value = fetch();
   push(value);
}


void divide()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   push(operand_1/operand_2);
}


void equal()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   if (operand_1 == operand_2)
       push(1);
   else
       push(0);
}


void greaterThan()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   if (operand_1 > operand_2)
       push(1);
   else
       push(0);
}


void greaterOrEq()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   if (operand_1 >= operand_2)
       push(1);
   else
       push(0);
}


void halt()
{
   running = 0;
}


void inputInteger()
{
   int i, destAddr;

   destAddr = pop();
   scanf("%d",&i);
   memory[destAddr] = i;
   line_in_progress = 0;
}


void lessThan()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   if (operand_1 < operand_2)
       push(1);
   else
       push(0);
}


void lessOrEq()
{
   int operand_1, operand_2;
   operand_2 = pop();
   operand_1 = pop();
   if (operand_1 <= operand_2)
       push(1);
   else
       push(0);
}


void localVariable()
{
   int displacement;

   displacement = fetch();
   push(bp + displacement);
}


void modulo()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   push(operand_1 % operand_2);
}


void multiply()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   push(operand_1*operand_2);
}


void negate()
{
   int operand_1;

   operand_1 = pop();
   push(-operand_1);
}


void notEqual()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   if (operand_1 != operand_2)
       push(1);
   else
       push(0);
}


void not()
{
   int operand_1;

   operand_1 = pop();
   if (operand_1 == 0)
       push(1);
   else
       push(0);
}


void outputInteger()
{
   int i;

   i = pop();
   printf("%d ", i);
   line_in_progress = 1;
}




void outputNewLine()
{
   printf("\n");
   line_in_progress = 0;
}

void popParms()
{
   int toss, i;
   i = fetch();
   for(;i>0; i--)
      toss = pop();
}

void procedureCall()
{
   int level, displacement, tempBp;

   level = fetch();
   displacement = fetch();
   tempBp = bp;
   while (level > 0)
   {
      tempBp = memory[tempBp];
      --level;
   }
   push(tempBp);    // static link
   push(bp);        // dynamic link
   push(pc);        // return address
   bp = sp - 2;
   pc += displacement;
}


void procedure()
{
   int varLength;

   varLength    = fetch();
   sp += varLength;
}


void program()
{
   int varLength;

   varLength = fetch();
   bp = stackBottom;
   sp = bp + varLength + 2;
   if (sp > MAX_MEM)
       error("Storage Error");
}


void returnInst()
{
   sp = bp - 1;
   pc = memory[bp + 2];
   bp = memory[bp + 1];
}


void simpleAssign()
{
   int x, destAddr;

   x = pop();
   destAddr = pop();
   memory[destAddr] = x;
}

void assign()
{
   int i, destAddr;
   
   i = fetch();   
   destAddr = memory[sp-i];
   for(i=i-1; i>=0; i--)
      memory[destAddr+i] = pop();
   destAddr = pop();  // Just remove the addr
}

void value()
{
   int i, addr;
   int num = fetch();
   addr = pop();
   for(i=0; i <num; i++)
      push(memory[addr+i]);
}


void subtract()
{
   int operand_1, operand_2;

   operand_2 = pop();
   operand_1 = pop();
   push(operand_1 - operand_2);
}


void simpleValue()
{
   int x;

   x = pop();
   push(memory[x]);
}


void variable()
{
   int level, displacement, tempBp;

   level        = fetch();
   displacement = fetch();
   tempBp = bp;
   while (level > 0)
   {
      tempBp = memory[tempBp];
      --level;
   }
   push(tempBp + displacement);
}


// *** END machine instructions ***


//**************************************************************************************
// Ok, my code starts again here
//**************************************************************************************

// bounds -- checks that the array index is within the array's bounds, then
//    normalizes it within those bounds
void bounds()
{
   int upper, lower, index;
   upper = pop(); // get the bounds
   lower = pop();
   index = pop(); // get the index
   
   // perform the bounds check
   if (index < lower || index > upper)
   {
      printf("Runtime error: index out of bounds\n");
      exit(4);
   }
   else  // if bounds check was ok, normalize the index
      push(index-lower);
}

// outputString -- output a string literal
void outputString()
{
   int len;

   // get the length of the string and for each char, get it and write it
   for(len = fetch(); len > 0; len--)
      printf("%c",(char)fetch());
   line_in_progress = 1;
}

// skipLine -- skips a line in the output
//   NOTE: I assume that skipLine means:
//             if a line is already in progress
//                end it
//             skip the next line
void skipLine()
{
   if (line_in_progress)
      printf("\n");
   printf("\n");
   line_in_progress = 0;
}

// setup_function_table -- set up the jump table for the functions to be called
void setup_function_table()
{
   // first, set all positions in the jump table to NULL
   int i;
   for(i=0; i<= NUMBER_OF_OPCODES; i++)
      ops[i] = NULL;
      
   // Set each instruction code's jump spot to the appropriate function
   ops[i_add]           = add;
   ops[i_goto]          = branch;
   ops[i_branch_true]   = branchNonZero;
   ops[i_branch_false]  = branchZero;
   ops[i_constant]      = constant;
   ops[i_div]           = divide;
   ops[i_eq]            = equal;
   ops[i_get_int]       = inputInteger;
   ops[i_gt]            = greaterThan;
   ops[i_ge]            = greaterOrEq;
   ops[i_halt]          = halt;
   ops[i_lt]            = lessThan;
   ops[i_le]            = lessOrEq;
   ops[i_localvar]      = localVariable;
   ops[i_mod]           = modulo;
   ops[i_mult]          = multiply;
   ops[i_neg]           = negate;
   ops[i_ne]            = notEqual;
   ops[i_not]           = not;
   ops[i_proc_call]     = procedureCall;
   ops[i_procedure]     = procedure;
   ops[i_program]       = program;
   ops[i_put_int]       = outputInteger;
   ops[i_new_line]      = outputNewLine;
   ops[i_return]        = returnInst;
   ops[i_sub]           = subtract;
   ops[i_simple_assign] = simpleAssign;
   ops[i_simple_value]  = simpleValue;
   ops[i_variable]      = variable;
   ops[i_assign]        = assign;
   ops[i_value]         = value;
   ops[i_put_string]    = outputString;
   ops[i_bounds]        = bounds;
   ops[i_skip_line]     = skipLine;
   ops[i_pop]           = popParms;
}


// run -- run a "go" file
void run()
{
   int OpCode,i;

   running = 1;
   pc = 0;
   while (running)
   {
      OpCode = fetch();  // get the next instruction
      
      // if debug mode is on, write the instruction and its name
      if (debug)
         printf("(@%-5d %15s) ", pc-1, op_names[OpCode]);
         
      // if the jump table spot for the function is not defined, state so
      if (ops[OpCode] == NULL)
         printf("invalid opcode %d\n",OpCode);
         
      // otherwise, execute the correct routine
      else
         ops[OpCode]();
         
      // If debugging is on, print the current stack contents
      if (debug)
      {
         // add spacing based on the number of operands for the instruction
         if (HAS_NO_OPERANDS(OpCode))         
            printf("            ");
         else if (!HAS_TWO_OPERANDS(OpCode))
            printf("      ");
         printf(" --->>> ");
         for(i=sp; i >= stackBottom; i--)
            printf("%d ",memory[i]);
         printf("\n");
      }
   }
}


// load -- load a "go" file
void load(char *file_name)
{
   int count;
   int address = 0;

   // open the file
   if ((file = open(file_name, O_RDONLY)) < 0)
      error("Could not open the executable file\n");
   else     
   {
      // Read the file into memory
      while (count = read(file, &memory[address++], sizeof(int)));
      stackBottom = address;
      close(file);
   }
}


// Main -- check parameters and run
void main(int argc, char **argv)
{
   int i;
   
   // Check the number of parameters
   if (argc < 2 || argc > 3)
      error("Usage: go <executable name> [-d]\n");
      
   else
   {
      if (argc == 3)
         // if debug flag is set, turn debugging on
         if (argv[2][0] == '-' && argv[2][1] == 'd')
            debug = 1;
         else
            printf("Invalid option %s ignored\n",argv[2]);
            
      // zero out memory
      for (i = 0;  i <= MAX_MEM; i++)
         memory[i] = 0;

      // initialize registers
      pc = bp = sp = stackBottom = 0;
      running = 0;
    
      load(argv[1]);             // load the program
      flushall();                // flush output buffers
      setup_function_table();    // setup jump table
      run();                     // run the program
   }
}