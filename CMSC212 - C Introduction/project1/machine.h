typedef unsigned int Memory_word;
typedef unsigned int CPU_register;

typedef enum { HALT, ADD, SUB, MUL, DIV, NEG, ANDB, ORB, XORB,
	       ANDL, ORL, NOTL, MOVE, LI, LW, SW, BLT, JR,
               READ_INT, WRITE_INT, READ_CHAR, WRITE_CHAR } Op_code;

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
