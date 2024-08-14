/**
 * code adapted from
 * Optimized ISO-C11 Implementation of LEDAcrypt using GCC built-ins.
 * https://github.com/LEDAcrypt/LEDAcrypt/blob/master/Optimized_Implementation/Common/ninclude/bitslicing_helpers.h
 * @version 3.0 (May 2020)
 *
 * In alphabetical order:
 *
 * @author Marco Baldi <m.baldi@univpm.it>
 * @author Alessandro Barenghi <alessandro.barenghi@polimi.it>
 * @author Franco Chiaraluce <f.chiaraluce@univpm.it>
 * @author Gerardo Pelosi <gerardo.pelosi@polimi.it>
 * @author Paolo Santini <p.santini@pm.univpm.it>
 *
 **/

#pragma once

#include <stdint.h>
#include <immintrin.h>

#define int32 int32_t
#define SLICE_TYPE __m256i
#define BITSLICED_OPERAND_WIDTH 32 

/*bitsliced operand*/
typedef struct {
   SLICE_TYPE slice[BITSLICED_OPERAND_WIDTH];
} bs_operand_t;

static inline
void bitslice_half_adder(SLICE_TYPE  addend_a,
                         SLICE_TYPE  addend_b,
                         SLICE_TYPE *result,
                         SLICE_TYPE *carry_out)
{
   *result    = addend_a ^ addend_b;
   *carry_out = addend_a & addend_b;
   return;
}

static inline
bs_operand_t bitslice_inc(bs_operand_t a, SLICE_TYPE b)
{
   bs_operand_t result;
   SLICE_TYPE carry;
   bitslice_half_adder(a.slice[0],b,&(result.slice[0]),&carry);
   for(int i = 1; i<BITSLICED_OPERAND_WIDTH; i++) {
      bitslice_half_adder(a.slice[i],
                          carry,
                          &(result.slice[i]),
                          &carry);
   }
   return result;
}

static inline
bs_operand_t slice_constant(int32 constant)
{
   bs_operand_t result;
   for(int bit = 0; bit < BITSLICED_OPERAND_WIDTH; bit++) {
      result.slice[bit] = (SLICE_TYPE)0 - (constant & 1);
      constant >>=1;
   }
   return result;
}