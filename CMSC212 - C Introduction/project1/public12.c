/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #12, public12.c
 * Checks disassemble() with a small program and uses decode_instruction()
 *   to decode each instruction
 */

#include <stdio.h>
#include "machine.h"

#define NUM_INSTRS 4

int main() {
  int retval;
  Memory_word words[NUM_INSTRS]= {
    0x340011e9, 0x07cab212, 0x06fee112, 0x03bead88
  };
  Instr program[NUM_INSTRS];
  int i;
  
  for (i= 0; i < NUM_INSTRS; i++) {
    retval= decode_instruction(words[i], program + i);
    if (retval != 1) {
      printf("decode_instruction() returned %d!\n", retval);
      printf("Test failed\n");
      return -1;
    }
  }
  
  retval= disassemble(program, NUM_INSTRS);
  if (retval != 1) {
    printf("disassemble() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
