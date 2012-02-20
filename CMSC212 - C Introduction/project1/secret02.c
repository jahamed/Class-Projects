/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #2, secret02.c
 * Tests relocate_program() with a 2048-word program and a 2049-word program
 */

#include <stdio.h>
#include "machine.h"

#define NUM_WORDS 3000

int main() {
  int retval;
  Memory_word words1[NUM_WORDS], words2[NUM_WORDS];
  int i;

  for (i= 0; i < NUM_WORDS; i++)
    words1[i]= 0x00000000;

  retval= relocate_program(words1, words2, 2048, 4);
  if (retval != 1) {
    printf("relocate_program() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }
  
  retval= relocate_program(words1, words2, 2049, 4);
  if (retval != 0) {
    printf("relocate_program() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
