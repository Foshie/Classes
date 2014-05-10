#include "machine.h"
#include <stdio.h>
/* Josh Fann
   Project 1
   CMSC212 0202
   2/24/10
*/

/*Following symbolic constants are for bit masking.*/
#define instruct 0xF800
#define reg1 0x0700
#define reg2 0x0070
#define reg3 0x0007
#define reg_ia 0x00FF /*Used for sw, lw, li, and j, jsr)*/
#define reg_2d 0x00E0 /*Used for two register and address 
			instructions(lo, beq, and bne) to find R2.  
			Different from previous R2*/
#define reg_ad 0x001F /*Used for two register and addresss 
			instructions (lo, beq, and bne)*/

/* get_bit() returns the int in the memory address that user is asking for.
   Most called will be expected to match the symbolic constants defined earlier.
*/
int get_bit(Mem memory, int  mask){
  int to_return = memory & mask;
  if(mask == instruct){
    to_return = to_return >> 11;
  }
  else if(mask == reg1){
    to_return = to_return >> 8;
  }
  else if(mask == reg2){
  to_return = to_return >> 4;
    /*no need to worry if mask == reg3 || mask == reg_ia || mask == reg_ad ,
      already at right most position*/
  }
  else if(mask == reg_2d){
    to_return = to_return >> 5;
  }
  return to_return;
}


/* Returns 0 when word_ptr is null or type is invalid.  Else return 1.
   If type is DATA, then contents is set to type parameter 
   and value is set to data_value.
   If type is INSTR, contents is set to type paramater
   values are set using other parameters given.
   Then return 1.
*/
int init_word(Word *const word_ptr, Word_type type, Op oper, short reg_1, 
	      short reg_2, short reg_3, short addr, int immediate, int data_value){
  if(word_ptr == NULL || (type != INSTR && type != DATA))
     return 0;
  if(type == INSTR){
    word_ptr->contents = type;
    word_ptr->value.instr.op = oper;
    word_ptr->value.instr.r1 = reg_1;
    word_ptr->value.instr.r2 = reg_2;
    word_ptr->value.instr.r3 = reg_3;
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
   3. If the parameters are odd.
   Otherwise:
   Return 1 if size is 0.
   Or
   Print each of the elements of the memory array starting with the start index and ending at start+size-1 following given guidelines.
   Then return 1. 
*/
int print_program(const Mem memory[], int start, int size){
  int i, inst;
  Mem value;
  if ((start % 2 != 0) || (size % 2 != 0) || (start < 0) || (size < 0) || (size > 255) || (start + size > 255)){
    return 0;
  }

  for(i = start; i < size+start; i+=2){
    value = memory[i/2];
    inst  = get_bit(value, instruct);
    if(inst == ADD){
      printf("%02x: add R%d R%d R%d\n", i,get_bit(value, reg1), 
	     get_bit(value, reg2), get_bit(value, reg3));
    }else if(inst == SUB){   
      printf("%02x: sub R%d R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2), get_bit(value, reg3));
    }else if(inst == MUL){
      printf("%02x: mul R%d R%d R%d\n", i, get_bit(value, reg1),
	     get_bit(value, reg2), get_bit(value, reg3));
    }else if(inst == DIV){
      printf("%02x: div R%d R%d R%d\n", i,  get_bit(value, reg1), 
	     get_bit(value, reg2), get_bit(value, reg3));
    }else if(inst == MOD){
      printf("%02x: mod R%d R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2), get_bit(value, reg3));
    }else if(inst == AND){
      printf("%02x: and R%d R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2), get_bit(value, reg3));
    }else if(inst == OR){
      printf("%02x: or R%d R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2), get_bit(value, reg3));
    }else if(inst == XOR){
      printf("%02x: xor R%d R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2), get_bit(value, reg3));
    }else if(inst == NOT){
      printf("%02x: not R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2));
    }else if(inst == NEG){ 
      printf("%02x: neg R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2));
    }else if(inst == INC){
      printf("%02x: inc R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2));
    }else if(inst == IO){
      printf("%02x: io R%d R%d\n", i, get_bit(value, reg1), 
	     get_bit(value, reg2));
    }else if(inst == MOVE){
      printf("%02x: move R%d R%d\n", i, get_bit(value, reg1), 
	       get_bit(value, reg2));
    }else if(inst == J){
	printf("%02x: j %02x\n", i, get_bit(value, reg_ia));
    }else if(inst == JSR){
      printf("%02x: jsr %02x\n", i, get_bit(value, reg_ia));
    }else if(inst == RTN){
      printf("%02x: rtn\n", i);
    }else if(inst == SW){
      printf("%02x: sw R%d %02x\n", i, get_bit(value, reg1),
	     get_bit(value, reg_ia));
    }else if(inst == LW){
      printf("%02x: lw R%d %02x\n", i, get_bit(value, reg1),
	     get_bit(value, reg_ia));
    }else if(inst == LI){
      printf("%02x: li R%d %02x\n", i, get_bit(value, reg1),
	     get_bit(value, reg_ia));
    }else if(inst == LO){
      printf("%02x: lo R%d R%d %02x\n", i, get_bit(value, reg1),
	     get_bit(value, reg_2d), get_bit(value, reg_ad));
    }else if(inst == BEQ){
      printf("%02x: beq R%d R%d %02x\n", i, get_bit(value, reg1),
	     get_bit(value, reg_2d), get_bit(value, reg_ad));
    }else if(inst == BNE){
      printf("%02x: bne R%d R%d %02x\n", i, get_bit(value, reg1),
	     get_bit(value, reg_2d), get_bit(value, reg_ad));
    }else if(inst == HALT){
      printf("%02x: halt\n", i);
    }else
      return 0;
  }
  return 1;
}
/* Shifts location of memory from start index to new_start_loc index with the same size.
   Returns 0 if current memory[start] begins outside of array or ends outside of array. 
      Or if new start loc starts/ends outside of the array. 
   Returns 0 if int parameters are negative or odd.
   returns 1 if size is 0.
   Returns 1 after cells are copied to new location.  Some overwriting may be doen.
*/

int shift_program(Mem memory[], int start, int size, int new_start_loc){
  int index, new_end = new_start_loc + size;
  if ((start%2 != 0) || (size%2 != 0) || (new_start_loc%2 != 0) ||
    (start < 0) || (size < 0) || (new_start_loc < 0) ||
    (size > 255) || (start + size > 255) || (new_end > 255))
    return 0;
  if ((new_start_loc <= start + size) && (new_start_loc > start)){
    for (index = size; index >= 0; index -= 2)
      memory[(new_start_loc + index)/2] = memory[(start + index)/2];
  } else {
    for (index = 0; index < size; index += 2)
      memory[(new_start_loc + index)/2] = memory[(start + index)/2];
  }


  return 1;
}

Status execute_program(Mem memory[], short regs[], int start, int max_instr,
                       int debug){
  int inst;
  int i;
  Mem value;
  int next_instr;

  if(start%2 != 0)
    return ERROR;

  if(max_instr <= 0)
    return ACTIVE;

  regs[7] = 0;
  regs[6] = 254;

  for(i = 1; i <= max_instr; i++){

    next_instr = regs[7] + start;
    value = memory[next_instr / 2];
    inst = get_bit(value, instruct);

    if((next_instr %2 != 0) || (next_instr < 0) || (next_instr > 254))
      return ERROR;

    if(inst == ADD){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = regs[get_bit(value, reg2)] + regs[get_bit(value, reg3)];
       

    }else if(inst == SUB){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = regs[get_bit(value, reg2)] - regs[get_bit(value, reg3)];
       

    }else if(inst == MUL){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = regs[get_bit(value, reg2)] * regs[get_bit(value, reg3)];
       

    }else if(inst == DIV){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      if(regs[get_bit(value, reg3)] == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = regs[get_bit(value, reg2)] / regs[get_bit(value, reg3)];
       

    }else if(inst == MOD){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      if(regs[get_bit(value, reg3)] == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = regs[get_bit(value, reg2)] % regs[get_bit(value, reg3)];
       

    }else if(inst == AND){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      if((regs[get_bit(value, reg2)] & regs[get_bit(value, reg3)]) != 0)
	regs[get_bit(value, reg1)] = 1;
      else
	regs[get_bit(value, reg1)] = 0;
       

    }else if(inst == OR){
      if(get_bit(value, reg1) == 0)
	return ERROR;
     if((regs[get_bit(value, reg2)] | regs[get_bit(value, reg3)]) != 0)
	regs[get_bit(value, reg1)] = 1;
      else
	regs[get_bit(value, reg1)] = 0;
      

    }else if(inst == XOR){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      if((regs[get_bit(value, reg2)] ^ regs[get_bit(value, reg3)]) != 0)
	regs[get_bit(value, reg1)] = 1;
      else
	regs[get_bit(value, reg1)] = 0;
       

    }else if(inst == NOT){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      if(regs[get_bit(value, reg2)] != 0)
	regs[get_bit(value, reg1)] = 0;
      else
	regs[get_bit(value, reg1)] = 1;
       

    }else if(inst == NEG){ 
      if(get_bit(value, reg1) == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = - regs[get_bit(value, reg2)];
       

    }else if(inst == INC){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = regs[get_bit(value, reg2)] + 1;
       

    }else if(inst == IO){
      if(regs[get_bit(value, reg1)] == 0){
	printf("%d", regs[get_bit(value, reg2)]);
      }else if(regs[get_bit(value, reg1)] == 1){
	scanf("%d", (int *) &regs[get_bit(value, reg2)]);
      }else if(regs[get_bit(value, reg1)] == 2){
	printf("%c", regs[get_bit(value, reg2)]);
      }else if(regs[get_bit(value, reg1)] == 3){
	scanf("%c", (char * ) &regs[get_bit(value, reg2)]);
      }else
	return ERROR;
       

    }else if(inst == MOVE){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = regs[get_bit(value, reg2)]; 
       
    }else if(inst == J){
      if(get_bit(value, reg_ia) % 2 != 0)
	return ERROR;
      regs[7] = get_bit(value, reg_ia);
      regs[7] -=2; /*I subtract 2 to counteract the increment
		     of 2 at the end of each iteration of the loop.*/

    }else if(inst == JSR){
      if(regs[6] == 0)
	return ERROR;
      memory[(start + regs[6]) / 2] = next_instr + 2;
      regs[6] -= 2;
      regs[7] = get_bit(value, reg_ia);
      regs[7] -=2;

    }else if(inst == RTN){
      if(regs[6] == 254)
	return ERROR;
      regs[6] += 2;
      regs[7] = memory[(start + regs[6])/2];
      regs[7] -=2;

    }else if(inst == SW){
      if(get_bit(value, reg_ia) %2 != 0)
	return ERROR;
      memory[(start + get_bit(value, reg_ia)) / 2] = regs[get_bit(value, reg1)];
       

    }else if(inst == LW){
      if((get_bit(value, reg1) == 0) || (get_bit(value, reg_ia) %2 != 0))
	return ERROR;
      regs[get_bit(value, reg1)] = memory[(start + get_bit(value, reg_ia)) /2];
       

    }else if(inst == LI){
      if(get_bit(value, reg1) == 0)
	return ERROR;
      regs[get_bit(value, reg1)] = get_bit(value, reg_ia);
       

    }else if(inst == LO){
      if(get_bit(value, reg1) == 0 || get_bit(value, reg_ad) %2 != 0)
      return ERROR;
      regs[get_bit(value, reg1)] = memory[(start + regs[get_bit(value, reg_2d)]
					   + get_bit(value, reg_ad))/2];
       

    }else if(inst == BEQ){
      if(regs[get_bit(value, reg1)] == regs[get_bit(value, reg_2d)]){
	regs[7] = get_bit(value, reg_ad);
	regs[7] -=2;
      }  

    }else if(inst == BNE){
      if(regs[get_bit(value, reg1)] != regs[get_bit(value, reg_2d)]){
	regs[7] = get_bit(value, reg_ad);
	regs[7] -=2;
      }

    }else if(inst == HALT){
      i--;
      return TERMINATED;

    }else{
      return ERROR;
    }
    regs[7] +=2;
  }
  return ACTIVE;
}


