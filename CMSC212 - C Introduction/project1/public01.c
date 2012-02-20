/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #1, public01.c
 * Ensures decode_instruction() functions properly when given a NULL pointer
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  
  retval= decode_instruction(0x045f4ab9, NULL);
  if (retval != 0) {
    printf("decode_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
