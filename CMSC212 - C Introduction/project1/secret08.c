/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #8, secret08.c
 * Calls print_instruction() with lw, sw, and blt instructions that all have
 *   bad memory addresses
 */

#include <stdio.h>
#include <stdlib.h>
#include "machine.h"

static void test_instruction(Instr instr, int expval) {
  int retval= print_instruction(instr);
  if (expval)
    printf("\n");
  if (retval != expval) {
    printf("print_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    exit(-1);
  }
}

int main() {
  Instr instr= { HALT, 0x1337, 1, 2, 3 };

  instr.operation= LW;
  test_instruction(instr, 1);

  instr.operation= SW;
  test_instruction(instr, 1);

  instr.operation= BLT;
  test_instruction(instr, 0);

  printf("Test finished!\n");
  return 0;
}
