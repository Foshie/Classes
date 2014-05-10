#include "machine.h"
#include <stdio.h>
/* Josh Fann
   Project 1
   CMSC212 0202
   2/24/10
*/

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7

/* Returns 0 when word_ptr is null or type is invalid.  Else return 1.
   If type is DATA, then contents is set to type parameter 
   and value is set to data_value.
   If type is INSTR, contents is set to type paramater
   values are set using other parameters given.
   Then return 1.
*/
int init_word(Word *const word_ptr, Word_type type, Op oper, short reg1,
              short reg2, short reg3, short addr, int immediate,
              int data_value){
  if(word_ptr == NULL || (type != INSTR && type != DATA))
    return 0;
  if(type == INSTR){
    word_ptr->contents = type;
    word_ptr->value.instr.op = oper;
    word_ptr->value.instr.r1 = reg1;
    word_ptr->value.instr.r2 = reg2;
    word_ptr->value.instr.r3 = reg3;
    word_ptr->value.instr.address = addr;
    word_ptr->value.instr.imm = immediate;
    return 1;
 }
  if(type == DATA){
    word_ptr->contents = type;
    word_ptr->value.data = data_value;
    return 1;
  }
  return 1;
}

/* Checks the operation at the memory address. 
   Prints corresponding output depending on operation
   I originally had it count from start to size but then realized it was wrong.
   So instead of setting i to 0, and going in to change all array indexes to i+start, I just got lazy and made the count go up to size + start
 */

/* Returns 0 when:
   1. The index starts/ends somewhere outside of the 128 memory addresses
   2. If the parameters have a negative value.
   Otherwise:
   Return 1 if size is 0.
   Or
   Print each of the elements of the memory array starting with the start index and ending at start+size-1 following given guidelines.
   Then return 1. 
*/
int print_program(const Word memory[], int start, int size){
  int i;
  if(start + size > 128 || start < 0 || size < 0){
    return 0;
  }
  if(!size){
    return 1;
  }

  for(i = start; i < size+start; i++){
    if(memory[i].contents == DATA){
      printf("%d: .data: %d\n", i, memory[i].value.data);
    }else{
      if(memory[i].value.instr.op == ADD){
	printf("%d: add R%d R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.r3);
      }else if(memory[i].value.instr.op == SUB){
	printf("%d: sub R%d R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.r3);
      }else if(memory[i].value.instr.op == MUL){
	printf("%d: mul R%d R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.r3);
      }else if(memory[i].value.instr.op == DIV){
	printf("%d: div R%d R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.r3);
      }else if(memory[i].value.instr.op == MOD){
	printf("%d: mod R%d R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.r3);
      }else if(memory[i].value.instr.op == AND){
	printf("%d: and R%d R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.r3);
      }else if(memory[i].value.instr.op == OR){
	printf("%d: or R%d R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.r3);
      }else if(memory[i].value.instr.op == XOR){
	printf("%d: xor R%d R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.r3);
      }else if(memory[i].value.instr.op == NOT){
	printf("%d: not R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2);
      }else if(memory[i].value.instr.op == NEG){ 
	printf("%d: neg R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2);
      }else if(memory[i].value.instr.op == INC){
	printf("%d: inc R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2);
      }else if(memory[i].value.instr.op == IO){
	printf("%d: io R%d R%d\n", i, memory[i].value.instr.r1,
	     memory[i].value.instr.r2);  
      }else if(memory[i].value.instr.op == MOVE){
	printf("%d: move R%d R%d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2);
      }else if(memory[i].value.instr.op == J){
	printf("%d: j %d\n", i,  memory[i].value.instr.address);
      }else if(memory[i].value.instr.op == JSR){
	printf("%d: jsr %d\n", i,  memory[i].value.instr.address);
      }else if(memory[i].value.instr.op == RTN){
	printf("%d: rtn\n", i);
      }else if(memory[i].value.instr.op == SW){
	printf("%d: sw R%d %d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.address);
      }else if(memory[i].value.instr.op == LW){
	printf("%d: lw R%d %d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.address);
      }else if(memory[i].value.instr.op == LI){
	printf("%d: li R%d %d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.imm);
      }else if(memory[i].value.instr.op == LO){
	printf("%d: lo R%d R%d %d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.address);
      }else if(memory[i].value.instr.op == BEQ){
	printf("%d: beq R%d R%d %d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.address);
      }else if(memory[i].value.instr.op == BNE){
	printf("%d: bne R%d R%d %d\n", i, memory[i].value.instr.r1,
	       memory[i].value.instr.r2, memory[i].value.instr.address);
      }else if(memory[i].value.instr.op == HALT){
	printf("%d: halt\n", i);
      }
    }
  }
  return 1;
}
/* Shifts location of memory from start index to new_start_loc index with the same size.
   Returns 0 if current memory[start] begins outside of array or ends outside of array.  Or if new start loc starts/ends outside of the array. 
   Returns 0 if int parameters are negative.
   returns 1 if size is 0.
   Returns 1 after cells are copied to new location.  Some overwriting may be doen.
*/

int shift_program(Word memory[], int start, int size, int new_start_loc){
  int index, new_end = new_start_loc + size;
  if(start + size > 127 || new_start_loc + size > 127){
    return 0;
  }
  if(start < 0 || size < 0 || new_start_loc < 0){
    return 0;
  }
  if(size == 0){
    return 1;
  }
/*
  for(index = 0; index < size; index++){
    memory[new_start_loc + index] = memory[start + index];
  }
*/
  if(new_start_loc < start){
    for(index = 0; index < size; index++){
      memory[new_start_loc + index] = memory[start + index];
    }
  }else{
    for(index = new_end - 1; index >= new_start_loc; index--){
      memory[index] = memory[index + start - new_start_loc];
    }
  }
  return 1;
}
