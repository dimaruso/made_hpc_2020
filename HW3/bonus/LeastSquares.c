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
    omp_lock_t locker;
    omp_init_lock(&locker);
    const size_t nThreads = (argc > 2) ? atoi(argv[2]) : 4;

    srand(time(NULL));
    unsigned int seeds[nThreads];
    omp_set_num_threads(nThreads);
    seedThreads(nThreads, seeds);

    const size_t noise_max = 3, X_max = 100; // noise & X limits for rand
    double noise;
    size_t tid, seed;

    const double a = 17, b = 42; // real weight lin_reg
    double a_lr = 0.0, b_lr = 0.0; // init weight lin_reg
    const double lr = 0.0003; // learning_rate
    double y_pred, d_y, d_x;

    const size_t N = (argc > 1) ? atoi(argv[1]) : 50000;
    double X[N], y[N];

    if (argc > 3)
    {
        for (size_t i = 0; i < nThreads; ++i)
            printf("seed_%d = %d ", i, seeds[i]);
        printf("\n");
    }

#pragma omp parallel private(noise, tid, seed, y_pred, d_y, d_x)
    {
        tid = omp_get_thread_num();
        seed = seeds[tid];
        srand(seed);

// Generate data
#pragma omp for
        for (size_t i = 0; i < N; ++i)
        { 
            X[i] = (double) rand() / RAND_MAX;
            noise = (double) rand() / RAND_MAX;
            X[i] += (double) (rand() % X_max);
            noise += (double) (rand() % noise_max);

            y[i] = X[i] * a + b + noise;

            if (argc > 3)
                printf("\n tid = %d: x = %f, y = %f", tid, X[i], y[i]); 
        }
// Minimize Sum( (y[i] - f(X[i], a, b))^2 ) -> min(a,b)
#pragma omp for
        for (size_t i = 0; i < N; ++i)
        { 
            omp_set_lock(&locker);
            
            // forward
            y_pred = X[i] * a_lr + b_lr;
            // backward
            d_y = y_pred - y[i];
            d_x = X[i] * d_y;
            // update weight
            a_lr -= d_x * lr;
            b_lr -= d_y * lr;

            omp_unset_lock(&locker);
            
            // logger
            if ((N < 20 && i % N == 0) || (N >= 20 && i % (N / 20) == 0))
                printf("\ni = %d: y_pred = %f, y = %f, a = %f, b = %f", i, y_pred, y[i], a_lr, b_lr); 
        }
    }
    printf("\n\ntrue f(x) = %f * x + %f", a, b); 
    printf("\n\npred f(x) = %f * x + %f", a_lr, b_lr); 
    omp_destroy_lock(&locker);
    return 0;
}