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
	
	This program was expanded to give a run method which interprets RISK 
	instructions and actually implements the instructions, manipulating memory
	and registers. This program also now contains a simple debug function
	to help debug RISK programs in a method similar to gdb.
	
	This program makes use of almost everything we have learned in class so far,
	including if,switch,includes,structures,pointers,bit shifts,etc.
*/

/*“I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment.”*/

#include <stdio.h>
#include "interpreter.h"
#include "assembler.h"

int validate(Instr *ptr_struct);

/*This function assuming instr is a valid parameter prints the instructions
components on a single line. It has been modified from project 1 to handle
floating point numbers*/

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
				printf("add R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				/*was invalid*/
				return 0;
			}
			break;
		case SUB:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("sub R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case MUL:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("mul R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case DIV:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("div R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
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
				printf("andb R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case ORB:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("orb R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case XORB:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("xorb R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case ANDL:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("andl R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case ORL:
			if((instr.reg1>0&&instr.reg1<15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("orl R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
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
			if((instr.reg1>=0&&instr.reg1<=15)
			&&(instr.reg2>=0&&instr.reg2<=15)){
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
		case FADD:
			if((instr.reg1>=0&&instr.reg1<=15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("fadd R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case FSUB:
			if((instr.reg1>=0&&instr.reg1<=15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("fsub R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case FMUL:
			if((instr.reg1>=0&&instr.reg1<=15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("fmul R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case FDIV:
			if((instr.reg1>=0&&instr.reg1<=15)&&(instr.reg2>=0&&instr.reg2<=15)
			&&(instr.reg3>=0&&instr.reg3<=15)){
				printf("fdiv R%02d R%02d R%02d",instr.reg1,instr.reg2,
				instr.reg3);
				return 1;
			}else{
				return 0;
			}
			break;
		case READ_FLOAT:
			if(instr.reg1>=0&&instr.reg1<=15){
				printf("read_float R%02d",instr.reg1);
				return 1;
			}else{
				return 0;
			}
			break;
		case WRITE_FLOAT:
			if(instr.reg1>=0&&instr.reg1<=15){
				printf("write_float R%02d",instr.reg1);
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


/*This function helps validate instructions that would be passed to the RISK
interpreter*/

int validate(Instr *ptr_struct){

	switch (ptr_struct->operation){ 
		case HALT:
			/*nothing necessary to validate*/
			return 1;
			break;
		case ADD:
			/*Checking if Register 1 is 0 or 15 or if R1,R2,R3 out of bounds*/
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				/*was invalid*/
				return 0;
			}
			break;
		case SUB:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case MUL:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case DIV:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case NEG:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case ANDB:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case ORB:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case XORB:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case ANDL:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case ORL:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case NOTL:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case MOVE:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case LI:
			if(ptr_struct->reg1>0&&ptr_struct->reg1<15){
				return 1;
			}else{
				return 0;
			}		
			break;
		case LW:
			if((ptr_struct->reg1>0&&ptr_struct->reg1<15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case SW:
			if((ptr_struct->reg1>=0&&ptr_struct->reg1<=15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case BLT:
			if((ptr_struct->reg1>=0&&ptr_struct->reg1<=15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)){
				return 1;
			}else{
				return 0;
			}
			break;
		case JR:
			if(ptr_struct->reg1>=0&&ptr_struct->reg1<=15){
				return 1;
			}else{
				return 0;
			}
			break;
		case READ_INT:
			if(ptr_struct->reg1>0&&ptr_struct->reg1<15){
				return 1;
			}else{
				return 0;
			}
			break;
		case WRITE_INT:
			if(ptr_struct->reg1>=0&&ptr_struct->reg1<=15){
				return 1;
			}else{
				return 0;
			}
			break;
		case READ_CHAR:
			if(ptr_struct->reg1>0&&ptr_struct->reg1<15){
				return 1;
			}else{
				return 0;
			}
			break;
		case WRITE_CHAR:
			if(ptr_struct->reg1>=0&&ptr_struct->reg1<=15){
				return 1;
			}else{
				return 0;
			}
			break;
		case FADD:
			if((ptr_struct->reg1>=0&&ptr_struct->reg1<=15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				/*was invalid*/
				return 0;
			}
			break;
		case FSUB:
			if((ptr_struct->reg1>=0&&ptr_struct->reg1<=15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				/*was invalid*/
				return 0;
			}
			break;
		case FMUL:
			if((ptr_struct->reg1>=0&&ptr_struct->reg1<=15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				/*was invalid*/
				return 0;
			}
			break;
		case FDIV:
			if((ptr_struct->reg1>=0&&ptr_struct->reg1<=15)
			&&(ptr_struct->reg2>=0&&ptr_struct->reg2<=15)
			&&(ptr_struct->reg3>=0&&ptr_struct->reg3<=15)){
				return 1;
			}else{
				/*was invalid*/
				return 0;
			}
			break;
		case READ_FLOAT:
			if(ptr_struct->reg1>=0&&ptr_struct->reg1<=15){
				return 1;
			}else{
				return 0;
			}
			break;
		case WRITE_FLOAT:
			if(ptr_struct->reg1>=0&&ptr_struct->reg1<=15){
				return 1;
			}else{
				return 0;
			}
			break;				
		default:
			/*means it had invalid opcode. this should not happen however...*/
			return 0; 
		break;
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



/*This function acts as an interpreter for RISK machine language programs, 
modeling registers and memory in the computer to simulate operations symbolized 
by all the available opcodes. It returns appropriate states and errors, such as 
when operations are invalid or there are invalid memory addresses being 
accessed*/
	
State run(Memory_word memory[], Int_register registers[],
	  Float_register fregisters[], int stop_addr, int max_instr){
	  

	float float_input;
	char char_input;
	int int_input;
	int instructions_completed=0;
	Instr decoded_struct, *ptr_struct;
	ptr_struct=&decoded_struct;
	
	  
	/*This case checks if stop_addr was 0 to begin with*/  
	if(stop_addr>=0&&stop_addr==registers[15]){
		return BREAKPOINT;
	} 
	  
	/*This case checks if max_instr was 0 to begin with*/
	if(max_instr==0 && instructions_completed==0){
		return RUNNING;
	}
	
	while(registers[15]<8192&&registers[15]>=0){	

		/*checking for breakpoint*/		
		if(stop_addr>=0&&stop_addr==registers[15]){
			return BREAKPOINT;
		}
					
		decode_instruction(memory[registers[15]/4],ptr_struct); 

		switch (ptr_struct->operation){ 
			case HALT:
				return FINISHED;
				break;	
			case ADD:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					+registers[ptr_struct->reg3];
				}else{
					/*validate failed to validate integrity of instruction*/
					return ERRINVINSTR;
				}
				break;
			case SUB:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					-registers[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case MUL:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					*registers[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case DIV:
				if(validate(ptr_struct)){
					if(ptr_struct->reg3==0){
						return ERRFPE;
					}
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					/registers[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case NEG:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=(registers[ptr_struct->reg2]
					*-1);
				}else{
					return ERRINVINSTR;
				}
				break;
			case ANDB:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					&registers[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}				
				break;
			case ORB:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					|registers[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case XORB:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					^registers[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case ANDL:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					&&registers[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case ORL:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2]
					||registers[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case NOTL:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=!(registers[ptr_struct->reg2]);
				}else{
					return ERRINVINSTR;
				}
				break;
			case MOVE:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=registers[ptr_struct->reg2];
				}else{
					return ERRINVINSTR;
				}
				break;
			case LI:
				if(validate(ptr_struct)){
					registers[ptr_struct->reg1]=ptr_struct->addr_or_const;
				}else{
					return ERRINVINSTR;
				}
				break;
			case LW:
				if(validate(ptr_struct)){
					if(ptr_struct->addr_or_const+registers[ptr_struct->reg2]
					>=8192
					||(ptr_struct->addr_or_const+registers[ptr_struct->reg2])<0
					||(ptr_struct->addr_or_const+registers[ptr_struct->reg2])
					%4!=0){
						return ERRINVADDR;
					}
					registers[ptr_struct->reg1]=
					memory[((ptr_struct->addr_or_const)+(ptr_struct->reg2))/4];
				}else{
					return ERRINVINSTR;
				}
				break;
			case SW:
				if(validate(ptr_struct)){
					if(ptr_struct->addr_or_const+registers[ptr_struct->reg2]
					>=8192
					||(ptr_struct->addr_or_const+registers[ptr_struct->reg2])<0
					||(ptr_struct->addr_or_const+registers[ptr_struct->reg2])
					%4!=0){
						return ERRINVADDR;
					}
					memory[((ptr_struct->addr_or_const)+(ptr_struct->reg2))/4]=
					registers[ptr_struct->reg1];
				}else{
					return ERRINVINSTR;
				}
				break;
			case BLT:
				/*if register 1 is less than register 2, do BLT reg 15 jump*/
				if(validate(ptr_struct)){					
					if(registers[ptr_struct->reg1]<registers[ptr_struct->reg2]){
						if(ptr_struct->addr_or_const>=8192
						||(ptr_struct->addr_or_const)<0
						||(ptr_struct->addr_or_const)%4!=0){
							return ERRINVADDR;
						}
						/*the -4 is to offset the +4 at the end of the loop*/
						registers[15]=((ptr_struct->addr_or_const)-4);
					}		
				}else{
					return ERRINVINSTR;
				}
				break;
			case JR:
				if(validate(ptr_struct)){
					registers[15]=((registers[ptr_struct->reg1])-4);
				}else{
					return ERRINVINSTR;
				}
				break;
			case READ_INT:
				if(validate(ptr_struct)){
					scanf("%d",&int_input);
					registers[ptr_struct->reg1]=int_input;
				}else{
					return ERRINVINSTR;
				}
				break;
			case WRITE_INT:
				if(validate(ptr_struct)){
					printf("%d",registers[ptr_struct->reg1]);
				}else{
					return ERRINVINSTR;
				}
				break;
			case READ_CHAR:
				if(validate(ptr_struct)){
					scanf("%c",&char_input);
					registers[ptr_struct->reg1]=char_input;
				}else{
					return ERRINVINSTR;
				}	
				break;
			case WRITE_CHAR:
				if(validate(ptr_struct)){
					printf("%c",registers[ptr_struct->reg1]);
				}else{
					return ERRINVINSTR;
				}
				break;
			case FADD:
				if(validate(ptr_struct)){
					fregisters[ptr_struct->reg1]=fregisters[ptr_struct->reg2]
					+fregisters[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case FSUB:
				if(validate(ptr_struct)){
					fregisters[ptr_struct->reg1]=fregisters[ptr_struct->reg2]
					-fregisters[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case FMUL:
				if(validate(ptr_struct)){
					fregisters[ptr_struct->reg1]=fregisters[ptr_struct->reg2]
					*fregisters[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case FDIV:
				if(validate(ptr_struct)){
					if(ptr_struct->reg3==0){
						return ERRFPE;
					}
					fregisters[ptr_struct->reg1]=fregisters[ptr_struct->reg2]
					/fregisters[ptr_struct->reg3];
				}else{
					return ERRINVINSTR;
				}
				break;
			case READ_FLOAT:
				if(validate(ptr_struct)){
					scanf("%f",&float_input);
					fregisters[ptr_struct->reg1]=float_input;
				}else{
					return ERRINVINSTR;
				}
				break;
			case WRITE_FLOAT:
				if(validate(ptr_struct)){
					printf("%f",fregisters[ptr_struct->reg1]);
				}else{
					return ERRINVINSTR;
				}
				break;
		}
			
		instructions_completed++;
		/*increment the program counter by a word*/
		registers[15]+=4;
		
		/*returns breakpoint if stop_addr equals current r[15]*/
		if(stop_addr>=0&&stop_addr==registers[15]){
			return BREAKPOINT;
		}
		
		/*returns running when instructions completed is equal to max_instr*/
		if(max_instr>0 && max_instr==instructions_completed){
			return RUNNING;
		}	
	}
	/*if the program counter is invalid return invalid memory address*/
	return ERRINVADDR;
}


/*this function implements a simple debugger for RISK programs by emulating a 
Risk computer with registers, fregisters, memory, and simple debugging commands.
Its functionality is quite similar to gdb*/

void debug(Memory_word memory[], int start_addr){
	
	int command_restricted=0;
	int i, j, regnum;
	int max_instr=-1;
	int stop_addr=-1;
	int valid_answer=0;
	char command, regchar;
	unsigned int mem_address;
	Int_register registers[16]={0};
	Float_register fregisters[16]={0};
	Memory_word memory_copy[2048];
	State run_state;
	Instr dummy; 
	Instr *dummy_ptr=&dummy;
	  
	/*this is making a copy of the memory array as debug may call run multiple 
	times*/
	for (i=0; i<2048; i++){
    	memory_copy[i]=memory[i];
	}
	
	/*The loop will continue until the debugger is quit*/
	while(1){
		decode_instruction(memory_copy[registers[15]/4], dummy_ptr);
		printf("%04x: ", registers[15]);
		printf("(");
		print_instruction(*dummy_ptr);
		printf("):\t");
	
		while(!valid_answer){	
			scanf(" %c", &command);
			if(command=='m'||command=='b'){
				scanf("%x", &mem_address);
				valid_answer=1;
				if(mem_address>=8192||mem_address<0||mem_address%4!=0){
					valid_answer=0;
					printf("Error: illegal argument.");
				}
			}else if(command=='p'){
				scanf("%c%d",&regchar,&regnum);
				valid_answer=1;
				if((regchar!='R'&&regchar!='F')||regnum>15||regnum<0){
					valid_answer=0;
					printf("Error: illegal argument.");
				}
			}else if(command=='u'||command=='r'||command=='c'||command=='s'
			||command=='q'){
				/*Do nothing*/
				valid_answer=1;
			}else{
				printf("Error: illegal command.");
				valid_answer=0;
			}
		}
		valid_answer=0;
		
		switch(command){
			case 'm':
				printf("%08x", memory_copy[(mem_address)/4]);
				break;
			case 'p':
				if(regchar=='R'){
					printf("%d", registers[regnum]);
				}else if(regchar=='F'){
					printf("%f", fregisters[regnum]);
				}
				break;
			case 'b':
				stop_addr=mem_address;
				break; 
			case 'u':
				stop_addr=-1;
				break;
			case 'r':
				for (i=0; i<2048; i++){
					memory_copy[i]=memory[i];
				}
		
				/*this is reinit. the registers and fregisters elements to 0*/
				for (j=0;j<16;j++){
					registers[j]=0;
					fregisters[j]=0;
				}
				
				registers[15]=start_addr;
				run_state = run(memory_copy, registers, fregisters, stop_addr, 
				max_instr);
				
				/*This checks run's return state to error conditions, putting 
				restrictions on command c and s if necessary*/
				if(run_state==ERRINVINSTR||run_state==ERRINVADDR
				||run_state==ERRFPE){
					printf("Error: program failed.");
					command_restricted=1;
				}else if(run_state==FINISHED){
					command_restricted=1;
				}else{
					command_restricted=0;
				}
				break;
			case 'c':
				if(!command_restricted){			
					run(memory_copy, registers, fregisters, stop_addr,
					max_instr);
				}else{
					printf("Error: the program is not being run.");
				}
				break;
			case 's':
				if(!command_restricted){
					run(memory_copy, registers, fregisters, stop_addr, 1);
				}else{
					printf("Error: the program is not being run.");
				}
				break;
			case 'q':
				printf("\n");
				return;
				break;
		}
	printf("\n");
	}
}	
