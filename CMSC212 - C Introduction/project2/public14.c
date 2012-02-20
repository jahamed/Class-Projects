#include <stdio.h>
#include "assembler.h"
#include "interpreter.h"

#define MEMORY_SIZE 2048
#define NUM_REGISTERS 16
#define BYTES_PER_WORD 4

/**
 * CMSC 212, 2008 Fall, Project #2
 * Public Test #13, public13.c
 * Tests proper behavior of single-stepping in debug() ('s').
 */

int debug_code(const char *filename);

int main() {
  debug_code("public14.a");
  return 0;
}

int debug_code(const char *filename) {
  Memory_word program[MEMORY_SIZE]= {0};
  int num_instructions;

  num_instructions= assemble(filename, program, 0);

  if (num_instructions == 0)
    printf("Couldn't assemble \"%s\", exiting.\n", filename);
  else {
    debug(program, 0);
    printf("Debugger exited normally.\n");
  }

  return 0;
}
