/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #10, public10.c
 * Checks if print_instruction() handles a halt instruction properly
 *   even though it has some invalid data (which is unused by halt)
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr instr= {HALT, 0x3678, 15, 2, 10};
  
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
