#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000  // Array size

void arraySumParallel(int arr[N],long long *sum)
{
    *sum=0;
    #pragma omp parallel for reduction(+:*sum)
    for(int i=0;i<N;i++)
    {
        *sum+=arr[i];
    }
}

