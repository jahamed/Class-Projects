/**
* CMSC 212, 2008 Fall, Project #1
* All Public Tests in one file.
*/

#include <stdio.h>
#include "machine.h"

#define NUM_INSTRS 4
#define NUM_INSTRS2 10
#define NUM_USED    7
#define NUM_USED2    9

int main()
{
	int retval;
	Instr instr ;
	Memory_word one[5], two[5];
	Instr instr0 = {HALT, 0, 0, 0, 0};
	Instr instr1 = {ADD, 0, 3, 5, 9};
	Instr instr3 = {HALT, 0x3678, 15, 2, 10};
	Instr instr4 = {LW, 0x538, 1, 12, 10};
	Memory_word words[NUM_INSTRS] = {
	                                    0x340011e9, 0x07cab212, 0x06fee112, 0x03bead88
	                                };
	Instr program[NUM_INSTRS2];
	Memory_word words1[NUM_INSTRS2] = {
	                                      0x342121ab, 0x3c5f4122, 0x343271f9, 0x385f42e7, 0x0777e312,
	                                      0x4d112358, 0x01132134, 0x8cd4ffe3, 0xecb04806, 0xaa40c348
	                                  };
	Memory_word words2[NUM_INSTRS2];
	Memory_word words3[NUM_INSTRS2] = {
	                                      0x342121ab, 0x3c5f4122, 0x343271f9, 0x385f42e7, 0x0777e312,
	                                      0x4d112358, 0x3400a4bc, 0x54eee421, 0x01132134, 0x8cd4ffe3
	                                  };
	Memory_word words4[NUM_INSTRS2];
	int i;


	/* Ensures decode_instruction() functions properly when given a NULL pointer */
	retval = decode_instruction(0x045f4ab9, NULL);
	if (retval != 0)
	{
		printf("decode_instruction() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");

	
	/*  Ensures disassemble() functions properly when given a NULL pointer */
	retval = disassemble(NULL, 1);
	if (retval != 0)
	{
		printf("disassemble() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");

	/* Ensures relocate_program() functions properly when given a NULL pointer */
	retval = relocate_program(NULL, NULL, 1, 4);
	if (retval != 0)
	{
		printf("relocate_program() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");


	/* Ensures disassemble() functions properly when given a negative number */
	retval = disassemble(program, -5);
	if (retval != 0)
	{
		printf("disassemble() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");


	/* Ensures relocate_program() functions properly when given a negative number   of elements */
	retval = relocate_program(one, two, -5, 4);
	if (retval != 0)
	{
		printf("relocate_program() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");


	/* Checks if decode_instruction() decodes a valid instruction properly */
	retval = decode_instruction(0x045f4ab9, &instr);
	if (retval != 1)
	{
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

	
	/* Checks if decode_instruction() decodes an invalid instruction properly */
	retval = decode_instruction(0xdeadbeef, &instr);
	if (retval != 1)
	{
		printf("decode_instruction() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	if (instr.operation != 55 || instr.addr_or_const != 0x2adb ||
	        instr.reg1 != 0xe || instr.reg2 != 0xe || instr.reg3 != 0xf)
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


	/* Checks if print_instruction() handles a simple instruction properly */
	retval = print_instruction(instr0);
	printf("\n");
	if (retval != 1)
	{
		printf("print_instruction() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");

	
	/* Checks if print_instruction() handles an add instruction properly */
	retval = print_instruction(instr1);
	printf("\n");
	if (retval != 1)
	{
		printf("print_instruction() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");


	/* Checks if print_instruction() handles a halt instruction properly
	*  even though it has some invalid data (which is unused by halt) */
	retval = print_instruction(instr3);
	printf("\n");
	if (retval != 1)
	{
		printf("print_instruction() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");

	
	/* Checks if print_instruction() handles an lw instruction properly */
	retval = print_instruction(instr4);
	printf("\n");
	if (retval != 1)
	{
		printf("print_instruction() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	printf("Test finished!\n");

	
	/* Checks disassemble() with a small program and uses decode_instruction()
	   to decode each instruction */
	for (i = 0; i < NUM_INSTRS; i++)
	{
		retval = decode_instruction(words[i], program + i);
		if (retval != 1)
		{
			printf("decode_instruction() returned %d!\n", retval);
			printf("Test failed\n");
			return -1;
		}
	}

	retval = disassemble(program, NUM_INSTRS);
	if (retval != 1)
	{
		printf("disassemble() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}

	printf("Test finished!\n");


	/* Checks relocate_program() with a small program that contains some
	*  instructions that use the memory address field */
	retval = relocate_program(words1, words2, NUM_USED, 0x514);
	if (retval != 1)
	{
		printf("relocate_program() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	for (i = 0; i < NUM_USED; i++)
	{
		if (words1[i] != words2[i])
			printf("Instruction %d relocated (%x => %x)\n", i, words1[i], words2[i]);
	}
	
	printf("Test finished!\n");


	/* Checks relocate_program() with a small program, decodes the resultant
	 *   program, and then uses disassemble() to print out the new program */
	retval = relocate_program(words3, words4, NUM_USED2, 0x514);
	if (retval != 1)
	{
		printf("relocate_program() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}
	for (i = 0; i < NUM_USED2; i++)
	{
		retval = decode_instruction(words4[i], program + i);
		if (retval != 1)
		{
			printf("decode_instruction() returned %d!\n", retval);
			printf("Test failed - word %d\n", i);
			return -1;
		}
	}
	retval = disassemble(program, NUM_USED2);
	if (retval != 1)
	{
		printf("disassemble() returned %d!\n", retval);
		printf("Test failed\n");
		return -1;
	}

	printf("Test finished!\n");


	return 0 ;
}
