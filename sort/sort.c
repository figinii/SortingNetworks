#include "./comparator/compare.h"
#include "sort.h"

void bubbleSort(int32 *a, Dlong dim);
void mergExchange(int32 *arr, Dlong dim, comparator comparator);


void bubbleSort(int32 *a, Dlong dim)
{

    for (int32 i = 0; i < dim - 1; i++)
    {
        for (int32 j = 0; j < dim - i - 1; j++)
        {
            compare(j, j+1, a);
        }
    }
}

void mergExchange(int32 *arr, Dlong dim, comparator comparator)
{
    Dlong p, q, r, d, i;
    int firsTime;


    if(comparator == NULL)
        comparator = compare;

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
                    comparator(i, (i+d), arr);
                }
            }
            firsTime = 0;
        }while(q != p);
        
    }

}