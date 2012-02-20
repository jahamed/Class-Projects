#if !defined(ASSEMBLER_H)
#define ASSEMBLER_H

#include "interpreter.h"

/*
 * Originally written by Saeed Alaei, 2006.  Modified and revised by
 * Larry Herman, 2007, 2008.  International copyrights reserved.
 * Wash with like colors.
 */

/*
 * General features:
 *
 * All of the following may appear in a program to be assembled and will be
 * handled correctly:
 *   - Empty lines
 *   - Labels (must begin with a non-digit character and end with a colon)
 *   - Comments (begin with # or with //), which can appear on a line by
 *     themselves, or following an instruction at the end of the same line
 *   - The .data directive, of the form ".data num", which causes the value
 *     num to be stored in the current memory location
 * 
 * More information:
 *   - Numeric constants may be given in decimal, in hexadecimal using a 0x
 *     prefix, or octal using a 0 prefix
 *   - Labels can be used wherever a memory address or a constant is expected
 *   - Multiple lables on the same line or on empty lines are valid
 * 
 * Note that the assembler checks instructions for correct syntax (is the
 * instruction name valid and does it have the right number and types of
 * operands?), but does not check the validity of instructions.  For
 * example, it does not check for instructions which attempt to modify R0 or
 * R15, it will just assemble such instructions.  Of course, the validity of
 * instructions may need to be checked elsewhere in the project.
 */

/* Description of parameters and return value:
 *
 *   - fname is the name of a file containing the program to be assembled.
 *     If fname is "", the assembly program will be read from the program's
 *     standard input.
 *
 *   - pgm is where the instructions of the assembled program will be placed.
 *     You can do anything you'd like with the contents of the assembled
 *     program to test your functions- call valid_instruction() on each
 *     element, call run() on the assembled program, call load_program()
 *     to load it into an array representing memory somewhere, etc.
 *
 * Returns the number of instructions which were assembled.
 */
int assemble(const char* fname, Memory_word pgm[], int start_address);

#endif
