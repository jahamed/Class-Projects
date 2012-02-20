/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #8, public08.c
 * Checks if print_instruction() handles a simple instruction properly
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr instr= {HALT, 0, 0, 0, 0};
  
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
