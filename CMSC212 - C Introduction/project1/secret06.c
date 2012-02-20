/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #6, secret06.c
 * Calls print_instruction() with instructions that store things in R00 & R15
 */

#include <stdio.h>
#include <stdlib.h>
#include "machine.h"

static void test_bad_instruction(Instr instr) {
  int retval= print_instruction(instr);
  if (retval != 0) {
    printf("print_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    exit(-1);
  }
}

int main() {
  Op_code store_ops[]= { ADD, SUB, MUL, DIV, NEG, ANDB, ORB, XORB, ANDL,
                          ORL, NOTL, MOVE, LI, LW, READ_INT, READ_CHAR };
  Instr instr= { HALT, 0x0000, 0, 2, 3 };
  int i;

  for (i= 0; i < sizeof(store_ops) / sizeof(Op_code); i++) {
    instr.operation= store_ops[i];
    instr.reg1= 0;
    test_bad_instruction(instr);
    instr.reg1= 15;
    test_bad_instruction(instr);
  }

  printf("Test finished!\n");
  return 0;
}
