/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #14, public14.c
 * Checks relocate_program() with a small program, decodes the resultant
 *   program, and then uses disassemble() to print out the new program
 */

#include <stdio.h>
#include "machine.h"

#define NUM_INSTRS 10
#define NUM_USED    9

int main() {
  int retval;
  Memory_word words1[NUM_INSTRS]= {
    0x342121ab, 0x3c5f4122, 0x343271f9, 0x385f42e7, 0x0777e312,
    0x4d112358, 0x3400a4bc, 0x54eee421, 0x01132134, 0x8cd4ffe3
  };
  Memory_word words2[NUM_INSTRS];
  Instr instr[NUM_INSTRS];
  int i;
  
  retval= relocate_program(words1, words2, NUM_USED, 0x514);
  if (retval != 1) {
    printf("relocate_program() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }
  for (i= 0; i < NUM_USED; i++) {
    retval= decode_instruction(words2[i], instr + i);
    if (retval != 1) {
      printf("decode_instruction() returned %d!\n", retval);
      printf("Test failed - word %d\n", i);
      return -1;
    }
  }
  retval= disassemble(instr, NUM_USED);
  if (retval != 1) {
    printf("disassemble() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
