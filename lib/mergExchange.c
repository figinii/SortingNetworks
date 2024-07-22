#include "mergExchange.h"

void mergExchange(int32 *arr, Dlong dim)
{
    Dlong p, q, r, d, i;
    int firsTime;

    Dlong top = 1;
    while (top < dim - top) top += top;

    for(p = top; p > 0; p >>= 1){
        q = top;
        r = 0;
        d = p;
        firsTime = 1;

        do{
            if(!firsTime){
                d = q - p;
                q >>= 1;
                r = p;
            }
            for(i = 0; i < dim - d; i++){
                if((i & p) == r)
                {
                    compare(&arr[i], &arr[i+d]);
                }
            }
            firsTime = 0;
        }while(q != p);
        
    }

}