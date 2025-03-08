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
int main()
{
    static int arr[N];
    long long sum;
    
    // Initialize array with random values
    srand(time(NULL));
    for(int i=0;i<N;i++)
    {
        arr[i]=rand() % 10;
    }
    double start=omp_get_wtime();
    arraySumParallel(arr,&sum);
    double end=omp_get_wtime();

    double time_taken=(end - start) * 1000;
    printf("Parallel Sum: %lld\n",sum);
    print("Parallel Execution Time: %.2f ms\n", time_taken);

    return 0;
}
