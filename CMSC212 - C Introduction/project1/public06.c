/**
 * CMSC 212, 2008 Fall, Project #1
 * Public Test #6, public06.c
 * Checks if decode_instruction() decodes a valid instruction properly
 */

#include <stdio.h>
#include "machine.h"

int main() {
  int retval;
  Instr instr;
  
  retval= decode_instruction(0x045f4ab9, &instr);
  if (retval != 1) {
    printf("decode_instruction() returned %d!\n", retval);
    printf("Test failed\n");
    return -1;
  }
  if (instr.operation != 1 || instr.addr_or_const != 0x5f4 ||
      instr.reg1 != 0xa || instr.reg2 != 0xb || instr.reg3 != 0x9)
  {
    printf("Incorrect decoding of instruction.\n");
    printf("  Operation:  %d\n", instr.operation);
    printf("  Addr/Const: %x\n", instr.addr_or_const);
    printf("  Register 1: %d\n", instr.reg1);
    printf("  Register 2: %d\n", instr.reg2);
    printf("  Register 3: %d\n", instr.reg3);
    printf("Test failed\n");
    return -1;
  }

  printf("Test finished!\n");
  return 0;
}
