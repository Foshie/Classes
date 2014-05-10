#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7

typedef enum { ADD, SUB, MUL, DIV, MOD, AND, OR, XOR, NOT, NEG, INC,
               IO, MOVE, J, JSR, RTN, SW, LW, LI, LO, BEQ, BNE, HALT } Op;

typedef struct {
  Op op;
  short r1;
  short r2;
  short r3;
  short address;
  int imm;
} Instruction;

typedef enum { INSTR, DATA } Word_type;

typedef struct {
  Word_type contents;
  union {
    Instruction instr;
    int data;
  } value;
} Word;

int init_word(Word *const word_ptr, Word_type type, Op oper, short reg1,
              short reg2, short reg3, short addr, int immediate,
              int data_value);
int print_program(const Word memory[], int start, int size);
int shift_program(Word memory[], int start, int size, int new_start_loc);
