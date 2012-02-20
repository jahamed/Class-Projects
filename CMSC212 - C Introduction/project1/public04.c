/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #4, public04.c
 * Ensures disassemble() functions properly when given a negative number
 *   of elements
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr program[5];
  
  retval= disassemble(program, -5);
  if (retval != 0) {
    printf("disassemble() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
