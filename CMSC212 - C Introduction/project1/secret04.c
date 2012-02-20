/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #4, secret04.c
 * Calls print_instruction() with a blt instruction containing a bad address
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr instr= { BLT, 0x0539, 1, 2, 3 };

  retval= print_instruction(instr);
  if (retval != 0) {
    printf("print_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
