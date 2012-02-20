/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #3, public03.c
 * Ensures relocate_program() functions properly when given a NULL pointer
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  
  retval= relocate_program(NULL, NULL, 1, 4);
  if (retval != 0) {
    printf("relocate_program() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
