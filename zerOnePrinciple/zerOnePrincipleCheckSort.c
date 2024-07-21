#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../utils/arrayUtils.h"
#include "../sort/sort.h"

#define Dlong int64_t
#define int32 int32_t

bool zerOnePrincipleCheckSort(Dlong size){
    int32 *input = (int32 *)calloc(size, sizeof(int32));
    for (Dlong i = 0; i < pow(2, size); i++)
    {
        bitwiseRep(input, size, i);
        mergExchange(input, size, NULL);
        if (!checkIfSorted(input, size))
        {
            free(input);
            return false;
        }
        reset(input, size);
    }
    free(input);
    return true;
} 

int main(){
    int size;

    // Read the size of the array
    printf("Enter array size: ");
    scanf("%d", &size);
    if(zerOnePrincipleCheckSort(size)){
        printf("The sorting network satisfies the zero-one principle\n");
    }else{
        printf("The sorting network does not satisfy the zero-one principle\n");
    }
}