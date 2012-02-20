/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #5, public05.c
 * Ensures relocate_program() functions properly when given a negative number
 *   of elements
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Memory_word one[5], two[5];
  
  retval= relocate_program(one, two, -5, 4);
  if (retval != 0) {
    printf("relocate_program() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
