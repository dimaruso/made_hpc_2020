#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

float dotprod(float * a, float * b, size_t N)
{
    int tid;
    float sum;


#pragma omp parallel for reduction(+:sum) private(tid)
    for (size_t i = 0; i < N; ++i)
    {
        sum += a[i] * b[i];
        tid = omp_get_thread_num();
        printf("tid = %d i = %d\n", tid, i);
    }

    return sum;
}

int main (int argc, char *argv[])
{
    const size_t N = 100;
    float sum = 0.0;
    float a[N], b[N];

#pragma omp parallel for 
    for (size_t i = 0; i < N; ++i)
    {
        a[i] = b[i] = (double)i;
    }

    sum = dotprod(a, b, N);

    printf("Sum = %f\n",sum);

    return 0;
}