#include <stdlib.h>  /* needed for definition of size_t */
#include "puzzles.h"

/* Josh Fann
   jfann 109901918
   CMSC216
   Project 1
*/
/*
  This function should return the bitwise AND of 
  the a and b parameters (a & b).

  DeMorgan's Law

  Allowed operators: + | ~ ^ << ! >>
*/
int bit_and(int a, int b){

  return ~(~a | ~b);

}

/* ************************************
  Returns 1 if x is not zero, 0 otherwise.

  Allowed operators: + & | ~ ^ << ! >>
*/
int is_nonzero(int x){
  return !(!x);
}

/*
  Returns 7 times x.  You may assume that the value of 7 * x 
  can be stored in an unsigned int without any overflow

  7*x = 4x + 2x + x

  Allowed operators: + & ~ | ^ << ! >>
  Allowed constants: 1 2 4 8 16

*/
unsigned int times7(unsigned int x){

  return (x << 2) + (x << 1) + x;

}

/*
  Returns the floor of the binary logarithm of x (i.e., log2(x)).  
  If x is 0, the function should return -1.

  Essentially finds the most significant bit by shifting x to the
  right until x is zero.  That's where it occurs.

  Allowed operators: ++ -- = & | ~ ^ << ! >>
  Allowed constants: 1 2 4 8 16
  Allowed constructs: for loops
*/
int floor_log2(unsigned int x){
  int count = -1;
  unsigned int i = 0;

  for(i = x; i; i= i >> 1)
    count++;
  return count;
}

/*
  Returns the size of an int, in bytes, without using the sizeof operator. 
  The return value should be equivalent to the expression sizeof(int).
  Note that your function must be written to work on any system, 
  so you may not make any assumptions about the size of an int
  based on what you know of the Grace systems.

  Allowed operators: ++ -- = & | ~ ^ << ! >>
  Allowed constants: 1 2 4 8 16
  Allowed constructs: for loops
*/
size_t sizeof_int(){
  int bit = 1;
  unsigned int mask = 1, x;
  size_t num_bytes;
  /* Loop skips the first bit because first bit of ~1 is always zero.*/
  for(x = ~1; x; bit++){
    mask = mask << 1;
    /*Deletes the 1 value of x where mask is located. 
      Then increments bit counter*/
    x ^= mask;
  }
  /*When x becomes 0, convert bit count to byte counts.  Divide by 8.*/
  num_bytes = bit >> 3;
  return num_bytes;
}

/*
  Reverse the bytes of x (you may assumed that ints are 
  4 bytes in size for this function).

  Allowed operators: + - = & | ~ ^ << ! >>
  Allowed constants: 1 2 4 8 16
*/
unsigned int reverse_bytes(unsigned int x){
  unsigned int to_return = 0, mask = 0xff << (16+8);
  /*Moves first byte to last byte*/
  to_return = (mask & x) >> (16+8); /*shift by 24 bits to first byte of int.*/
  mask = mask >> 8;
  /*Moves second byte to 3rd byte*/
  to_return |= (mask & x) >> 8;
  mask = mask >> 8;
  /*Moves 3rd byte to 2nd byte*/
  to_return |= (mask & x) << 8;
  mask = mask >> 8;
  /*Moves last byte to 1st byte*/
  to_return |= (mask & x) << (16 + 8);
  return to_return;

}

/* 
   Returns 0xc0c0c0c0

   Adds 12 then shifts to the left.
   Allowed operators: + - = & | ~ << ! >>
   Allowed constants: 1 2 4 8 16
 */
unsigned int hex_c0c0c0c0(){
  unsigned int ret = 8 + 4;
  ret = (((ret << 8 | ret) << 8 | ret) << 8 | ret) << 4;
  return ret;
}

/*
  Return the population count( the number of bits set to 1) of x.

  Sets mask first to equal x.  Then sets x to x & mask -1.  This
  removes the least significant bit of x.  Does this until x is zero.
  Count increments until x is zero.  Function returns count.

  Allowed operators: ++ -- = & ~ | ^ << ! >>
  Allowed constants: 1 2 4 8 16
  Allowed constructs: while loops
*/
int pop_count(unsigned int x){
  int count = 0, mask = x;
  while(x){
    mask --;
    x &= mask;
    mask= x;
    count++;
  }
  return count;
}

/*
  Return the nth-most signficant byte of x 
  (with n == 0 denoting the most significant byte).

  Allowed operators: + - = & | ~ ^ << ! >>
  Allowed constants: 1 2 4 8 16
*/
unsigned int get_byte(unsigned int x, int n){
  unsigned int to_return, mask = 0xFF;
  /*Takes 3-n and shifts it to the left by 3 bits and compares it
    with wanted byte.  Returns correct byte*/
  int shift = (2 + 1 - n) << (4 - 1);
  to_return = x & (mask << shift);
  to_return = to_return >> shift;
  return to_return;

}

/*
  Return 1 if a == b, 0 otherwise.

  Allowed operators: + & | ~ ^ << ! >>
  Allowed constants: 1 2 4 8 16
*/
int equal(int a, int b){
  /* If a and b are equal, then their XOR value will be 0.
     Otherwise it will return some value greater than 0. */
    return !(a^b);

}
