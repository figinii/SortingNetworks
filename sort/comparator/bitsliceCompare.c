#include "./bitsliceCompare.h"

#include <stdio.h>

void bitsliceCompare(int32 firstIndex, int32 secondIndex, int32* arr){
    
}

int main(){
    int32 rand = 2;
    bs_operand_t sliceTest;

    sliceTest = slice_constant(rand);

    for(int i = 0; i < BITSLICED_OPERAND_WIDTH; i++){
        printf("%d\n", sliceTest.slice[i]);
    }

    return 0;
}