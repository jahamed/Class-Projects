/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #13, public13.c
 * Checks relocate_program() with a small program that contains some
 *   instructions that use the memory address field
 */

#include <stdio.h>
#include "machine.h"

#define NUM_INSTRS 10
#define NUM_USED    7

int main() {
  int retval;
  Memory_word words1[NUM_INSTRS]= {
    0x342121ab, 0x3c5f4122, 0x343271f9, 0x385f42e7, 0x0777e312,
    0x4d112358, 0x01132134, 0x8cd4ffe3, 0xecb04806, 0xaa40c348
  };
  Memory_word words2[NUM_INSTRS];
  int i;
  
  retval= relocate_program(words1, words2, NUM_USED, 0x514);
  if (retval != 1) {
    printf("relocate_program() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }
  for (i= 0; i < NUM_USED; i++) {
    if (words1[i] != words2[i]){     
      printf("Instruction %d relocated (%x => %x)\n", i, words1[i], words2[i]);
  	}
  }

  printf("Test finished!\n");
  return 0;
}
