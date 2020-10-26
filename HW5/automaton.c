#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int n;
    int *line_1;
    int *line_2;
} life_t;

void rule30(life_t *life)
{
    for (int i = 1; i < life->n - 1; ++i)
        if (life->line_1[i-1] == 0 && life->line_1[i] == 0 && life->line_1[i+1] == 0)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 0 && life->line_1[i+1] == 1)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 1 && life->line_1[i+1] == 0)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 1 && life->line_1[i+1] == 1)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 0 && life->line_1[i+1] == 0)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 0 && life->line_1[i+1] == 1)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 1 && life->line_1[i+1] == 0)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 1 && life->line_1[i+1] == 1)
            life->line_2[i] = 0;
}

void rule110(life_t *life)
{
    for (int i = 1; i < life->n - 1; ++i)
        if (life->line_1[i-1] == 0 && life->line_1[i] == 0 && life->line_1[i+1] == 0)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 0 && life->line_1[i+1] == 1)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 1 && life->line_1[i+1] == 0)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 1 && life->line_1[i+1] == 1)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 0 && life->line_1[i+1] == 0)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 0 && life->line_1[i+1] == 1)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 1 && life->line_1[i+1] == 0)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 1 && life->line_1[i+1] == 1)
            life->line_2[i] = 0;
}

void rule184(life_t *life)
{
    for (int i = 1; i < life->n - 1; ++i)
        if (life->line_1[i-1] == 0 && life->line_1[i] == 0 && life->line_1[i+1] == 0)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 0 && life->line_1[i+1] == 1)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 1 && life->line_1[i+1] == 0)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 0 && life->line_1[i] == 1 && life->line_1[i+1] == 1)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 0 && life->line_1[i+1] == 0)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 0 && life->line_1[i+1] == 1)
            life->line_2[i] = 1;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 1 && life->line_1[i+1] == 0)
            life->line_2[i] = 0;
        else if (life->line_1[i-1] == 1 && life->line_1[i] == 1 && life->line_1[i+1] == 1)
            life->line_2[i] = 1;
}

void life_init(const int n, const int steps, life_t *life)
{
    &life->n = n;
    life->line_1 = (int*)calloc(life->n, sizeof(int));
    life->line_2 = (int*)calloc(life->n, sizeof(int));
    for(int i = 0; i < psize; ++i)
        life->line_1[i] = (i * 127 + 1) % 13 % 2;
}

void life_step(const int rool_id, life_t *life)
{
    if (rool_id == 30)
        rule30(life);
    else if(rool_id == 110)
        rule110(life);
    else if(rool_id == 110)
        rule184(life);
    int *tmp;
    tmp = life->line_1;
    life->line_1 = life->line_2;
    life->line_2 = tmp;
} 

void life_save(int step, life_t *life)
{
    FILE *f;
    f = fopen("output.txt", "a");
    for (int i = 0; i < life->n; ++i)
        if (life->line_1[i] == 1) 
            fprintf(f, "■");
        else 
            fprintf(f, "□");
    fprintf(f, "\n");
    fclose(f);
}

int main(int argc, char argv [])
{    
    const int RULE = (argc > 1) ? atoi(argv[1]) : 110;
    const int N = (argc > 2) ? atoi(argv[2]) : 20;
    const int STEPS = (argc > 3) ? atoi(argv[3]) : 20;
    const int GHOST = (argc > 4) ? atoi(argv[4]) : 1;
    int psize;
    int prank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);
    
    int dims = 0;
    int periods = 1;
    MPI_Dims_create(psize, 1, &dims);
    MPI_Comm cart_1d;
    MPI_Cart_create(MPI_COMM_WORLD, 1, &dims, &periods, 0, &cart_1d);
    
    MPI_Comm_rank(cart_1d, &prank);
    MPI_Comm_size(cart_1d, &psize);
    MPI_Status status;
    
    life_t life;
    if (prank == 0) 
    {
        life_init(N, STEPS, &life);
        life_save(0, &life);
    }

    MPI_Bcast(&life.n, 1, MPI_INT, 0, cart_1d);
    MPI_Bcast(&STEPS, 1, MPI_INT, 0, cart_1d);
    
    int blocksize = life.n / dims + 2 * GHOST;
    if (prank == dims - 1)
        blocksize += life.n % dims;

    life_t life_block;
    life_block.n = blocksize;
    life_block.line_1 = (int*)calloc(life_block.n, sizeof(int));
    life_block.line_2 = (int*)calloc(life_block.n, sizeof(int));
    
    int shift = life.n / dims;
    int *start = (int*)calloc(psize, sizeof(int));
    int *count = (int*)calloc(psize, sizeof(int));

    for(int i = 0; i < psize; ++i)
    {
        start[i] = i * shift;
        count[i] = shift;
    }
    count[psize - 1] += life.n % dims;
    
    int source;
    int dest;

    for (int i = 0; i < STEPS; ++i)
    {
        MPI_Scatterv(&life.line_1[0], &count[0], &start[0], MPI_INT,
            &life_block.line_1[GHOST], life_block.n - 2 * GHOST, MPI_INT, 0, cart_1d);
        MPI_Scatterv(&life.line_2[0], &count[0], &start[0], MPI_INT,
            &life_block.line_2[GHOST], life_block.n - 2 * GHOST, MPI_INT, 0, cart_1d);
        
        MPI_Cart_shift(cart_1d, 0, 1, &source, &dest);
        MPI_Send(&life_block.line_1[blocksize - GHOST - 1], 1, MPI_INT, dest, 0, cart_1d);
        MPI_Recv(&life_block.line_1[0], 1, MPI_INT, source, 0, cart_1d, &status);
        
        MPI_Cart_shift(cart_1d, 0, -1, &source, &dest);
        MPI_Send(&life_block.line_1[GHOST], 1, MPI_INT, dest, 0, cart_1d);
        MPI_Recv(&life_block.line_1[blocksize - 1], 1, MPI_INT, source, 0, cart_1d, &status);

        life_step(RULE, &life_block);

        MPI_Gatherv(&life_block.line_1[GHOST], blocksize - 2 * GHOST, MPI_INT,
            &life.line_1[0], count, start, MPI_INT, 0, cart_1d);
        MPI_Gatherv(&life_block.line_2[GHOST], blocksize - 2 * GHOST, MPI_INT,
            &life.line_2[0], count, start, MPI_INT, 0, cart_1d);
        if (prank == 0)
             life_save(i, &life);
    }

    MPI_Finalize();

    free(life.line_1);
    free(life.line_2);
    free(life_block.line_1);
    free(life_block.line_2);

    return 0;
}
