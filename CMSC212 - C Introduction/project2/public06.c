#include <stdio.h>
#include "assembler.h"
#include "interpreter.h"

#define MEMORY_SIZE 2048
#define NUM_REGISTERS 16
#define BYTES_PER_WORD 4

/**
 * CMSC 212, 2008 Fall, Project #2
 * Public Test #6, public06.c
 * Tests loading and saving of words from memory.
 */

void check_memory(Memory_word memory[], int start_address);

int main() {
  Memory_word program[MEMORY_SIZE]= {0};
  Int_register reg[NUM_REGISTERS]= {0};
  Float_register freg[NUM_REGISTERS]= {0.0};
  char *filename= "public06.a";
  int num_instructions;
  State status;
  int q;

  num_instructions= assemble(filename, program, 0);

  if (num_instructions == 0)
    printf("Couldn't assemble \"%s\", exiting.\n", filename);
  else {

    status= run(program, reg, freg, -1, -1);

    if (status != FINISHED)
      printf("\nError - run() returned status %d.\n", status);
    else {
      printf("Integer Registers:\n");
      for (q= 0; q < NUM_REGISTERS; q++)
        printf("Register R%02d: %d\n", q, reg[q]);
      printf("\n");
      printf("Float Registers:\n");
      for (q= 0; q < NUM_REGISTERS; q++)
        printf("Register F%02d: %f\n", q, freg[q]);
      printf("\n");
      printf("Memory:\n");
      check_memory(program, (num_instructions + 1) * BYTES_PER_WORD);
    }
  }

  return 0;
}

/** Checks the higher memory addresses (addresses > start_address) to make sure
 * they're all still 0, the program shouldn't have modified them from 0.
 * Explicitly print out the lower values.
 */
void check_memory(Memory_word memory[], int start_address) {
  int q;

  for (q= 0; q < start_address; q += 4)
    printf("0x%04x: 0x%08x\n", q, memory[q / 4]);

  for (q= start_address; q < MEMORY_SIZE; q +=4)
    if (memory[q] != 0)
      printf("Memory address 0x%08x is nonzero, should be 0.\n", q);
}
