/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #11, public11.c
 * Checks if print_instruction() handles an lw instruction properly
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr instr= {LW, 0x538, 1, 12, 10};
  
  retval= print_instruction(instr);
  printf("\n");
  if (retval != 1) {
    printf("print_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
