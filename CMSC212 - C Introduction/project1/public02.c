/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #2, public02.c
 * Ensures disassemble() functions properly when given a NULL pointer
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  
  retval= disassemble(NULL, 1);
  if (retval != 0) {
    printf("disassemble() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
