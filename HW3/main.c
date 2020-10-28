#include <omp.h>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>

void seedThreads(const size_t nThreads, unsigned int* seeds) {
    int my_thread_id;
    unsigned int seed;
    #pragma omp parallel private (seed, my_thread_id)
    {
        my_thread_id = omp_get_thread_num();
        unsigned int seed = (unsigned) time(NULL);
        seeds[my_thread_id] = (seed & 0xFFFFFFF0) | (my_thread_id + 1);
    }
    return;
}

int main(int argc, char* argv[])
{
    const size_t nThreads = (argc > 2) ? atoi(argv[2]) : 4;

    srand(time(NULL));
    unsigned int seeds[nThreads];
    omp_set_num_threads(nThreads);
    seedThreads(nThreads, seeds);

    double x, y, Pi; 
    size_t a = 1;
    size_t in_circ = 0;
    const size_t N = (argc > 1) ? atoi(argv[1]) : 500000;
    size_t tid, seed;

    if (argc > 3)
    {
        for (size_t i = 0; i < nThreads; i++)
            printf("seed_%ld = %ld ", i, seeds[i]);
        printf("\n");
    }

#pragma omp parallel reduction(+: in_circ) \
                            private(x, y, tid, seed)
    {
        tid = omp_get_thread_num();
        seed = seeds[tid];
        srand(seed);

#pragma omp for 
        for (size_t i = 0; i < N; ++i)
        { 
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;
            x += rand() % a;
            y += rand() % a;

            if (argc > 3)
                printf("\n tid = %ld: x = %f, y = %f", tid, x, y); 

            if (x * x + y * y <= a * a)
                in_circ += 1; 
        }
    }
    Pi = ((double) in_circ / N) * 4;
    printf("\n\nin_circ = %ld, N = %ld, Pi = %f", in_circ, N, Pi); 
    return 0;
}