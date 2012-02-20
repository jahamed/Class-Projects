/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #1, secret01.c
 * Tests disassemble() with a 22-instruction program containing every
 *   possible opcode
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr program[50];
  Instr instr= { HALT, 0x0004, 1, 2, 3 };
  int i;
  Op_code op;

  i= 0;
  for (op= HALT; op <= WRITE_CHAR; op++) {
    instr.operation= op;
    program[i++]= instr;
  }

  retval= disassemble(program, i);
  if (retval != 1) {
    printf("disassemble() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
