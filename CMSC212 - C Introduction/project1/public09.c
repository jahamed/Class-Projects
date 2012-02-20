/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #9, public09.c
 * Checks if print_instruction() handles an add instruction properly
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr instr= {ADD, 0, 3, 5, 9};
  
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
