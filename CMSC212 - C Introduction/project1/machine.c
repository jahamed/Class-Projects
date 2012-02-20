/*
Name=Javed Ahamed
Glue Logon=jahamed
UID=109365000
Sec=0202
*/

/*
	The purpose of this program was to build functions for a RISK or Reduced 
	Instruction Set Komputer. This program implements methods that allow one to
	print instructions opcodes, registers, and memory/constants. It also allows 
	one to extract this prior information from a memory word and also implements
	a disassembler for the RISK architecture. The program also implements 
	a relocate function that allows one to offset the memory component of an
	instruction.
	
	This program makes use of almost everything we have learned in class so far,
	including if,switch,includes,structures,pointers,bit shifts,etc.
*/
/*“I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment.”*/

#include <stdio.h>
#include "machine.h"

/*This function assuming instr is a valid parameter prints the instructions
components on a single line*/

int print_instruction(Instr instr)
{ 
	/*Chooses which opcode to use*/
	switch (instr.operation){ 
		case HALT:
			printf("halt");
			return 1;
			break;
		case ADD:
			/*Checking if Register 1 is 0 or 15 or if R1,R2,R3 out of bounds*/
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("add R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
			/*was invalid*/
			return 0;
			}
			break;
		case SUB:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("sub R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case MUL:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("mul R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case DIV:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("div R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case NEG:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)){
				printf("neg R%02d R%02d",instr.reg1,instr.reg2);
				return 1;
			}else{
				return 0;
			}
			break;
		case ANDB:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("andb R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case ORB:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("orb R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case XORB:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("xorb R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case ANDL:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("andl R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case ORL:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("orl R%02d R%02d R%02d",instr.reg1,instr.reg2,instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case NOTL:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)){
				printf("notl R%02d R%02d",instr.reg1,instr.reg2);
				return 1;
			}else{
				return 0;
			}
			break;
		case MOVE:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)){
				printf("move R%02d R%02d",instr.reg1,instr.reg2);
				return 1;
			}else{
				return 0;
			}
			break;
		case LI:
			if(instr.reg1>0&&instr.reg1<15){
				printf("li R%02d %04x",instr.reg1,instr.addr_or_const);
				return 1;
			}else{
				return 0;
			}		
			break;
		case LW:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)){
				printf("lw R%02d R%02d %04x",instr.reg1,instr.reg2,
				instr.addr_or_const);
				return 1;
			}else{
				return 0;
			}
			break;
		case SW:
			if((instr.reg1>=0&&instr.reg1<=15)&&(instr.reg2>=0&&instr.reg2<=15)){
				printf("sw R%02d R%02d %04x",instr.reg1,instr.reg2,
				instr.addr_or_const);
				return 1;
			}else{
				return 0;
			}
			break;
		case BLT:
			if((instr.reg1>=0&&instr.reg1<=15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&instr.addr_or_const>=0&&instr.addr_or_const<8192
			&&instr.addr_or_const%4==0){
				printf("blt R%02d R%02d %04x",instr.reg1,instr.reg2,
				instr.addr_or_const);
				return 1;
			}else{
				return 0;
			}
			break;
		case JR:
			if(instr.reg1>=0&&instr.reg1<=15){
				printf("jr R%02d",instr.reg1);
				return 1;
			}else{
				return 0;
			}
			break;
		case READ_INT:
			if(instr.reg1>0&&instr.reg1<15){
				printf("read_int R%02d",instr.reg1);
				return 1;
			}else{
				return 0;
			}
			break;
		case WRITE_INT:
			if(instr.reg1>=0&&instr.reg1<=15){
				printf("write_int R%02d",instr.reg1);
				return 1;
			}else{
				return 0;
			}
			break;
		case READ_CHAR:
			if(instr.reg1>0&&instr.reg1<15){
				printf("read_char R%02d",instr.reg1);
				return 1;
			}else{
				return 0;
			}
			break;
		case WRITE_CHAR:
			if(instr.reg1>=0&&instr.reg1<=15){
				printf("write_char R%02d",instr.reg1);
				return 1;
			}else{
				return 0;
			}
			break;
		default:
			return 0; /*means it had invalid opcode*/
		break;
	}
}

/*This function uses the passed Memory_word to initialize the elements of the 
structure that the pointer parameter points to.*/
int decode_instruction(const Memory_word memory, Instr *instr_ptr){
	unsigned int opcode=0;
	unsigned int memory_or_constant=0;
	unsigned int r1=0;
	unsigned int r2=0;
	unsigned int r3=0;
	
	/*checks if pointer is null*/
	if(instr_ptr==0){
		return 0;
	}else{
	/*using bit shifts to isolate parts of the Memory_word*/
		r3=(memory<<28)>>28;
		r2=(memory<<24)>>28;
		r1=(memory<<20)>>28;
		memory_or_constant=(memory<<6)>>18;
		opcode=(memory>>26);
		
		/*assigns parts of the structures to values we just computed*/
		instr_ptr->operation=opcode;
		instr_ptr->addr_or_const=memory_or_constant;
		instr_ptr->reg1=r1;
		instr_ptr->reg2=r2;
		instr_ptr->reg3=r3;
		
		return 1;
	}
}

/*This function loops through the program array, and prints valid instructions
from the structure fields*/

int disassemble(const Instr program[], int num_elements){
	int i=0;
	/*testing if program is null, or if num_elements is invalid*/
	if(program==0||num_elements<0||num_elements>2048){
		return 0;
	}else{
		for(i=0;i<num_elements;i++){
			/*if the instruction was invalid calc. in print_instruction*/
			if(print_instruction(program[i])==0){
				return 0;
			}
			printf("\n");
		}
		return 1;
	}
}

/*this function copies all elements from old program to new program defined
by num_elements, and for every instruction that uses a memory address in the 14
bit field, it increments this memory address by the offset before copying it to 
new array*/
int relocate_program(const Memory_word old_program[],
                     Memory_word new_program[], int num_elements, int offset){
 	int i=0;
 	unsigned int opcode=0;
 	unsigned int memory_temp, r1, r2, r3;
 	/*testing to see if num elements is invalid or if either array 
 	is set to null*/
	if(num_elements<0||num_elements>2048||old_program==0||new_program==0){
		return 0;
	}
	
	for(i=0;i<num_elements;i++){ 
		/*calculating opcode to see which case we should follow*/
		opcode=old_program[i]>>26;
		switch(opcode){
			case 14: /*lw*/
				/*calculating individual parts of the memoryword now*/
				memory_temp=((old_program[i]<<6>>18))+offset;
				r3=(old_program[i]<<28)>>28;
				r2=(old_program[i]<<24)>>28;
				r1=(old_program[i]<<20)>>28;
				/*testing to see if rellocated memory addr. is too large to fit 
				in 14 bits*/
				if(memory_temp>16383){
					return 0;
				}
				/*setting the modified version of new program*/
				new_program[i]=((opcode<<26)|(memory_temp<<12))|(r1<<8)|(r2<<4)|
				(r3);
			break;
			case 15: /*sw*/
				memory_temp=((old_program[i]<<6>>18))+offset;
				r3=(old_program[i]<<28)>>28;
				r2=(old_program[i]<<24)>>28;
				r1=(old_program[i]<<20)>>28;
				if(memory_temp>16383){
					return 0;
				}
					new_program[i]=((opcode<<26)|(memory_temp<<12))|(r1<<8)|
					(r2<<4)|(r3);
			break;
			case 16: /*blt*/
				memory_temp=((old_program[i]<<6)>>18)+offset;
				r3=(old_program[i]<<28)>>28;
				r2=(old_program[i]<<24)>>28;
				r1=(old_program[i]<<20)>>28;
				/*testing to see if above memory or if not divisible by 4*/
				if(memory_temp>8192||memory_temp%4!=0){
					return 0;
				}
				new_program[i]=((opcode<<26)|(memory_temp<<12))|(r1<<8)|(r2<<4)
				|(r3);
			break;
			default:
			/*use this when not lw,sw,blt*/
				new_program[i]=old_program[i];
			break;
		}
	}	
	return 1;                 
}

