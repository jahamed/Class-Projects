/**
 * CMSC 212, 2008 Fall, Project #1
 * Secret Test #12, secret12.c
 * Calls relocate_program() with a program that contains li, sw, lw, and blt
 *   instructions that result in misaligned memory locations
 */

#include <stdio.h>
#include "machine.h"

#define PROG_LEN (sizeof(program1) / sizeof(Memory_word))

int main() {
  int retval;
  Memory_word program1[]= { 0x34050a78, 0x380543f8, 0x3c0ec75a, 0x400f0747 };
  Memory_word program2[PROG_LEN];

  retval= relocate_program(program1, program2, PROG_LEN, 0x0005);
  if (retval != 0) {
    printf("relocate_program() returned %d!\n", retval);
    printf("Test failed\n");
  }

  printf("Test finished!\n");
  return 0;
}
