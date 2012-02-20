/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #5, secret05.c
 * Calls print_instruction() with blt instructions around the upper limit
 *   of valid memory addresses (0x1ff8= ok, 0x2000 = not ok)
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr instr= { BLT, 0x1ff8, 1, 2, 3 };

  retval= print_instruction(instr);
  printf("\n");
  if (retval != 1) {
    printf("print_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  instr.addr_or_const= 0x2000;
  retval= print_instruction(instr);
  if (retval != 0) {
    printf("print_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
