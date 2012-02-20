/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #3, secret03.c
 * Tests disassemble() with a 5-instruction program where the 4th is invalid
 */

#include <stdio.h>
#include "machine.h"

#define NUM_INSTRS 5

int main() {
  int retval;
  Instr instr[]= {
    { LI, 0x0001, 1, 2, 3 },
    { LI, 0x0002, 2, 1, 2 },
    { ADD, 0x3fff, 3, 1, 2 },
    { WRITE_CHAR + 12, 0x3fff, 37, 42, 55 },
    { HALT, 0, 0, 0, 0 }
  };

  retval= disassemble(instr, NUM_INSTRS);
  if (retval != 0) {
    printf("disassemble() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
