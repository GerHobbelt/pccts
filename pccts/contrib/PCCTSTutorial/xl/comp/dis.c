// dis.c -- disassembler for "go" code

// include headers
#include <stdio.h>      // standard i/o
#include "opcodes.h"    // instruction codes
#include "opnames.h"    // names for the codes
#include <fcntl.h>      // file stuff


// The main routine -- fairly short and sweet...
void disassemble(char *file_name)
{
   int file; // file handle
   int op, op1, i, c;
   int loc = 0;

   // open the file
   if ((file = open(file_name, O_RDONLY)) < 0)
      printf("Could not open the executable file\n");
   else     
   {
      // Read the file into memory
      while (read(file, &op, sizeof(int)))
      {
         // Print out the instruction displacement and operation name
         printf("%6d %-15s", loc, op_names[op]);
         loc++;
         if (!HAS_NO_OPERANDS(op))
         {
            // Read first operand
            read(file, &op1, sizeof(int));
            // Print it
            printf("%10d",op1);
            loc++;
            // If it's a branch instruction, print the destination displacement
            if (op == i_goto || op == i_branch_true || op == i_branch_false)
               printf("(%10d)", loc+op1);
         }
         // If this is a "put string" instruction, write out the string
         if (op == i_put_string)
         {
            printf(" ");
            for(i=0; i<op1; i++)
            {
               read(file, &c, sizeof(int));
               printf("%c", (char)c);
            }
         }
         // if there is a second operand, print it
         else if (HAS_TWO_OPERANDS(op))
         {
            read(file, &op1, sizeof(int));
            printf("%10d",op1);
            loc++;
            if (op == i_proc_call) 
               printf("(%10d)", loc+op1);
         }
         printf("\n");
      }
      close(file);
   }
}


// Main -- call the disassembler...
void main(int argc, char **argv)
{
   if (argc != 2)
      printf("Usage: dis <executable name>\n");
   else
      disassemble(argv[1]);
}