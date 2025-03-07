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
    
    for(int i=0;i<N;i++)
    {
        arr[i]=rand() % 10;
    }
}




