#if !defined(INTERPRETER_H)
#define INTERPRETER_H

typedef unsigned int Memory_word;
typedef unsigned int CPU_register;
typedef int Int_register;
typedef float Float_register;

typedef enum { HALT, ADD, SUB, MUL, DIV, NEG, ANDB, ORB, XORB,
	       ANDL, ORL, NOTL, MOVE, LI, LW, SW, BLT, JR,
               READ_INT, WRITE_INT, READ_CHAR, WRITE_CHAR,
               FADD, FSUB, FMUL, FDIV, READ_FLOAT, WRITE_FLOAT } Op_code;

typedef struct {
  Op_code operation;
  int addr_or_const;
  CPU_register reg1;
  CPU_register reg2;
  CPU_register reg3;
} Instr;

int print_instruction(Instr instr);
int decode_instruction(const Memory_word memory, Instr *instr_ptr);
int disassemble(const Instr program[], int num_elements);
int relocate_program(const Memory_word old_program[],
                     Memory_word new_program[], int num_elements, int offset);

typedef enum { RUNNING, FINISHED, BREAKPOINT, ERRINVINSTR, ERRINVADDR,
               ERRFPE } State;

State run(Memory_word memory[], Int_register registers[],
	  Float_register fregisters[], int stop_addr, int max_instr);
void debug(Memory_word memory[], int start_addr);

#endif
