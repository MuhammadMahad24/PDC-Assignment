#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000 //Array-size define directive

//Array-sum Function
void arraySumSequential(int arr[N],long long *sum)
{
    *sum=0;
    for(int i=0;i<N;i++)
    {
        *sum+=arr[i];
    }
}

int main()
{
    static int arr[N];
    long long sum;

    //Initialize array with random-values
    srand(time(NULL));
    for(int i=0;i<N;i++)
    {
        arr[i]=rand() % 10;
    }

clock_t start = clock();
arraySumSequential(arr, &sum);
clock_t end = clock();

double time_taken=((double)(end - start)) / CLOCKS_PER_SEC * 1000;
printf("Sequential Sum: %lld\n", sum);
printf("Sequential Execution Time: %.2f ms\n", time_taken);

return 0;

}


