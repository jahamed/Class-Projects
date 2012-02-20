/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #7, secret07.c
 * Calls print_instruction() with instructions that don't store things in 
 *   the first register but have R00 or R15 as the first register
 */

#include <stdio.h>
#include <stdlib.h>
#include "machine.h"

static void test_good_instruction(Instr instr) {
  int retval= print_instruction(instr);
  printf("\n");
  if (retval != 1) {
    printf("print_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    exit(-1);
  }
}

int main() {
  Op_code no_store_ops[]= { HALT, SW, BLT, JR, WRITE_INT, WRITE_CHAR };
  Instr instr= { HALT, 0x0004, 0, 2, 3 };
  int i;

  for (i= 0; i < sizeof(no_store_ops) / sizeof(Op_code); i++) {
    instr.operation= no_store_ops[i];
    instr.reg1= 0;
    test_good_instruction(instr);
    instr.reg1= 15;
    test_good_instruction(instr);
  }

  printf("Test finished!\n");
  return 0;
}
